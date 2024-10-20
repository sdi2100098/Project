#include "Library.hpp"

void Robust_Prune(int p, std::set<int> &V, float a, Graph *G){

    int p_star;
    double min_distance, temp_distance;

    /* V <- (V U Nout(p)) \ {p} */
    for (auto it = G->nodes_array[p].edges.begin(); it != G->nodes_array[p].edges.end(); it++)
        V.insert(*it);
    V.erase(p);

    /* Nout(p) <- 0 */
    G->nodes_array[p].edges.clear();

    while (V.size() != 0) { /* V != 0 */

        min_distance = std::numeric_limits<double>::infinity();
        
        // Find the closest node in V
        for (auto p_tonos : V) {
            temp_distance = EuclidianDistance(G->nodes_array[p_tonos].vector, G->nodes_array[p].vector, G->dimension);
            if (min_distance > temp_distance) {
                min_distance = temp_distance;
                p_star = p_tonos;
            }
        }

        // Add p_star to the edges of node p
        G->nodes_array[p].edges.insert(p_star); /* Nout(p) <- Nout(p) U {p*} */

        if (G->nodes_array[p].edges.size() == G->R) 
            break; /* |Nout(p)| = R */

        // Safely erase elements from V while iterating
        for (auto p_tonos = V.begin(); p_tonos != V.end(); /* no increment here */) {
            if ((a * EuclidianDistance(G->nodes_array[p_star].vector, G->nodes_array[*p_tonos].vector, G->dimension))
                <= EuclidianDistance(G->nodes_array[p].vector, G->nodes_array[*p_tonos].vector, G->dimension)) {
                p_tonos = V.erase(p_tonos); // erase returns the next valid iterator
            } else {
                ++p_tonos; // increment only if not erasing
            }
        }
    }
}
