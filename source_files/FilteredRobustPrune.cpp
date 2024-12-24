#include "fun.hpp"
#include <stdlib.h>
#include <iostream>

void Filtered_Robust_Prune(int p, std::set<int> V, float a, Graph *G,float *Distances)
{
    int p_star;

    std::set<int> Temp_V;

    /* V <- (V U Nout(p)) \ {p} */
    for (std::set<int>::iterator it = G->index_array[p].edges.begin(); it != G->index_array[p].edges.end(); it++)
        V.insert(*it);
    V.erase(p);

    /* Nout(p) <- 0 */
    G->index_array[p].edges.clear();

    while (V.size() != 0)
    { /* V != 0 */

        /* p* <- arg min[for p'in V compute d(p,p')] */
        p_star = Argument_Min_Distance(G, NULL, &V, p,Distances,false);

        G->index_array[p].edges.insert(p_star); /* Nout(p) <- Nout(p) U {p*} */

        if ((int)G->index_array[p].edges.size() == G->R) /* |Nout(p)| = R */
            break;

        Temp_V.clear();
        for (std::set<int>::iterator it = V.begin(); it != V.end(); it++)
        {
            Temp_V.insert(*it);
        }

        for (std::set<int>::iterator it = Temp_V.begin(); it != Temp_V.end(); it++)
        {
            /* if Fp'∩ Fp not ⊂ Fp* then continue */
            if (G->index_array[p].filter == G->index_array[*it].filter && G->index_array[p].filter != G->index_array[p_star].filter)
                continue;

            if ((a * EuclideanDistance(G->index_array[p_star].vector,G->index_array[*it].vector,G->dimension)) <= EuclideanDistance(G->index_array[p].vector,G->index_array[*it].vector,G->dimension))
            {
                V.erase(*it);
            }
        }
    }
}
