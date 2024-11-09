#include "Library.hpp"

int Medoid(Graph *G)
{
    std::cout << "Calculating Medoid..." << std::endl;
    double SumDistances, TempDistance, MinDistance = std::numeric_limits<double>::max();
    int MedoidIndex;
    std::vector<double> array(G->number_of_nodes, 0.0);
    for (int i = 0; i < G->number_of_nodes; i++) // For all vectors in Graph
    {
        SumDistances = 0.0;
        for (int j = 0; j < G->number_of_nodes; j++) // check for every vector in Graph except for yourself
        {
            if (j < i)
                TempDistance = G->Distances[i][j];
            if (i == j)
            {
                G->Distances[i][j] = 0.0;
                continue;
            }
            else
            {
                TempDistance = EuclidianDistance(G->nodes_array[i].vector, G->nodes_array[j].vector, G->dimension);
                G->Distances[i][j] = TempDistance;
                G->Distances[j][i] = TempDistance;
            }
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
    std::cout << "Medoid is : " << MedoidIndex << std::endl;
    return MedoidIndex;
}