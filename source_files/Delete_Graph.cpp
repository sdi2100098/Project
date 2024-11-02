#include "Library.hpp"

void Delete_Graph(Graph *G)
{

    /* Free memmory for the struct (node) */
    for (int i = 0; i < G->number_of_nodes; i++)
    {
        free(G->nodes_array[i].vector);
        G->nodes_array[i].edges.clear();
    }

    free(G->nodes_array);
}

void Delete_Query(Query *Q)
{
    // Free memory for the query (float**)
    for (int i = 0; i < Q->number_of_vectors; i++)
    {
        free(Q->vectors_array[i]);
    }
    free(Q->vectors_array);
}

void Delete_GroundTruth(groundTruth *GT){
    // Free memory for the groundtruth (int**)
    for(int i = 0; i<GT->size; i++){
        free(GT->array[i]);
    }
    free(GT->array);
}