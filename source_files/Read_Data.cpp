#include "struct.hpp"
#include "fun.hpp"

#include <stdio.h>
#include <stdlib.h>

int Init_Graph_Data(Graph *G,const char *file_path){

    printf("Try to initialize the Graph data...\n");

    FILE *file = fopen(file_path,"rb");
    if(file == NULL){
        perror("Error in Init_Graph_Data (fopen)");
        return 1;
    }

    int dimension = 100, number_of_nodes = 0;
    float garbage = 0.0f;
    node *nodes_array = NULL;

    if(fread(&number_of_nodes,sizeof(int),1,file) != 1) goto fread_error;

    /* Alocate the nececery memmory */
    nodes_array = new node[number_of_nodes]();
    if(nodes_array == NULL) goto memmory_error;

    for(int i = 0; i < number_of_nodes; i++){
        nodes_array[i].vector = (float*)malloc(dimension * sizeof(float));
        if(nodes_array[i].vector == NULL) goto memmory_error;
    }

    /* Read the Data */
    for(int i = 0; i < number_of_nodes; i++){
        if(fread(&(nodes_array[i].filter),sizeof(float),1,file) != 1) goto fread_error;
        if(fread(&garbage,sizeof(float),1,file) != 1) goto fread_error;
        if(fread(nodes_array[i].vector,sizeof(float),dimension,file) != (size_t)dimension) goto fread_error;
    }   

    G->nodes_array = nodes_array;
    G->number_of_nodes = number_of_nodes;
    G->dimension = dimension;

    fclose(file);
    return 0;

/* In case something goes wrong in (fread) */
fread_error:
    perror("Error in Init_Graph_Data (fread)");
    fclose(file);
    return 1;

memmory_error:
    perror("Error in Init_Graph_Data (new,malloc)");
    fclose(file);
    return 1;
}
