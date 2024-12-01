#include "fun.hpp"
#include <iostream>
#include <stdlib.h>

void Robust_Prune(int p, std::set<int> *V, float a, Graph *G)
{

    int p_star, first_calc_first_index, first_calc_second_index, second_calc_first_index, second_calc_second_index;

    std::set<int> Temp_V = {};

    /* V <- (V U Nout(p)) \ {p} */
    for (std::set<int>::iterator it = G->index_array[p].edges.begin(); it != G->index_array[p].edges.end(); it++)
        V->insert(*it);
    V->erase(p);

    /* Nout(p) <- 0 */
    G->index_array[p].edges.clear();

    while (V->size() != 0)
    { /* V != 0 */

        /* p* <- arg min[for p'in V compute d(p,p')] */
        p_star = Argument_Min_Distance(G, NULL, V, p);

        G->index_array[p].edges.insert(p_star); /* Nout(p) <- Nout(p) U {p*} */

        if ((int)G->index_array[p].edges.size() == G->R)
            break; /* |Nout(p)| = R */

        Temp_V.clear();
        for (std::set<int>::iterator it = V->begin(); it != V->end(); it++)
        {
            Temp_V.insert(*it);
        }

        for (std::set<int>::iterator it = Temp_V.begin(); it != Temp_V.end(); it++)
        {
            first_calc_first_index = (p_star >= (*it)) ? p_star : (*it);
            first_calc_second_index = (first_calc_first_index == p_star) ? (*it) : p_star;
            second_calc_first_index = (p >= (*it)) ? p : (*it);
            second_calc_second_index = (second_calc_first_index == p) ? (*it) : p;

            if ((a * G->memo.Distances[first_calc_first_index][first_calc_second_index]) <= G->memo.Distances[second_calc_first_index][second_calc_second_index])
            {
                V->erase(*it);
            }
        }
    }
}