#include "fun.hpp"
#include <iostream>
#include <thread>
#include <vector>
#include <set>
#include <chrono>

void processRange(Query& Q, const Ground_Truth& GT, Graph* G, int k, int L, int* S, int start, int end, 
                  int& localAccuracy_filtered, int& localAccuracy_unfiltered, 
                  double& local_time_filtered, double& local_time_unfiltered, int& local_filtered_count, int& local_unfiltered_count) {
    std::set<int> Temp_Set;
    Result_greedy* Result;

    for (int i = start; i < end; ++i) {
        int sum = 0;
        Result = Filtered_Greedy_Search(G, i, k, L, S, &Q);

        Temp_Set.clear();
        for (auto it = Result->L.begin(); it != Result->L.end(); ++it) {
            Temp_Set.insert(it->second);
        }

        // Track time for query processing
        auto start_time = std::chrono::high_resolution_clock::now();

        // Check if the query is filtered or unfiltered
        if (Q.index_array[i].filter == -1) { // Unfiltered query
            local_unfiltered_count++;
            for (int j = 0; j < GT.array[i].K; j++) {
                if (Temp_Set.find(GT.array[i].K_NBH_array[j]) != Temp_Set.end()) {
                    sum++;
                }
            }
            if ((double)sum / GT.array[i].K >= 0.9) {
                localAccuracy_unfiltered++;
            }
        } else { // Filtered query
            local_filtered_count++;
            for (int j = 0; j < GT.array[i].K; j++) {
                if (Temp_Set.find(GT.array[i].K_NBH_array[j]) != Temp_Set.end()) {
                    sum++;
                }
            }
            if ((double)sum / GT.array[i].K >= 0.9) {
                localAccuracy_filtered++;
            }
        }

        // Calculate the time taken for this query (filtered or unfiltered)
        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end_time - start_time;
        if (Q.index_array[i].filter == -1) {
            local_time_unfiltered += duration.count();
        } else {
            local_time_filtered += duration.count();
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

    // Local variables for each thread
    std::vector<int> localAccuracies_filtered(numThreads, 0);
    std::vector<int> localAccuracies_unfiltered(numThreads, 0);
    std::vector<double> localTime_filtered(numThreads, 0.0);
    std::vector<double> localTime_unfiltered(numThreads, 0.0);
    std::vector<int> localFilteredCounts(numThreads, 0);
    std::vector<int> localUnfilteredCounts(numThreads, 0);

    std::vector<std::thread> threads;

    // Spawn threads
    for (int t = 0; t < numThreads; ++t) {
        int start = t * chunkSize;
        int end = std::min(start + chunkSize, totalIndices);
        if (start < totalIndices) {
            threads.emplace_back(processRange, std::ref(Q), std::cref(GT), G, k, L, S, start, end,
                                 std::ref(localAccuracies_filtered[t]), std::ref(localAccuracies_unfiltered[t]),
                                 std::ref(localTime_filtered[t]), std::ref(localTime_unfiltered[t]),
                                 std::ref(localFilteredCounts[t]), std::ref(localUnfilteredCounts[t]));
        }
    }

    // Join threads
    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }

    // Combine results from all threads
    int accuracy_filtered = 0, accuracy_unfiltered = 0;
    double total_time_filtered = 0.0, total_time_unfiltered = 0.0;
    int filtered_count = 0, unfiltered_count = 0;

    for (int t = 0; t < numThreads; ++t) {
        accuracy_filtered += localAccuracies_filtered[t];
        accuracy_unfiltered += localAccuracies_unfiltered[t];
        total_time_filtered += localTime_filtered[t];
        total_time_unfiltered += localTime_unfiltered[t];
        filtered_count += localFilteredCounts[t];
        unfiltered_count += localUnfilteredCounts[t];
    }

    // Print the results
    printf("\033[0;32m");
    printf("\nUnfiltered Queries Accuracy: %d/%d Passed Test", accuracy_unfiltered, unfiltered_count);
    if ((double)accuracy_unfiltered / unfiltered_count >= 0.9) {
        printf("\033[0;32m");
    } else {
        printf("\033[0;31m");
    }
    printf(" ~= %.2f%%\n", (double)accuracy_unfiltered / unfiltered_count * 100);

    printf("\nFiltered Queries Accuracy: %d/%d Passed Test", accuracy_filtered, filtered_count);
    if ((double)accuracy_filtered / filtered_count >= 0.9) {
        printf("\033[0;32m");
    } else {
        printf("\033[0;31m");
    }
    printf(" ~= %.2f%%\n", (double)accuracy_filtered / filtered_count * 100);

    // Calculate average time per query
    double avg_time_unfiltered = (unfiltered_count > 0) ? total_time_unfiltered / unfiltered_count : 0.0;
    double avg_time_filtered = (filtered_count > 0) ? total_time_filtered / filtered_count : 0.0;

    printf("\nAverage Time per Unfiltered Query: %.6f seconds\n", avg_time_unfiltered);
    printf("Average Time per Filtered Query: %.6f seconds\n", avg_time_filtered);

    if ((double)(accuracy_filtered + accuracy_unfiltered) / Q.number_of_indexes >= 0.9) {
        printf("\033[0;32m");
    } else {
        printf("\033[0;31m");
    }

    printf("%d/%d Total Queries Passed Test", accuracy_filtered + accuracy_unfiltered, Q.number_of_indexes);
    std::cout << " ~= " << (int)((accuracy_filtered + accuracy_unfiltered) / (double)Q.number_of_indexes * 100) << "%\n" << std::endl;
    printf("\033[0m");

    Delete_Query(&Q);
    Delete_Ground_Truth(&GT);
    return 0;
}
