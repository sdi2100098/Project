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

    int dimension = 100, number_of_nodes = 0,filter=0;
    float garbage = 0.0f,filter_float = 0.0f;
    node *nodes_array = NULL;
    std::set<int> Temp_Filters={};
    std::vector<int> *Filters = NULL;

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
        if(fread(&filter_float,sizeof(float),1,file) != 1) goto fread_error;
        filter = (int)filter_float;
        nodes_array[i].filter = filter;
        try{
            Temp_Filters.insert(filter);
        }
        catch(const std::bad_alloc &error){
            goto memmory_error;
        }
        
        if(fread(&garbage,sizeof(float),1,file) != 1) goto fread_error;
        if(fread(nodes_array[i].vector,sizeof(float),dimension,file) != (size_t)dimension) goto fread_error;
    }   

    Filters = new std::vector<int>[Temp_Filters.size()]();

    for(int i = 0; i < number_of_nodes; i++){
        Filters[nodes_array[i].filter].push_back(i);
    }

    G->nodes_array = nodes_array;
    G->number_of_nodes = number_of_nodes;
    G->dimension = dimension;
    G->Filters_Size = (int)Temp_Filters.size();
    G->Filters = Filters;

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
