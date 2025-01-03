#include "fun.hpp"
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <set>
#define Flag 999
#define Kappa 0

// Define dedicated mutexes for each critical operation
std::mutex greedy_search_mutex;
std::mutex robust_prune_mutex;
std::mutex edge_access_mutex;
std::mutex result_cleanup_mutex;
std::mutex random_perm_mutex;
std::mutex progress_output_mutex;
std::mutex graph_mutex; // Mutex for accessing Graph-related data
std::mutex set_mutex; // Mutex for accessing and modifying std::set

int* Filtered_Vamana(Graph *G, int L, int R, double a) {
    int threshold = 1;
    int *s = nullptr;

    // Lock for Graph data updates
    {
        std::lock_guard<std::mutex> lock(graph_mutex);
        G->kappa = Kappa;
        G->flag = Flag;
        G->R = R;
    }

    srand(static_cast<unsigned>(time(nullptr)));

    // Find medoid
    {
        std::lock_guard<std::mutex> lock(graph_mutex);
        s = FindMedoid(G, threshold);
    }

    std::vector<int> RandomPerm;
    {
        std::lock_guard<std::mutex> lock(random_perm_mutex);
        RandomPerm = RandomPermutation(G, false, -1);
    }

    std::cout << "\nSTART FILTERED VAMANA" << std::endl;
    std::cout << "PROGRESS : " << std::endl;

    // Determine number of threads
    int num_threads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;

    int chunk_size = G->number_of_indexes / num_threads;
    int remainder = G->number_of_indexes % num_threads;

    auto process_chunk = [&](int start, int end) {
        std::set<int> TempSet;

        for (int i = start; i < end; ++i) {
            int RandomPermutationIndex;
            {
                std::lock_guard<std::mutex> lock(random_perm_mutex);
                if (i >= (int)RandomPerm.size()) {
                    std::cerr << "Error: RandomPerm access out of bounds: " << i << std::endl;
                    continue;
                }
                RandomPermutationIndex = RandomPerm[i];
            }

            Result_greedy *result_greedy = nullptr;

            // Lock and call Filtered_Greedy_Search
            {
                std::lock_guard<std::mutex> lock(greedy_search_mutex);
                result_greedy = Filtered_Greedy_Search(G, RandomPermutationIndex, 0, L, s, nullptr);
                if (!result_greedy) {
                    std::cerr << "Error: result_greedy is null for node: " << RandomPermutationIndex << std::endl;
                    // Serialize the processing to avoid further issues
                    continue;
                }
            }

            // Lock and call Filtered_Robust_Prune
            {
                std::lock_guard<std::mutex> lock(robust_prune_mutex);
                Filtered_Robust_Prune(RandomPermutationIndex, result_greedy->V, a, G);
            }

            // Process edges safely
            for (auto &j : G->index_array[RandomPermutationIndex].edges) {
                if (j < 0 || j >= G->number_of_indexes) {
                    std::cerr << "Error: Edge index out of bounds: " << j << std::endl;
                    continue;
                }

                // Lock TempSet with mutex to avoid concurrent modification
                {
                    std::lock_guard<std::mutex> lock(set_mutex);
                    TempSet.clear();
                    for (auto &element : G->index_array[j].edges) {
                        TempSet.insert(element);
                    }
                    TempSet.insert(RandomPermutationIndex);
                }

                {
                    std::lock_guard<std::mutex> lock(robust_prune_mutex);
                    Filtered_Robust_Prune(j, TempSet, a, G);
                }
            }

            // Cleanup result_greedy
            {
                std::lock_guard<std::mutex> lock(result_cleanup_mutex);
                if (result_greedy) {
                    delete result_greedy;
                    result_greedy = nullptr;
                }
            }
        }
    }; // 

    // Launch threads and divide the work
    int start = 0;
    for (int t = 0; t < num_threads; ++t) {
        int end = start + chunk_size + (t < remainder ? 1 : 0);
        threads.emplace_back(process_chunk, start, end);
        start = end;
    }

    // Wait for all threads to complete
    for (auto &thread : threads) {
        thread.join();
    }

    std::cout << "\nEND FILTERED VAMANA" << std::endl;
    return s;
}
