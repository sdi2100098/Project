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

    int dimension = 100, number_of_indexes = 0,filter=0;
    float garbage = 0.0f,filter_float = 0.0f;
    node *index_array = NULL;
    std::set<int> Temp_Filters={};
    std::vector<int> *Filters = NULL;

    if(fread(&number_of_indexes,sizeof(int),1,file) != 1) goto fread_error;

    /* Alocate the nececery memmory */
    index_array = new node[number_of_indexes]();
    if(index_array == NULL) goto memmory_error;

    for(int i = 0; i < number_of_indexes; i++){
        index_array[i].vector = (float*)malloc(dimension * sizeof(float));
        if(index_array[i].vector == NULL) goto memmory_error;
    }


    /* Read the Data */
    for(int i = 0; i < number_of_indexes; i++){
        if(fread(&filter_float,sizeof(float),1,file) != 1) goto fread_error;
        
        filter = (int)filter_float;
        index_array[i].filter = filter;
        try{
            Temp_Filters.insert(filter);
        }
        catch(const std::bad_alloc &error){
            goto memmory_error;
        }
        
        if(fread(&garbage,sizeof(float),1,file) != 1) goto fread_error;
        if(fread(index_array[i].vector,sizeof(float),dimension,file) != (size_t)dimension) goto fread_error;
    }
       
    Filters = new std::vector<int>[Temp_Filters.size()]();

    for(int i = 0; i < number_of_indexes; i++){
        Filters[index_array[i].filter].push_back(i);
    }

    G->index_array = index_array;
    G->number_of_indexes = number_of_indexes;
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

int Init_Query_Data(Query *Q,const char *file_path,int number_of_filters){

    printf("Try to initialize the Query data...\n");

    FILE *file = fopen(file_path,"rb");
    if(file == NULL){
        perror("Error in Init_Query_Data (fopen)");
        return 1;
    }

    int Filters_Size = number_of_filters+1; //+1 to save nodes with no FILTER in the (number_of_filters) potition,(the last one)
    int dimension = 100, number_of_indexes = 0, No_filter_potition = number_of_filters, entry_potition = 0;
    float garbage_vector[dimension];

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

    std::vector<int> *Filters = NULL;
    query_node *index_array = NULL;

    try
    {
        Filters = new  std::vector<int>[Filters_Size];
    }
    catch(const std::bad_alloc &error)
    {
        goto memmory_error;
    }
   
    if(fread(&number_of_indexes,sizeof(int),1,file) != 1) goto fread_error;

    index_array = (query_node *)malloc(number_of_indexes * sizeof(query_node));
    if(index_array == NULL) goto memmory_error;

    /* Alocate memmory for the Query struct */
    for(int i = 0; i < number_of_indexes; i++){
        index_array[i].vector = (float *)malloc(dimension * sizeof(float));
        if(index_array[i].vector == NULL) goto memmory_error;
    }

    /* Time to read some data */
    for(int i = 0; i < number_of_indexes; i++){
        if(fread(&dimension_values,sizeof(Dimension_values),1,file) != 1) goto fread_error;
        
        /* skip the type 2,3 querys (we do not need them) */
        if(dimension_values.dimension_1 == 2.0f || dimension_values.dimension_1 == 3.0f || dimension_values.dimension_2 > (float)number_of_filters-1){ //in case exist filter with value more than 128
            if(fread(garbage_vector,sizeof(float),dimension,file) != (size_t)dimension) goto fread_error; //skip the vector
            continue;
        }

        /* if is type 0 ,I save it in Last potition of (Filters MAP),couse this mean i do not have filters */
        /* if is type 1 ,I save it in the (i-th) potition of (Filters MAP) */
        entry_potition = (dimension_values.dimension_1 == 0.0f) ? No_filter_potition : dimension_values.dimension_2;
    
        Filters[entry_potition].push_back(i);

        index_array[i].filter = (int)dimension_values.dimension_2;

        if(fread(index_array[i].vector,sizeof(float),dimension,file) != (size_t)dimension) goto fread_error;
    }

    Q->index_array = index_array;
    Q->number_of_indexes = number_of_indexes;
    Q->dimension = dimension;
    Q->Filters = Filters;
    Q->Filters_Size = Filters_Size;
    Q->NO_FILTERS_POTITION = No_filter_potition;

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
