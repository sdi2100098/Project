#include "fun.hpp"
#include <time.h>
#include <stdlib.h>
#include <iostream>
#define Flag 999
#define Kappa 0

int *Filtered_Vamana(Graph *G, int L, int R, double a)
{
    int RandomPermutationIndex, Size;
    int *s = NULL;
    int threshold = 1;
    std::vector<int> RandomPerm;
    std::set<int> TempSet = {};
    Result_greedy *result_greedy = NULL;
    
    G->kappa =Kappa;
    G->flag = Flag;

    
    G->R = R;

    srand(time(NULL));

    /*Let s denote the Medoid of P*/
    s = FindMedoid(G, threshold);

    /*Let σ denote be a random permutation of [n] */
    RandomPerm = RandomPermutation(G, false, -1);

    std::cout << "\nSTART FILTERED VAMANA"<<std::endl;
    fflush(stdout);
    std::cout << "PROGRESS : ";
    fflush(stdout);
    for (int i = 0; i < G->number_of_indexes; i++, G->kappa++)
    {

        if (G->kappa == G->flag)
        {
            printf("%.0f %% ", ((float)(G->flag + 1) / G->number_of_indexes) * 100);
            fflush(stdout);
            G->flag += 1000;
        }

        RandomPermutationIndex = RandomPerm[i];
        /*Let SF_x_σ(i) = {st(f) : f ε F_x_σ(i) }*/

        /*Let [0;VF_x_σ(i)] <-- FilteredGreedySearch(SF_x_σ(i),x_σ(i),0,L,F_x_σ(i))*/
        result_greedy = Filtered_Greedy_Search(G, RandomPermutationIndex, 0, L, s, NULL);

        /*Run FilteredRobustPrune(σ(i),VF_x_σ(i),a,R) to update out-neighbors of σ(i)*/
        Filtered_Robust_Prune(RandomPermutationIndex, (result_greedy->V), a, G);

        for (auto &j : G->index_array[RandomPermutationIndex].edges)
        {
            TempSet.clear();
            for (auto &element : G->index_array[j].edges)
                TempSet.insert(element);
            TempSet.insert(RandomPermutationIndex);
            Size = (int)TempSet.size();

            if (Size > R)
                /*Run FilteredRobustPrune(j,Nout(j),a,R) to update out-neighbors of j*/;
            Filtered_Robust_Prune(j, (TempSet), a, G);
        }
        // delete STRUCT
        delete result_greedy;
    }
    std::cout << "\nEND FILTERED VAMANA" << std::endl;
    fflush(stdout);
    return s;
}
