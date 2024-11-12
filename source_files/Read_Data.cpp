#include "struct.hpp"
#include "fun.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

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
    printf("Initialize the Graph data succefuly!\n");
    return 0;

/* In case something goes wrong in (fread) */
fread_error:
    perror("Error in Init_Graph_Data (fread)");
    fclose(file);
    return 1;

/* In case something goes wrong in (malloc,new) */
memmory_error:
    perror("Error in Init_Graph_Data (new,malloc)");
    fclose(file);
    return 1;
}

int Init_Query_Data(Query *Q,const char *file_path){

    printf("Try to initialize the Query data...\n");

    FILE *file = fopen(file_path,"rb");
    if(file == NULL){
        perror("Error in Init_Query_Data (fopen)");
        return 1;
    }

    int dimension = 100, number_of_nodes = 100, garbage = 0;

    typedef struct Dimension_values{
        float dimension_1;
        float dimension_2;
        float dimension_3;
        float dimension_4;
    }Dimension_values;

    Dimension_values dimension_values{
        .dimension_1 = -1.0f,
        .dimension_2 = -1.0f,
        .dimension_3 = -1.0f,
        .dimension_4 = -1.0f
    };

    query_node *nodes_array = (query_node *)malloc(number_of_nodes * sizeof(query_node));
    if(nodes_array == NULL) goto memmory_error;

    /* Alocate memmory for the Query struct */
    for(int i = 0; i < number_of_nodes; i++){
        nodes_array[i].vector = (float *)malloc(dimension * sizeof(float));
        if(nodes_array[i].vector == NULL) goto memmory_error;
    }

    /* Time to read some data */
    if(fread(&garbage,sizeof(int),1,file) != 1) goto fread_error;

    /* Time to read some right data */
    for(int i = 0; i < number_of_nodes; i++){
        if(fread(&dimension_values,sizeof(Dimension_values),1,file) != 1) goto fread_error;
        nodes_array[i].filter = (int)dimension_values.dimension_2;
        if(fread(nodes_array[i].vector,sizeof(float),dimension,file) != (size_t)dimension) goto fread_error;
    }

    Q->nodes_array = nodes_array;
    Q->number_of_nodes = number_of_nodes;
    Q->dimension = dimension;

    fclose(file);
    printf("Initialize the Graph data succefuly!\n");
    return 0;

/* In case something goes wrong in (fread) */
fread_error:
    fclose(file);
    perror("Error in Init_Query_Data (fread)");
    return 1;

/* In case something goes wrong in (malloc,new) */
memmory_error:
    fclose(file);
    perror("Error in Init_Graph_Data (new,malloc)");
    return 1;
}
