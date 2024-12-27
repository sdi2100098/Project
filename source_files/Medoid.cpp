#include "fun.hpp"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <limits>
#include <thread>
#include <vector>
#include <mutex>

int Medoid(Graph* G, int filter) {
    float MinDistance = std::numeric_limits<float>::max();
    int MedoidIndex = -1;
    std::vector<float> array(G->Filters[filter].size(), 0.0f);
    std::mutex minMutex; // To protect shared variables

    // Function to compute distances in parallel
    auto computeDistances = [&](int start, int end) {
        for (int i = start; i < end; ++i) {
            float SumDistances = 0.0f;
            for (int j = 0; j < (int)G->Filters[filter].size(); ++j) {
                SumDistances += EuclideanDistance(
                    G->index_array[G->Filters[filter][i]].vector,
                    G->index_array[G->Filters[filter][j]].vector,
                    G->dimension
                );
            }
            array[i] = SumDistances;
        }
    };

    // Determine the number of threads and split the workload
    int numThreads = std::thread::hardware_concurrency();
    int totalElements = (int)G->Filters[filter].size();
    int chunkSize = (totalElements + numThreads - 1) / numThreads;
    std::vector<std::thread> threads;

    for (int t = 0; t < numThreads; ++t) {
        int start = t * chunkSize;
        int end = std::min(start + chunkSize, totalElements);
        if (start < totalElements) {
            threads.emplace_back(computeDistances, start, end);
        }
    }

    // Join all threads
    for (auto& t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    // Find the minimum distance
    for (int i = 0; i < totalElements; ++i) {
        std::lock_guard<std::mutex> lock(minMutex);
        if (array[i] < MinDistance) {
            MinDistance = array[i];
            MedoidIndex = G->Filters[filter][i];
        }
    }

    return MedoidIndex;
}
