#include "fun.hpp"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

int Vamana(const char *file_path, Graph *G, int L, int R, float a, int filter)
{
    int s, Random_Permutation_Index, Size;
    std::set<int> TempSet = {};
    std::vector<int> RandomPerm;
    Result_greedy *GreedyReturnValue = NULL; // Will have the L set and V set obtained from Greedy
    srand(time(NULL));
    s = Medoid(G,filter);                          // Use the slow medoid

    RandomPerm = RandomPermutation(G,true,filter);      // Get a Random Permutation

    for (int i = 0; i < (int)G->Filters[filter].size();i++)
    {
        Random_Permutation_Index = RandomPerm[i];
        GreedyReturnValue = Greedy_Search(G, Random_Permutation_Index, 1, L, s,NULL); // [L,V] <- GreedySearch(s,x_s(i),1,L)


        Robust_Prune(Random_Permutation_Index, &(GreedyReturnValue->V), a, G); // RobustPrune(σ(i),V,a,R)
        delete GreedyReturnValue;
        for (auto &j : G->index_array[Random_Permutation_Index].edges) // for all points j in Nout(σ(i))
        {
            TempSet.clear();
            for (auto &element : G->index_array[j].edges)
                TempSet.insert(element);
            TempSet.insert(Random_Permutation_Index); // If it exists in the set size remains the same else it increases by one
            Size = TempSet.size();

            if (Size > R)
            { // if |Nout(j) U {σ(i)}| > R
                Robust_Prune(j, &(TempSet), a, G);
            }
            else
                G->index_array[j].edges.insert(Random_Permutation_Index); // Nout(j) <- Nout(j) U σ(i)
        }
    }
    return s;
}