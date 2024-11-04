#include "Library.hpp"

int Vamana(const char *file_path, Graph *G, int L, int R)
{
    int result, s, Random_Permutation_Index, Size;
    std::set<int> TempSet = {};
    float a = 1.1;
    float *vector;
    std::vector<int> RandomPerm;
    result_greedy *GreedyReturnValue = NULL; // Will have the L set and V set obtained from Greedy
    srand(time(NULL));
    G->R = R;
    result = Init_Graph_Data(file_path, G); // Create a random R-regular directed graph
    s = Medoid(G);                          // Use the slow medoid
    RandomPerm = RandomPermutation(G);      // Get a Random Permutation

    int flag = 1000, kapa = 0;

    std::cout << "Vamana Start" << std::endl;
    for (int i = 0; i < G->number_of_nodes; i++)
    {
        Random_Permutation_Index = RandomPerm[i];
        GreedyReturnValue = Greedy_Search(G, Random_Permutation_Index, 1, L, s,NULL); // [L,V] <- GreedySearch(s,x_s(i),1,L)

        kapa++;
        if (kapa == flag)
        {
            printf("%.0f%%\n", ((double)flag/ G->number_of_nodes) * 100);
            flag += 1000;
        }

        Robust_Prune(Random_Permutation_Index, &(GreedyReturnValue->V), a, G); // RobustPrune(σ(i),V,a,R)
        delete GreedyReturnValue;
        for (auto &j : G->nodes_array[Random_Permutation_Index].edges) // for all points j in Nout(σ(i))
        {
            TempSet.clear();
            for (auto &element : G->nodes_array[j].edges)
                TempSet.insert(element);
            TempSet.insert(Random_Permutation_Index); // If it exists in the set size remains the same else it increases by one
            Size = TempSet.size();

            if (Size > R)
            { // if |Nout(j) U {σ(i)}| > R
                Robust_Prune(j, &(TempSet), a, G);
            }
            else
                G->nodes_array[j].edges.insert(Random_Permutation_Index); // Nout(j) <- Nout(j) U σ(i)
        }
    }
    std::cout << "Vamana Ended Succesfully" << std::endl;
    return s;
}