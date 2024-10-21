#include "Library.hpp"

void Delete_Graph(Graph *G){

    /* Free memmory for the struct (node) */
    for(int i = 0; i < G->number_of_nodes; i++){
        free(G->nodes_array[i].vector);
        G->nodes_array[i].edges.clear();
    }

    free(G->nodes_array);
}