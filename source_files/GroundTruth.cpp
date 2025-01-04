#include "fun.hpp"
#include <iostream>
#include <thread>
#include <vector>
#include <set>
#include <chrono>

// Function to process a range of queries in parallel
void processRange(Query& Q, const Ground_Truth& GT, Graph* G, int k, int L, int* S, int start, int end, 
                  int& localAccuracyFiltered, int& localAccuracyUnfiltered, 
                  double& localTimeFiltered, double& localTimeUnfiltered, 
                  float* Distances) {
    std::set<int> Temp_Set;
    Result_greedy* Result;

    for (int i = start; i < end; ++i) {
        int sum = 0;
        // Initialize the Distances array for the current query
        for (int j = 0; j < G->number_of_indexes; ++j) {
            Distances[j] = -1.0f;
        }

        Result = Filtered_Greedy_Search(G, i, k, L, S, &Q, Distances);

        Temp_Set.clear();
        for (auto it = Result->L.begin(); it != Result->L.end(); ++it) {
            Temp_Set.insert(it->second);
        }

        // Track time for query processing
        auto start_time = std::chrono::high_resolution_clock::now();

        // Check if the query is filtered or unfiltered
        if (Q.index_array[i].filter == -1) { // Unfiltered query
            for (int j = 0; j < GT.array[i].K; ++j) {
                if (Temp_Set.find(GT.array[i].K_NBH_array[j]) != Temp_Set.end()) {
                    sum++;
                }
            }
            if ((double)sum / GT.array[i].K >= 0.9) {
                localAccuracyUnfiltered++;
            }
        } else { // Filtered query
            for (int j = 0; j < GT.array[i].K; ++j) {
                if (Temp_Set.find(GT.array[i].K_NBH_array[j]) != Temp_Set.end()) {
                    sum++;
                }
            }
            if ((double)sum / GT.array[i].K >= 0.9) {
                localAccuracyFiltered++;
            }
        }

        // Calculate the time taken for this query (filtered or unfiltered)
        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end_time - start_time;

        if (Q.index_array[i].filter == -1) {
            localTimeUnfiltered += duration.count();
        } else {
            localTimeFiltered += duration.count();
        }

        delete Result;
    }
}

int GroundTruth(const char* Query_path, const char* Ground_Truth_path, Graph* G, int k, int L, int* S) {
    std::cout << std::endl;

    Ground_Truth GT;
    Query Q;

    int result = Init_Query_Data(&Q, Query_path, G->Filters_Size);
    if (result == 1) return 1;

    result = Init_Ground_Truth_Data(&GT, Ground_Truth_path);
    if (result == 1) return 1;

    // Determine the number of threads and divide the workload
    int numThreads = std::thread::hardware_concurrency();
    int totalIndices = Q.number_of_indexes;
    int chunkSize = (totalIndices + numThreads - 1) / numThreads;

    // Local accuracy and time for each thread
    std::vector<int> localAccuraciesFiltered(numThreads, 0);
    std::vector<int> localAccuraciesUnfiltered(numThreads, 0);
    std::vector<double> localTimeFiltered(numThreads, 0.0);
    std::vector<double> localTimeUnfiltered(numThreads, 0.0);
    std::vector<std::thread> threads;

    // Allocate a separate Distances array for each thread
    std::vector<std::vector<float>> threadDistances(numThreads, std::vector<float>(G->number_of_indexes, -1.0f));

    // Spawn threads
    for (int t = 0; t < numThreads; ++t) {
        int start = t * chunkSize;
        int end = std::min(start + chunkSize, totalIndices);
        if (start < totalIndices) {
            threads.emplace_back(processRange, std::ref(Q), std::cref(GT), G, k, L, S, start, end, 
                                 std::ref(localAccuraciesFiltered[t]), std::ref(localAccuraciesUnfiltered[t]), 
                                 std::ref(localTimeFiltered[t]), std::ref(localTimeUnfiltered[t]), 
                                 threadDistances[t].data());
        }
    }

    // Join threads
    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }

    // Combine results
    int accuracyFiltered = 0, accuracyUnfiltered = 0;
    double totalTimeFiltered = 0.0, totalTimeUnfiltered = 0.0;

    for (int t = 0; t < numThreads; ++t) {
        accuracyFiltered += localAccuraciesFiltered[t];
        accuracyUnfiltered += localAccuraciesUnfiltered[t];
        totalTimeFiltered += localTimeFiltered[t];
        totalTimeUnfiltered += localTimeUnfiltered[t];
    }

    // Output filtered queries accuracy and time
    printf("\033[0;32m");
    printf("\nFiltered Queries Accuracy: %d/%d Passed Test", accuracyFiltered, totalIndices - accuracyUnfiltered);
    if ((double)accuracyFiltered / (totalIndices - accuracyUnfiltered) >= 0.9)
        printf("\033[0;32m");
    else
        printf("\033[0;31m");
    printf(" ~= %.2f%%\n", (double)accuracyFiltered / (totalIndices - accuracyUnfiltered) * 100);

    // Output unfiltered queries accuracy and time
    printf("Unfiltered Queries Accuracy: %d/%d Passed Test", accuracyUnfiltered, accuracyUnfiltered);
    if ((double)accuracyUnfiltered / accuracyUnfiltered >= 0.9)
        printf("\033[0;32m");
    else
        printf("\033[0;31m");
    printf(" ~= %.2f%%\n", (double)accuracyUnfiltered / accuracyUnfiltered * 100);

    // Calculate average time per query
    double avgTimeFiltered = (accuracyFiltered > 0) ? totalTimeFiltered / accuracyFiltered : 0.0;
    double avgTimeUnfiltered = (accuracyUnfiltered > 0) ? totalTimeUnfiltered / accuracyUnfiltered : 0.0;

    printf("Average Time per Filtered Query: %.6f seconds\n", avgTimeFiltered);
    printf("Average Time per Unfiltered Query: %.6f seconds\n", avgTimeUnfiltered);

    // Output total accuracy
    if ((double)(accuracyFiltered + accuracyUnfiltered) / Q.number_of_indexes >= 0.9)
        printf("\033[0;32m");
    else
        printf("\033[0;31m");

    printf("%d/%d Total Queries Passed Test", accuracyFiltered + accuracyUnfiltered, Q.number_of_indexes); // Total accuracy needs to be > 0.9*number_of_indexes
    std::cout << " ~= " << (int)((accuracyFiltered + accuracyUnfiltered) / (double)Q.number_of_indexes * 100) << "%\n" << std::endl;
    printf("\033[0m");

    Delete_Query(&Q);
    Delete_Ground_Truth(&GT);
    return 0;
}
