#include "Library.hpp"

int Vamana(const char *file_path, Graph *G, int L, int R)
{
    const char *query_filename = "Datasets/Small_Set/siftsmall_query.fvecs";
    const char *ground_truth_filename = "Datasets/Small_Set/siftsmall_groundtruth.ivecs";
    int result, s, Random_Permutation_Index, Size;
    std::set<int> TempSet={};
    float a = 1.2;
    int k = 100;
    float *vector;
    std::vector<int> RandomPerm;
    result_greedy *GreedyReturnValue = NULL; // Will have the L set and V set obtained from Greedy

    G->R = R;
    result = Init_Graph_Data(file_path, G); // Create a random R-regular directed graph
    //s = Medoid(G);
    s = 8736;                          // Use the slow medoid
    RandomPerm = RandomPermutation(G);      // Get a Random Permutation

    int flag = 1000, kapa = 0;

    for (int i = 0; i < G->number_of_nodes; i++)
    {
        Random_Permutation_Index = RandomPerm[i];
        vector = G->nodes_array[Random_Permutation_Index].vector;
        GreedyReturnValue = Greedy_Search(G, vector, 1, L, s); // [L,V] <- GreedySearch(s,x_s(i),1,L)

        kapa++;
        if(kapa == flag){
            printf("%d\n",flag);
            flag += 1000;
        }


        Robust_Prune(Random_Permutation_Index, &(GreedyReturnValue->V), a, G); // RobustPrune(σ(i),V,a,R)
        delete GreedyReturnValue;
        for (auto &j : G->nodes_array[Random_Permutation_Index].edges)         // for all points j in Nout(σ(i))
        {
            TempSet = G->nodes_array[j].edges;
            TempSet.insert(Random_Permutation_Index); // If it exists in the set size remains the same else it increases by one
            Size = TempSet.size();

            if (Size > R){ // if |Nout(j) U {σ(i)}| > R
                Robust_Prune(j, &(TempSet), a, G);
                G->nodes_array[j].edges.clear();
                G->nodes_array[j].edges = TempSet;
            }
            else
                G->nodes_array[j].edges.insert(Random_Permutation_Index); // Nout(j) <- Nout(j) U σ(i)
        }
    }
    result = GroundTruth(query_filename,ground_truth_filename,G,100,15,s);
    return result;
}