#include "Library.hpp"

int Vamana(const char *file_path, Graph *G, int L, int R)
{
    int result, s, Random_Permutation_Index, Size;
    float a = 1.1;
    int k = 2;
    float *vector;
    std::vector<int> RandomPerm;
    result_greedy *GreedyReturnValue = NULL; // Will have the L set and V set obtained from Greedy

    G->R = R;
    result = Init_Graph_Data(file_path, G); // Create a random R-regular directed graph
    s = Medoid(G); //Use the slow medoid
    RandomPerm = RandomPermutation(G); // Get a Random Permutation

    for (int i = 0; i < G->number_of_nodes; i++)
    {
        Random_Permutation_Index = RandomPerm[i];
        vector = G->nodes_array[Random_Permutation_Index].vector;
        GreedyReturnValue = Greedy_Search(G, vector, k, L, s);                 // [L,V] <- GreedySearch(s,x_s(i),1,L)
        Robust_Prune(Random_Permutation_Index, &(GreedyReturnValue->V), a, G); // RobustPrune(σ(i),V,a,R)
        for (auto &j : G->nodes_array[Random_Permutation_Index].edges)         // for all points j in Nout(σ(i))
        {
            GreedyReturnValue->V = G->nodes_array[j].edges;
            GreedyReturnValue->V.insert(Random_Permutation_Index); // If it exists in the set size remains the same else it increases by one
            Size = GreedyReturnValue->V.size();

            if (Size > R) // if |Nout(j) U {σ(i)}| > R
                Robust_Prune(j, &(GreedyReturnValue->V), a, G);
            else
                G->nodes_array[j].edges.insert(Random_Permutation_Index); // Nout(j) <- Nout(j) U σ(i)
        }
    }
    delete GreedyReturnValue;
    return result;
}