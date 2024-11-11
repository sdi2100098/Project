#include "struct.hpp"
#include "fun.hpp"

#include <stdlib.h>
#include <stdio.h>

void Delete_Graph(Graph *G){

    printf("Dealocate memmory for Graph!\n");

    for(int i = 0; i < G->number_of_nodes; i++){
        free(G->nodes_array[i].vector);
        G->nodes_array[i].edges.clear();
    }

    delete[] G->nodes_array;

}