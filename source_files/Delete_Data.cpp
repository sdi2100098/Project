#include "struct.hpp"
#include "fun.hpp"

#include <stdlib.h>
#include <stdio.h>

void Delete_Graph(Graph *G){

    printf("Dealocate memmory for Graph!\n");

    for(int i = 0; i < G->number_of_indexes; i++){
        free(G->index_array[i].vector);
    }

    delete[] G->index_array;
    delete[] G->Filters;
}

void Delete_Query(Query *Q){

    printf("Dealocate memmory for Query!\n");

    for(int i = 0; i < Q->number_of_indexes; i++){
        free(Q->index_array[i].vector);
    }

    free(Q->index_array);
    delete [] Q->Filters;
}
