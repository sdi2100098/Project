#include "fun.hpp"
#include <iostream>
#include <stdlib.h>
//

Result_greedy *Greedy_Search(Graph *G, int xq, int k, int L, int s, Query *Q, float *Distances)
{

    /* Initialize L <- {s} and V <- 0 */
    std::set<std::pair<float, int>> L_kal = {{0.0f, s}};
    std::set<std::pair<float, int>> Temp = {{}};
    std::set<int> V = {};
    std::set<int> Difference_L_V = {s};

    int p_star, i;
    float distance, *vector_1, *vector_2;

    /* while L\V != 0 */
    while (Difference_L_V.size() != 0)
    {
        i = 0;

        /* p* <- atg min d(Xp,Xq) for p in L\V */
        p_star = Argument_Min_Distance(G, Q, &Difference_L_V, xq, Distances);

        /* L <- L U Nout(p*) (with the distances)*/
        for (std::set<int>::iterator it = G->index_array[p_star].edges.begin(); it != G->index_array[p_star].edges.end(); it++)
        {

            vector_1 = G->index_array[*it].vector;
            vector_2 = (Q == NULL) ? G->index_array[xq].vector : Q->index_array[xq].vector;
            distance = Distance_Function(Distances, vector_1, vector_2, *it, G->dimension);

            L_kal.insert({distance, (*it)});
        }

        /* V <- V U {p*} */
        V.insert(p_star);

        /* |L kaligrafiko| > L */
        if ((int)L_kal.size() > L)
        {

            Temp.clear();
            /* L kaligrafiko retain closest L points to Xq */
            for (std::set<std::pair<float, int>>::iterator it = L_kal.begin(); it != L_kal.end() && i < L; i++, it++)
            {
                Temp.insert({it->first, it->second});
            }

            L_kal.clear();
            for (std::set<std::pair<float, int>>::iterator it = Temp.begin(); it != Temp.end(); it++)
            {
                L_kal.insert({it->first, it->second});
            }
        }

        Difference_L_V.clear();
        Set_Difference(&L_kal, &V, &Difference_L_V);
    }

    Result_greedy *RG = new Result_greedy;

    i = 0;
    /* closect k points from L kaligrafiko + V */
    for (std::set<std::pair<float, int>>::iterator it = L_kal.begin(); it != L_kal.end() && i < k; i++, it++)
    {
        RG->L.insert({it->first, it->second});
    }
    RG->V = V;

    return RG;
}