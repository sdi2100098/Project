#include "struct.hpp"
#include "fun.hpp"

#include <stdlib.h>
#include <stdio.h>

void Delete_Graph(Graph *G, bool Precompute_Done)
{
    // printf("Dealocate memmory for Graph!\n");

    for (int i = 0; i < G->number_of_indexes; i++)
        free(G->index_array[i].vector);

    delete[] G->index_array;
    delete[] G->Filters;

    if (!Precompute_Done)
        return;

    for (int i = 0; i < G->memo.rows; i++)
        free(G->memo.Distances[i]);

    free(G->memo.Distances);
}

void Delete_Query(Query *Q, bool Precompute_Done)
{

    // printf("Dealocate memmory for Query!\n");

    for (int i = 0; i < Q->number_of_indexes; i++)
        free(Q->index_array[i].vector);

    free(Q->index_array);
    delete[] Q->Filters;

    if (!Precompute_Done)
        return;

    for (int i = 0; i < Q->memo.rows; i++)
        free(Q->memo.Distances[i]);

    free(Q->memo.Distances);
}

void Delete_Ground_Truth(Ground_Truth *GT)
{

    // printf("Dealocate memmory for Ground Truth!\n");

    for (int i = 0; i < GT->Size; i++)
    {
        free(GT->array[i].K_NBH_array);
    }

    free(GT->array);
}
