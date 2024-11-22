#include "struct.hpp"
#include "fun.hpp"

#include <stdio.h>
#include <stdlib.h>

int Init_Graph_Data(Graph *G, const char *file_path)
{

    // printf("Try to initialize the Graph data...\n");

    FILE *file = fopen(file_path, "rb");
    if (file == NULL)
    {
        perror("Error in Init_Graph_Data (fopen)");
        return 1;
    }

    int dimension = 100, number_of_indexes = 0, filter = 0;
    float garbage = 0.0f, filter_float = 0.0f;
    node *index_array = NULL;
    std::set<int> Temp_Filters = {};
    std::vector<int> *Filters = NULL;

    if (fread(&number_of_indexes, sizeof(int), 1, file) != 1)
        goto fread_error;

    /* Alocate the nececery memmory */
    index_array = new node[number_of_indexes]();
    if (index_array == NULL)
        goto memmory_error;

    for (int i = 0; i < number_of_indexes; i++)
    {
        index_array[i].vector = (float *)malloc(dimension * sizeof(float));
        if (index_array[i].vector == NULL)
            goto memmory_error;
    }

    /* Read the Data */
    for (int i = 0; i < number_of_indexes; i++)
    {
        if (fread(&filter_float, sizeof(float), 1, file) != 1)
            goto fread_error;

        filter = (int)filter_float;
        index_array[i].filter = filter;
        try
        {
            Temp_Filters.insert(filter);
        }
        catch (const std::bad_alloc &error)
        {
            goto memmory_error;
        }

        if (fread(&garbage, sizeof(float), 1, file) != 1)
            goto fread_error;
        if (fread(index_array[i].vector, sizeof(float), dimension, file) != (size_t)dimension)
            goto fread_error;
    }

    Filters = new std::vector<int>[Temp_Filters.size()]();

    for (int i = 0; i < number_of_indexes; i++)
    {
        Filters[index_array[i].filter].push_back(i);
    }

    G->index_array = index_array;
    G->number_of_indexes = number_of_indexes;
    G->dimension = dimension;
    G->Filters_Size = (int)Temp_Filters.size();
    G->Filters = Filters;

    fclose(file);
    // printf("Initialize the Graph data succefuly!\n");
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

typedef struct Dimension_values
{
    float d1;
    float d2;
    float d3;
    float d4;
} Dimension_values;

/* Go and find the Number of querys that we want to (only this with type 0 or 1) */
int Find_Usefull_NumberofIndexes(FILE *file, int *number_of_indexes, int number_of_filters, int dimension)
{

    int temp_indexes = 0;
    float vector[dimension];

    Dimension_values dimension_values{
        .d1 = -1.0f,
        .d2 = -1.0f,
        .d3 = -1.0f,
        .d4 = -1.0f};

    for (int i = 0; i < *number_of_indexes; i++)
    {

        if (fread(&dimension_values, sizeof(Dimension_values), 1, file) != 1)
            goto fread_error;
        if (fread(vector, sizeof(float), dimension, file) != (size_t)dimension)
            goto fread_error; // skip the vector

        if (dimension_values.d1 == 2.0f || dimension_values.d1 == 3.0f || dimension_values.d2 > (float)number_of_filters)
        { // in case exist filter with value more than 128
            continue;
        }

        temp_indexes++;
    }

    *number_of_indexes = temp_indexes;

    fseek(file, sizeof(int), SEEK_SET); /* Skip the first value */
    return 0;

fread_error:
    perror("Error in Find_Usefull_NumberofIndexes (fread_error)");
    return 1;
}

int Init_Query_Data(Query *Q, const char *file_path, int number_of_filters)
{

    // printf("Try to initialize the Query data...\n");

    FILE *file = fopen(file_path, "rb");
    if (file == NULL)
    {
        perror("Error in Init_Query_Data (fopen)");
        return 1;
    }

    int Filters_Size = number_of_filters + 1; //+1 to save nodes with no FILTER in the (number_of_filters) potition,(the last one)
    int dimension = 100, number_of_indexes = 0, No_filter_potition = number_of_filters, entry_potition = 0, usefull_number_of_indexes = 0, all_number_of_indexes;
    float garbage_vector[dimension];

    Dimension_values dimension_values{
        .d1 = -1.0f,
        .d2 = -1.0f,
        .d3 = -1.0f,
        .d4 = -1.0f};

    std::vector<int> *Filters = NULL;
    query_node *index_array = NULL;

    try
    {
        Filters = new std::vector<int>[Filters_Size];
    }
    catch (const std::bad_alloc &error)
    {
        goto memmory_error;
    }

    if (fread(&all_number_of_indexes, sizeof(int), 1, file) != 1)
        goto fread_error;
    number_of_indexes = all_number_of_indexes;
    if (Find_Usefull_NumberofIndexes(file, &number_of_indexes, number_of_filters, dimension) == 1)
        goto fread_error;

    index_array = (query_node *)malloc(number_of_indexes * sizeof(query_node));
    if (index_array == NULL)
        goto memmory_error;

    /* Alocate memmory for the Query struct */
    for (int i = 0; i < number_of_indexes; i++)
    {
        index_array[i].vector = (float *)malloc(dimension * sizeof(float));
        if (index_array[i].vector == NULL)
            goto memmory_error;
    }

    /* Time to read some data */
    for (int i = 0; i < all_number_of_indexes; i++, usefull_number_of_indexes++)
    {
        if (fread(&dimension_values, sizeof(Dimension_values), 1, file) != 1)
            goto fread_error;

        /* skip the type 2,3 querys (we do not need them) */
        if (dimension_values.d1 == 2.0f || dimension_values.d1 == 3.0f || dimension_values.d2 > (float)number_of_filters)
        { // in case exist filter with value more than 128
            if (fread(garbage_vector, sizeof(float), dimension, file) != (size_t)dimension)
                goto fread_error;        // skip the vector
            usefull_number_of_indexes--; // keep track only for the INDEX of the usefull Vectors
            continue;
        }

        /* if is type 0 ,I save it in Last potition of (Filters MAP),couse this mean i do not have filters */
        /* if is type 1 ,I save it in the (i-th) potition of (Filters MAP) */
        entry_potition = (dimension_values.d1 == 0.0f) ? No_filter_potition : dimension_values.d2;

        Filters[entry_potition].push_back(usefull_number_of_indexes);

        index_array[usefull_number_of_indexes].filter = (int)dimension_values.d2;

        if (fread(index_array[usefull_number_of_indexes].vector, sizeof(float), dimension, file) != (size_t)dimension)
            goto fread_error;
    }

    Q->index_array = index_array;
    Q->number_of_indexes = number_of_indexes;
    Q->dimension = dimension;
    Q->Filters = Filters;
    Q->Filters_Size = Filters_Size;
    Q->NO_FILTERS_POTITION = No_filter_potition;

    fclose(file);
    // printf("Initialize the Graph data succefuly!\n");
    return 0;

/* In case something goes wrong in (fread) */
fread_error:
    fclose(file);
    perror("Error in Init_Query_Data (fread)");
    return 1;

/* In case something goes wrong in (malloc,new) */
memmory_error:
    fclose(file);
    perror("Error in Init_Query_Data (new,malloc)");
    return 1;
}

int Init_Ground_Truth_Data(Ground_Truth *GT, const char *file_path)
{

    FILE *file = fopen(file_path, "rb");
    if (file == NULL)
    {
        perror("Error in Init_Ground_Truth (fopen)");
        return 1;
    }

    int filters, tottal_querys, index, K;
    int *Querys_with_Filter = NULL, *Actual_KNN_with_Filter = NULL;
    Neighbor *array = NULL;

    if (fread(&filters, sizeof(int), 1, file) != 1)
        goto fread_error;
    if (fread(&tottal_querys, sizeof(int), 1, file) != 1)
        goto fread_error;

    Querys_with_Filter = (int *)malloc(sizeof(int) * filters);
    if (Querys_with_Filter == NULL)
        goto memmory_error;

    Actual_KNN_with_Filter = (int *)malloc(sizeof(int) * filters);
    if (Actual_KNN_with_Filter == NULL)
        goto memmory_error;

    array = (Neighbor *)malloc(sizeof(Neighbor) * tottal_querys);
    if (array == NULL)
        goto memmory_error;

    if (fread(Querys_with_Filter, sizeof(int), filters, file) != (size_t)filters)
        goto fread_error;
    if (fread(Actual_KNN_with_Filter, sizeof(int), filters, file) != (size_t)filters)
        goto fread_error;

    /* Pao kai blepo kathe filtro posa stixiea query exei dioti tha kano loop osa einai ta stixia tou prokeimenoy na ginei sosta to malloc
    dioti ta Query pou exoun idio filtro exoun kai idio arithmo ACTUAL geitonon*/
    for (int i = 0; i < filters; i++)
    {
        for (int j = 0; j < Querys_with_Filter[i]; j++)
        {

            if (fread(&index, sizeof(int), 1, file) != 1)
                goto fread_error; /* Read the Query_index */
            K = Actual_KNN_with_Filter[i];

            array[index].K = K;
            array[index].K_NBH_array = (int *)malloc(sizeof(int) * K);
            if (array[index].K_NBH_array == NULL)
                goto memmory_error;

            if (fread(array[index].K_NBH_array, sizeof(int), K, file) != (size_t)K)
                goto fread_error; /* Read the Actual K closest neighbor (their INDEX) */
        }
    }

    GT->array = array;
    GT->Size = tottal_querys;

    free(Querys_with_Filter);
    free(Actual_KNN_with_Filter);

    fclose(file);
    return 0;

memmory_error:
    fclose(file);
    perror("Error in Init_Ground_Truth (new,malloc)");
    return 1;

fread_error:
    fclose(file);
    perror("Error in Init_Ground_Truth (fopen)");
    return 1;
}
