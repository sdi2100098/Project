#include "Library.hpp"

void Delete_Graph(Graph *G)
{
    std::cout << "Free Memory for Graph" << std::endl;
    /* Free memmory for the struct (node) */
    for (int i = 0; i < G->number_of_nodes; i++)
    {
        delete[] (G->nodes_array[i].vector);
        delete[] (G->Distances[i]);
        G->nodes_array[i].edges.clear();
    }
    delete[] (G->Distances);
    delete[] (G->nodes_array);

}

void Delete_Query(Query *Q,int GraphSize)
{
    std::cout << "Free Memory for Query" << std::endl;
    // Free memory for the query (float**)
    for (int i = 0; i < Q->number_of_vectors; i++)
    {
        free(Q->vectors_array[i]);
    }
    for(int i = 0; i< GraphSize; i++)
        free(Q->Distances[i]);
        
    free(Q->Distances);

    free(Q->vectors_array);
}

void Delete_GroundTruth(groundTruth *GT)
{
    std::cout << "Free Memory for GroundTruth" << std::endl;
    // Free memory for the groundtruth (int**)
    for (int i = 0; i < GT->size; i++)
    {
        free(GT->array[i]);
    }
    free(GT->array);
}