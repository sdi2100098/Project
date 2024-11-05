#include "Library.hpp"

int Argument_Min_Distance(Graph *G, std::set<int> *Argument_Set, int Arg_1,Query *Q)
{
    int min_index;
    double min_distance, temp_distance;
    min_distance = std::numeric_limits<double>::max();
    // Finding from the set the node with the smallest distance and returning it's location on the graph
    for (std::set<int>::iterator it = Argument_Set->begin(); it != Argument_Set->end(); it++)
    {
        if(!Q)
            temp_distance = G->Distances[*it][Arg_1];
        else
            temp_distance = Q->Distances[*it][Arg_1];
        if (temp_distance < min_distance)
        {
            min_distance = temp_distance;
            min_index = *it;
        }
    }
    return min_index;
}