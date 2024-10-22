#include "Library.hpp"

int Argument_Min_Distance(Graph *G, std::set<int> *Argument_Set, float *Arg_1)
{
    int min_index;
    double min_distance, temp_distance;
    min_distance = std::numeric_limits<double>::max();

    for (std::set<int>::iterator it = Argument_Set->begin(); it != Argument_Set->end(); it++)
    {
        temp_distance = EuclidianDistance(Arg_1, G->nodes_array[*it].vector, G->dimension);
        if (temp_distance < min_distance)
        {
            min_distance = temp_distance;
            min_index = *it;
        }
    }
    return min_index;
}