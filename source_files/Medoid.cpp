#include "Library.hpp"

int Medoid(Graph *G)
{
    double SumDistances, TempDistance, MinDistance = std::numeric_limits<double>::max();
    int MedoidIndex;
    std::vector<double> array(G->number_of_nodes, 0.0);
    for (int i = 0; i < G->number_of_nodes; i++) // For all vectors in Graph
    {
        SumDistances = 0.0;
        for (int j = 0; j < G->number_of_nodes; j++) // check for every vector in Graph except for yourself
        {
            if (i == j)
                continue;
            TempDistance = EuclidianDistance(G->nodes_array[i].vector, G->nodes_array[j].vector, G->dimension);
            SumDistances += TempDistance; // Sum all the distances and store it into a vector
        }
        array[i] = SumDistances;
    }

    for (int i = 0; i < G->number_of_nodes; i++)
    {
        if (array[i] < MinDistance)
        {
            MinDistance = array[i];
            MedoidIndex = i; // Hold the index of the vector with the smallest sum of distances to all the other vectors. Effectively finding the Medoid
        }
    }

    return MedoidIndex;
}