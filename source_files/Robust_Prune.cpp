#include "Library.hpp"

void Robust_Prune(int p, std::set<int> *V, float a, Graph *G)
{

    int p_star, p_tonos;
    double min_distance, temp_distance;

    std::set<int> Temp_V = {};

    /* V <- (V U Nout(p)) \ {p} */
    for (std::set<int>::iterator it = G->nodes_array[p].edges.begin(); it != G->nodes_array[p].edges.end(); it++)
        V->insert(*it);
    V->erase(p);

    /* Nout(p) <- 0 */
    G->nodes_array[p].edges.clear();

    while (V->size() != 0)
    { /* V != 0 */

        /* p* <- arg min[for p'in V compute d(p,p')] */
        p_star = Argument_Min_Distance(G, V, p,NULL);

        G->nodes_array[p].edges.insert(p_star); /* Nout(p) <- Nout(p) U {p*} */

        if ((int)G->nodes_array[p].edges.size() == G->R)
            break; /* |Nout(p)| = R */

        Temp_V.clear();
        for (std::set<int>::iterator it = V->begin(); it != V->end(); it++)
        {
            Temp_V.insert(*it);
        }

        for (std::set<int>::iterator it = Temp_V.begin(); it != Temp_V.end(); it++)
        {
            if ((a * G->Distances[p_star][*it]) <= G->Distances[p][*it])
            {
                V->erase(*it);
            }
        }
    }
}