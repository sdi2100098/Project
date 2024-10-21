#include "Library.hpp"

int Medoid(Graph *G)
{
    double SumDistances, TempDistance, MinDistance = std::numeric_limits<double>::max();
    int MedoidIndex;
    std::vector<double> array(G->number_of_nodes, 0.0);
    for (int i = 0; i < G->number_of_nodes; i++)
    {
        SumDistances = 0.0;
        for (int j = 0; j < G->number_of_nodes; j++)
        {
            if (i == j)
                continue;
            TempDistance = EuclidianDistance(G->nodes_array[i].vector, G->nodes_array[j].vector, G->dimension);
            SumDistances += TempDistance;
        }
        array[i] = SumDistances;
    }

    for (int i = 0; i < G->number_of_nodes; i++)
    {
        if (array[i] < MinDistance)
        {
            MinDistance = array[i];
            MedoidIndex = i;
        }
    }

    return MedoidIndex;
}