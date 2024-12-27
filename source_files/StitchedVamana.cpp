#include "fun.hpp"
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <thread>
#include <vector>

#define Flag 999
#define Kappa 0

void processVamana(Graph* G, int L_small, int R_small, double a, int f) {
    Vamana(G, L_small, R_small, a, f, false);
}

void processRobustPrune(Graph* G, double a, int start, int end) {
    for (int v = start; v < end; ++v) {
        Filtered_Robust_Prune(v, (G->index_array[v].edges), a, G);
    }
}

int StichedVamana(Graph* G, int L_small, int R_small, int R_stitched, double a) {
    srand(time(NULL));
    G->kappa = Kappa;
    G->flag = Flag;
    std::cout << "\nSTART STITCHED VAMANA" << std::endl;
    fflush(stdout);
    std::cout << "PROGRESS : ";
    fflush(stdout);

    // Thread vector for parallel Vamana calls
    std::vector<std::thread> vamanaThreads;

    // Create a stitched graph over points (parallel Vamana calls)
    for (int f = 0; f < G->Filters_Size; ++f) {
        vamanaThreads.emplace_back(processVamana, G, L_small, R_small, a, f);
    }

    // Join all Vamana threads
    for (auto& t : vamanaThreads) {
        if (t.joinable()) {
            t.join();
        }
    }

    G->R = R_stitched;

    // Divide work for robust pruning among multiple threads
    int numThreads = std::thread::hardware_concurrency(); // Number of available threads
    int totalNodes = G->number_of_indexes;
    int chunkSize = (totalNodes + numThreads - 1) / numThreads; // Calculate chunk size
    std::vector<std::thread> pruningThreads;

    for (int i = 0; i < numThreads; ++i) {
        int start = i * chunkSize;
        int end = std::min(start + chunkSize, totalNodes);
        if (start < totalNodes) {
            pruningThreads.emplace_back(processRobustPrune, G, a, start, end);
        }
    }

    // Join all pruning threads
    for (auto& t : pruningThreads) {
        if (t.joinable()) {
            t.join();
        }
    }

    std::cout << "\nEND STITCHED VAMANA" << std::endl;
    fflush(stdout);
    return 0;
}
