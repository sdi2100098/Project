#include "fun.hpp"
#include <time.h>
#include <stdlib.h>
#include <iostream>

int *Filtered_Vamana(const char *file_path, Graph *G, int L, int R, double a)
{
    int RandomPermutationIndex, result, Size;
    int *s = NULL;
    int threshold = 1;
    std::vector<int> RandomPerm;
    std::set<int> TempSet = {};
    Result_greedy *result_greedy = NULL;

    /*Initialize G to an Empty Graph*/
    result = Init_Graph_Data(G, file_path, true);
    if (result == 1)
    {
        perror("Error in Init_Graph");
        return NULL;
    }
    G->R = R;

    /*Let s denote the Medoid of P*/
    s = FindMedoid(G, threshold);

    /*Let σ denote be a random permutation of [n] */
    RandomPerm = RandomPermutation(G);

    int flag = 999, kappa = 0;
    for (int i = 0; i < G->number_of_indexes; i++, kappa++)
    {

        if (kappa == flag)
        {
            printf("%.0f %%\n", ((float)(flag + 1) / G->number_of_indexes) * 100);
            flag += 1000;
        }

        RandomPermutationIndex = RandomPerm[i];
        /*Let SF_x_σ(i) = {st(f) : f ε F_x_σ(i) }*/

        /*Let [0;VF_x_σ(i)] <-- FilteredGreedySearch(SF_x_σ(i),x_σ(i),0,L,F_x_σ(i))*/
        result_greedy = Filtered_Greedy_Search(G, RandomPermutationIndex, 0, L, s, NULL);

        /*Run FilteredRobustPrune(σ(i),VF_x_σ(i),a,R) to update out-neighbors of σ(i)*/
        Filtered_Robust_Prune(RandomPermutationIndex, &(result_greedy->V), a, G);

        for (auto &j : G->index_array[RandomPermutationIndex].edges)
        {
            TempSet.clear();
            for (auto &element : G->index_array[j].edges)
                TempSet.insert(element);
            TempSet.insert(RandomPermutationIndex);
            Size = (int)TempSet.size();

            if (Size > R)
                /*Run FilteredRobustPrune(j,Nout(j),a,R) to update out-neighbors of j*/;
            Filtered_Robust_Prune(j, &(TempSet), a, G);
        }
        // delete STRUCT
        delete result_greedy;
    }

    return s;
}
