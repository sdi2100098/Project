#include "fun.hpp"
#include <time.h>
#include <stdlib.h>
#include <iostream>

#define Flag 999
#define Kappa 0

int StichedVamana( Graph *G, int L_small, int R_small, int R_stitched, double a)
{
    srand(time(NULL));
    G->kappa =Kappa;
    G->flag = Flag;
    std::cout << "\nSTART STITCHED VAMANA"<<std::endl;
    fflush(stdout);
    std::cout << "PROGRESS : ";
    fflush(stdout);
    // Create a stitched graph over points
    for (int f = 0; f < G->Filters_Size; f++)
    {
        // Call Vamana on the subset of points
        Vamana( G, L_small, R_small, a, f,false);
    }

    G->R = R_stitched;
    // Apply robust pruning to all nodes in the graph
    for (int v = 0; v < G->number_of_indexes; v++)
    {
        Filtered_Robust_Prune(v, (G->index_array[v].edges), a, G);
    }

    std::cout << "\nEND STITCHED VAMANA" << std::endl;
    fflush(stdout);
    return 0;
}
