#include "fun.hpp"
#include <limits>

int Argument_Min_Distance(Graph *G, Query *Q ,std::set<int> *Argument_Set, int x)
{
    int min_index = -1;
    double min_distance, temp_distance;
    min_distance = std::numeric_limits<double>::max();
    // Finding from the set the node with the smallest distance and returning it's location on the graph
    for (std::set<int>::iterator it = Argument_Set->begin(); it != Argument_Set->end(); it++)
    {
        temp_distance = (Q == NULL) ? G->memo.Distances[*it][x] : Q->memo.Distances[*it][x];

        if (temp_distance < min_distance)
        {
            min_distance = temp_distance;
            min_index = *it;
        }
    }
    return min_index;
}