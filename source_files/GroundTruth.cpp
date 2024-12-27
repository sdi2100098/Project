#include "fun.hpp"
#include <iostream>
#include <thread>
#include <vector>
#include <set>

void processRange(Query& Q, const Ground_Truth& GT, Graph* G, int k, int L, int* S, int start, int end, int& localAccuracy) {
    std::set<int> Temp_Set;
    Result_greedy* Result;

    for (int i = start; i < end; ++i) {
        int sum = 0;
        Result = Filtered_Greedy_Search(G, i, k, L, S, &Q);

        Temp_Set.clear();
        for (auto it = Result->L.begin(); it != Result->L.end(); ++it) {
            Temp_Set.insert(it->second);
        }

        for (int j = 0; j < GT.array[i].K; ++j) {
            if (Temp_Set.find(GT.array[i].K_NBH_array[j]) != Temp_Set.end()) {
                sum++;
            }
        }

        if ((double)sum / GT.array[i].K >= 0.9) {
            localAccuracy++;
        }

        delete Result;
    }
}

int GroundTruth(const char* Query_path, const char* Ground_Truth_path, Graph* G, int k, int L, int* S) {
    std::cout << std::endl;

    Ground_Truth GT;
    Query Q;

    int result = Init_Query_Data(&Q, Query_path, G->Filters_Size);
    if (result == 1)
        return 1;

    result = Init_Ground_Truth_Data(&GT, Ground_Truth_path);
    if (result == 1)
        return 1;

    // Determine the number of threads and divide the workload
    int numThreads = std::thread::hardware_concurrency();
    int totalIndices = Q.number_of_indexes;
    int chunkSize = (totalIndices + numThreads - 1) / numThreads;

    // Local accuracy for each thread
    std::vector<int> localAccuracies(numThreads, 0);
    std::vector<std::thread> threads;

    // Spawn threads
    for (int t = 0; t < numThreads; ++t) {
        int start = t * chunkSize;
        int end = std::min(start + chunkSize, totalIndices);
        if (start < totalIndices) {
            threads.emplace_back(processRange, std::ref(Q), std::cref(GT), G, k, L, S, start, end, std::ref(localAccuracies[t]));
        }
    }

    // Join threads
    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }

    // Combine results
    int accuracy = 0;
    for (const auto& localAccuracy : localAccuracies) {
        accuracy += localAccuracy;
    }

    // Output results
    if ((double)accuracy / Q.number_of_indexes >= 0.9)
        printf("\033[0;32m");
    else
        printf("\033[0;31m");

    printf("%d/%d Passed Test", accuracy, Q.number_of_indexes);
    std::cout << " ~= " << (int)((accuracy / (double)Q.number_of_indexes) * 100) << "%\n" << std::endl;
    printf("\033[0m");

    Delete_Query(&Q);
    Delete_Ground_Truth(&GT);
    return 0;
}
