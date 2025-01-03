#include "fun.hpp"
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <atomic>
#include <set>
#define Flag 999
#define Kappa 0

// Global mutex
std::mutex mtx;
std::mutex progress_mutex;  // Mutex for safe progress reporting
std::atomic<int> threads_finished(0);  // Atomic counter to track how many threads have finished

// Worker function to process a single index
void ProcessIndex(Graph *G, int L, int R, double a, int RandomPermutationIndex, int *s)
{
    std::set<int> TempSet;
    Result_greedy *result_greedy = nullptr;

    // Call Filtered_Greedy_Search with mutex lock
    {
        std::lock_guard<std::mutex> lock(mtx);
        result_greedy = Filtered_Greedy_Search(G, RandomPermutationIndex, 0, L, s, nullptr);
    }

    // Call Filtered_Robust_Prune with mutex lock
    {
        std::lock_guard<std::mutex> lock(mtx);
        Filtered_Robust_Prune(RandomPermutationIndex, result_greedy->V, a, G);
    }

    // Lock the entire section that processes the neighbors of RandomPermutationIndex
    {
        std::lock_guard<std::mutex> lock(mtx);

        for (auto &j : G->index_array[RandomPermutationIndex].edges)
        {
            TempSet.clear();

            // Access G->index_array[j].edges and modify TempSet
            for (auto &element : G->index_array[j].edges)
                TempSet.insert(element);
            TempSet.insert(RandomPermutationIndex);

            // Call Filtered_Robust_Prune if needed
            Filtered_Robust_Prune(j, TempSet, a, G);
        }
    }

    // Delete the result structure
    delete result_greedy;
}

int *Filtered_Vamana(Graph *G, int L, int R, double a)
{
    int *s = nullptr;
    int threshold = 1;

    G->kappa = Kappa;
    G->flag = Flag;
    G->R = R;

    srand(time(NULL));

    // Find the Medoid
    s = FindMedoid(G, threshold);

    // Generate a random permutation
    std::vector<int> RandomPerm = RandomPermutation(G, false, -1);

    std::cout << "\nSTART FILTERED VAMANA" << std::endl;
    printf("\nPROGRESS : ");
    fflush(stdout);

    // Create a vector of threads
    std::vector<std::thread> threads;

    // Calculate the progress step (every 10% of the total nodes)
    int progress_step = G->number_of_indexes / 10;

    // Spawn threads for each index
    for (int i = 0; i < G->number_of_indexes; i++, G->kappa++)
    {
        // Spawn a thread for each index
        threads.emplace_back([=, &G]() {
            // Process the index
            ProcessIndex(G, L, R, a, RandomPerm[i], s);

            // Update the progress in a thread-safe way
            {
                std::lock_guard<std::mutex> lock(progress_mutex);

                // Increment the number of finished threads
                threads_finished++;

                // Only display progress every 10% of the work
                if (threads_finished.load() % progress_step == 0) {
                    // Calculate the overall progress percentage
                    float progress = (float)threads_finished.load() / G->number_of_indexes * 100;
                    printf(" %.0f %%", progress);
                    fflush(stdout);
                }
            }
        });
    }

    // Wait for all threads to finish
    for (auto &t : threads)
    {
        if (t.joinable())
            t.join();
    }

    std::cout << "\nEND FILTERED VAMANA" << std::endl;
    fflush(stdout);

    return s;
}