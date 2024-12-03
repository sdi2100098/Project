#include "fun.hpp"
#include <time.h>
#include <stdlib.h>
#include <iostream>

int StichedVamana(const char *file_path, Graph *G, int L_small, int R_small, int R_stitched, double a)
{
    srand(time(NULL));
    /*Initialize G to an Empty Graph*/
    int result = Init_Graph_Data(G, file_path, true);

    if (result == 1)
    {
        perror("Error in Init_Graph");
        return 1;
    }
    // Create a stitched graph over points
    for (int f = 0; f < G->Filters_Size; f++)
    {
        // Call Vamana on the subset of points
        Vamana(file_path, G, L_small, R_small, a, f);
    }

    G->R = R_stitched;
    // Apply robust pruning to all nodes in the graph
    for (int v = 0; v < G->number_of_indexes; v++)
    {
        Filtered_Robust_Prune(v, (G->index_array[v].edges), a, G);
    }

    std::cout << "Stitched Vamana completed successfully." << std::endl;
    return 0;
}
