#include "fun.hpp"

result_greedy *Greedy_Search(Graph *G, int xq, int k, int L, int *s, Query *Q)
{

    /* Initialize L <- 0 and V <- 0 */
    std::set<std::pair<double, int>> L_kal = {{0, 0}};
    std::set<std::pair<double, int>> Temp = {{}};
    std::set<int> V = {};
    std::set<int> Difference_L_V = {};

    int p_star, i;
    double distance;
    float *vector;

    if (!Q)
        vector = G->index_array[xq].vector;
    else
        vector = Q->index_array[xq].vector;

    /* while L\V != 0 */
    while (Difference_L_V.size() != 0)
    {
        i = 0;

        /* p* <- atg min d(Xp,Xq) for p in L\V */
        p_star = Argument_Min_Distance(G, &Difference_L_V, vector);

        /* L <- L U Nout(p*) (with the distances)*/
        for (std::set<int>::iterator it = G->index_array[p_star].edges.begin(); it != G->index_array[p_star].edges.end(); it++)
        {

            distance = EuclideanDistance(G->index_array[*it].vector, vector, G->dimension);
            L_kal.insert({distance, *it});
        }

        /* V <- V U {p*} */
        V.insert(p_star);

        /* |L kaligrafiko| > L */
        if ((int)L_kal.size() > L)
        {

            Temp.clear();
            /* L kaligrafiko retain closest L points to Xq */
            for (std::set<std::pair<double, int>>::iterator it = L_kal.begin(); it != L_kal.end() && i < L; i++, it++)
            {
                Temp.insert({it->first, it->second});
            }

            L_kal.clear();
            for (std::set<std::pair<double, int>>::iterator it = Temp.begin(); it != Temp.end(); it++)
            {
                L_kal.insert({it->first, it->second});
            }
        }
        Difference_L_V.clear();
        Set_Difference(&L_kal, &V, &Difference_L_V);
    }

    result_greedy *RG = new result_greedy;
    RG->L = {};

    i = 0;
    /* closect k points from L kaligrafiko + V */
    for (std::set<std::pair<double, int>>::iterator it = L_kal.begin(); it != L_kal.end() && i < k; i++, it++)
    {
        RG->L.insert({it->first, it->second});
    }
    RG->V = V;

    return RG;
}