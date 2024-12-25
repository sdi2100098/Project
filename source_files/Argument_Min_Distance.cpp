#include "fun.hpp"
#include <limits>
#include <iostream>
#include <unistd.h>

int Argument_Min_Distance(Graph *G, Query *Q, std::set<int> *Argument_Set, int x, float *Distances)
{
    //
    int min_index = -1;
    float min_distance, temp_distance, *vector_1, *vector_2;
    min_distance = std::numeric_limits<float>::max();
    // Finding from the set the node with the smallest distance and returning it's location on the graph
    for (std::set<int>::iterator it = Argument_Set->begin(); it != Argument_Set->end(); it++)
    {
        vector_1 = G->index_array[*it].vector;
        vector_2 = (Q == NULL) ? G->index_array[x].vector : Q->index_array[x].vector;
        temp_distance = Distance_Function(Distances, vector_1, vector_2, *it, G->dimension);

        if (temp_distance < min_distance)
        {
            min_distance = temp_distance;
            min_index = *it;
        }
    }
    return min_index;
}