#include "fun.hpp"
#include <limits>
#include <iostream>
#include <unistd.h>

int Argument_Min_Distance(Graph *G, Query *Q, std::set<int> *Argument_Set, int x)
{
    int min_index = -1, first_index, second_index;
    float min_distance, temp_distance;
    min_distance = std::numeric_limits<float>::max();
    // Finding from the set the node with the smallest distance and returning it's location on the graph
    for (std::set<int>::iterator it = Argument_Set->begin(); it != Argument_Set->end(); it++)
    {
        first_index = (x >= (*it)) ? x : (*it);
        second_index = (first_index == x) ? (*it) : x;
        temp_distance = (Q == NULL) ? G->memo.Distances[first_index][second_index] : Q->memo.Distances[*it][x];

        if (temp_distance < min_distance)
        {
            min_distance = temp_distance;
            min_index = *it;
        }
    }
    return min_index;
}