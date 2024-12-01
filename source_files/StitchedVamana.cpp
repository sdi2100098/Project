#include "fun.hpp"
#include <time.h>
#include <stdlib.h>
#include <iostream>

int* StichedVamana(const char *file_path, Graph *G, int L_small, int R_small,int R_stitched, double a) {
    int *s = NULL;
    Result_greedy *result_greedy = NULL;
    /*Initialize G to an Empty Graph*/
    int result = Init_Graph_Data(G, file_path, true);
    if (result == 1)
    {
        perror("Error in Init_Graph");
        return NULL;
    }
    // Create a stitched graph over points
    for (int f = 0; f < G->Filters_Size; f++) {
        std::vector<int> &Pf = G->Filters[f]; // Set of points with label f
        Graph Gf; // Temporary subgraph for the current filter

        Init_Graph_Data(&Gf, file_path, true); // Initialize Gf for the subset
        Gf.Filters_Size = 1; // Only one filter active in this subgraph
        Gf.R = R_small;

        // Call Vamana on the subset of points
        Vamana(file_path, &Gf, L_small, R_small, a, G->Filters[f]);

        // Merge edges into the main graph
        for (int i = 0; i < Pf.size(); i++) {
            int point = Pf[i];
            G->index_array[point].edges.insert(Gf.index_array[point].edges.begin(), Gf.index_array[point].edges.end());
        }

        Delete_Graph(&Gf, true); // Clean up temporary subgraph
    }

    // Apply robust pruning to all nodes in the graph
    for (int v = 0; v < G->number_of_indexes; v++) {
        Filtered_Robust_Prune(v, &G->index_array[v].edges, a, G);
    }

    std::cout << "Stitched Vamana completed successfully." << std::endl;
    return s;
}


