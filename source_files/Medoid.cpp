#include "fun.hpp"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <limits>

int Medoid(Graph *G, int filter)
{
    float SumDistances, MinDistance = std::numeric_limits<float>::max();
    int MedoidIndex = -1;
    std::vector<float> array(G->Filters[filter].size(), 0.0f);
    for (int i = 0; i < (int)G->Filters[filter].size(); i++)
    {
        SumDistances = 0.0f;
        for (int j = 0; j < (int)G->Filters[filter].size(); j++)
            SumDistances += EuclideanDistance(G->index_array[G->Filters[filter][i]].vector,G->index_array[G->Filters[filter][j]].vector,G->dimension);

        array[i] = SumDistances;
    }

    for (int i = 0; i < (int)G->Filters[filter].size(); i++)
    {
        if (array[i] < MinDistance)
        {
            MinDistance = array[i];
            MedoidIndex = G->Filters[filter][i]; // Hold the index of the vector with the smallest sum of distances to all the other vectors. Effectively finding the Medoid
        }
    }
    return MedoidIndex;
}