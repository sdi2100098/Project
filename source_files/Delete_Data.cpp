#include "struct.hpp"
#include "fun.hpp"

#include <stdlib.h>
#include <stdio.h>

void Delete_Graph(Graph *G){

    printf("Dealocate memmory for Graph!\n");

    for(int i = 0; i < G->number_of_nodes; i++){
        free(G->nodes_array[i].vector);
    }

    delete[] G->nodes_array;
    delete[] G->Filters;
}

void Delete_Query(Query *Q){

    printf("Dealocate memmory for Query!\n");

    for(int i = 0; i < Q->number_of_nodes; i++){
        free(Q->nodes_array[i].vector);
    }

    free(Q->nodes_array);
}
