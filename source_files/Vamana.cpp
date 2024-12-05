#include "fun.hpp"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>


int Vamana( Graph *G, int L, int R, float a, int filter,bool test)
{
    if(test){
        G->kappa = 0;
        G->flag = 0;
    }
    int s, Random_Permutation_Index, Size, Random_Num, Random_Index;
    std::set<int> TempSet = {};
    std::vector<int> RandomPerm;
    Result_greedy *GreedyReturnValue = NULL; // Will have the L set and V set obtained from Greedy

    G->R = R;

    for (int i = 0; i < (int)G->Filters[filter].size(); i++)
    {
        G->index_array[G->Filters[filter][i]].edges = {};
        while (G->index_array[G->Filters[filter][i]].edges.size() < (size_t)R)
        {
            Random_Index = rand() % (int)G->Filters[filter].size();
            Random_Num = G->Filters[filter][Random_Index];
            G->index_array[G->Filters[filter][i]].edges.insert(Random_Num);
            if ((int)G->Filters[filter].size() < R && (int)G->index_array[G->Filters[filter][i]].edges.size() == (int)G->Filters[filter].size())
                break;
        }
    }
    s = Medoid(G, filter); // Use the slow medoid

    RandomPerm = RandomPermutation(G, true, filter); // Get a Random Permutation

    for (int i = 0; i < (int)G->Filters[filter].size(); i++ , G->kappa ++)
    {   
        if (G->kappa == G->flag)
        {
            printf("%.0f %% ", ((float)(G->flag + 1) / G->number_of_indexes) * 100);
            fflush(stdout);
            G->flag += 1000;
        }
        Random_Permutation_Index = RandomPerm[i];

        GreedyReturnValue = Greedy_Search(G, Random_Permutation_Index, 1, L, s, NULL); // [L,V] <- GreedySearch(s,x_s(i),1,L)

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