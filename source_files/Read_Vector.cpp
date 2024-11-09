#include "Library.hpp"

/* Function to read fvecs file using dynamically allocated arrays.If something goes wrong return NULL and exit the program else return the vector array */
int Init_Graph_Data(const char *file_path, Graph *graph)
{
    std::cout << "Try Initializing Graph..." << std::endl;
    FILE *infile = fopen(file_path, "rb");

    if (infile == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    int dimension, garbage, random_number, vectors_number;
    size_t result_fread;
    long total_size_bytes, vecsize_bytes;
    node *nodes_array = NULL;
    double **Distances_array = NULL;

    /* read dimension and compute the byte size of a vector */
    result_fread = fread(&dimension, sizeof(int), 1, infile);
    if (result_fread != 1)
        goto fread_error;

    vecsize_bytes = (sizeof(float) * (dimension)) + sizeof(int);

    /* compute the size of the file in bytes and find the number of vectors */
    fseek(infile, 0, SEEK_END);
    total_size_bytes = ftell(infile);
    vectors_number = total_size_bytes / vecsize_bytes;

    /* fvecs, create the graph */

    /* alocate memmory for the (nodes_array) */
    nodes_array = (node *)malloc(vectors_number * sizeof(node));
    if (nodes_array == NULL)
        goto memmory_error;

    Distances_array = (double **)malloc(vectors_number * sizeof(double *));
    if (Distances_array == NULL)
        goto memmory_error;

    /* for every node in nodes_array alocate memory for the vector and for the edges*/
    for (int i = 0; i < vectors_number; i++)
    {
        nodes_array[i].vector = (float *)malloc(dimension * sizeof(float));
        if (nodes_array[i].vector == NULL)
            goto memmory_error;
        Distances_array[i] = (double *)malloc(vectors_number * sizeof(double));
        if (Distances_array[i] == NULL)
            goto memmory_error;
    }

    /* Initilize the Struct */
    fseek(infile, 0, SEEK_SET);
    for (int i = 0; i < vectors_number; i++)
    {
        result_fread = fread(&garbage, sizeof(int), 1, infile);
        if (result_fread != 1)
            goto fread_error;

        result_fread = fread(nodes_array[i].vector, sizeof(float), dimension, infile);
        if (result_fread != dimension)
            goto fread_error;
    }

    graph->nodes_array = nodes_array;
    graph->Distances = Distances_array;
    graph->number_of_nodes = vectors_number;
    graph->dimension = dimension;

    for (int index = 0; index < graph->number_of_nodes; index++)
    {
        graph->nodes_array[index].edges = {}; // we need to Initialize the set . Otherwise we have undefined behaviour
        while ((int)graph->nodes_array[index].edges.size() < graph->R)
        {                                                                   // while the size of set is smaller than R
            random_number = GetRandomNumber(graph->number_of_nodes, index); // min = 0, max = number of Vectors, number to exclude is the index of the current node
            try
            {
                graph->nodes_array[index].edges.insert(random_number); // insert the element
            }
            catch (const std::bad_alloc &error)
            {
                goto memmory_error;
            }
        }
    }

    /* All went well well */
    fclose(infile);
    std::cout << "Initialize Graph Complete!" << std::endl;
    return 0;

/* ERRORS AREA */

/* in case something goes wrong with memory */
memmory_error:
    fclose(infile);
    perror("No memmory in FUN(Init_Graph_Data)");
    return 1;

/* in case something goes wrong with fread */
fread_error:
    fclose(infile);
    perror("Fread error in FUN(Init_Graph_Data)");
    return 1;
}

/*
Read the Query Data from the file and Initilize the Query struct so we can use it in our program
If all goes good return 0 else return 1
*/
int Init_Query_Data(const char *file_path, Query *query,Graph *G)
{
    std::cout << "Try Initializing Query..." << std::endl;
    FILE *infile = fopen(file_path, "rb");

    if (infile == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    /* alocate memmory for the vectors */
    float **vectors_array ;
    double **distances;
    int dimension, garbage, number_of_vectors,tempDist;
    long vecsize_bytes;
    long total_size_bytes;

    /* read dimension and compute the byte size of a vector */
    if(fread(&dimension, sizeof(int), 1, infile)!=1){
        goto memmory_error;
    }

    /* compute the size of the file in bytes and find the number of vectors */
    fseek(infile, 0, SEEK_END);
    total_size_bytes = ftell(infile);
    vecsize_bytes  = (sizeof(float) * (dimension)) + sizeof(int);
    number_of_vectors = total_size_bytes / vecsize_bytes;

    vectors_array = (float **)malloc(sizeof(float *) * number_of_vectors);

    distances = (double **)malloc(sizeof(double *) * G->number_of_nodes);
    if (vectors_array == NULL)
        goto memmory_error;

    if(distances == NULL)
        goto memmory_error;

    for (int i = 0; i < number_of_vectors; i++)
    {
        vectors_array[i] = (float *)malloc(sizeof(float) * dimension);
        if (vectors_array[i] == NULL)
            goto memmory_error;
    }

    for(int i = 0; i < G->number_of_nodes; i++){
        distances[i] = (double *)malloc(sizeof(double) * number_of_vectors);
        if(distances[i] == NULL)
            goto memmory_error;
    }

    /* Initilize the Struct */
    fseek(infile, 0, SEEK_SET);
    for (int i = 0; i < number_of_vectors; i++)
    {
        if(fread(&garbage, sizeof(int), 1, infile)!=1)
            goto fread_error;
        if(fread(vectors_array[i], sizeof(float), dimension, infile)!=dimension){
            goto fread_error;
        }
    }

    query->vectors_array = vectors_array;
    query->Distances = distances;
    query->dimension = dimension;
    query->number_of_vectors = number_of_vectors;

    for(int i = 0; i < G->number_of_nodes; i++){
        for(int j = 0; j<number_of_vectors; j++){
            tempDist = EuclidianDistance(G->nodes_array[i].vector,query->vectors_array[j],query->dimension);
            query->Distances[i][j] = tempDist;
        }
    }

    /* All went well well */
    fclose(infile);
    std::cout << "Initialize Query Complete!" << std::endl;
    return 0;

/* in case something goes wrong with memory */
/* in case something goes wrong with memory */
memmory_error:
    fclose(infile);
    perror("No memmory in FUN(Init_Graph_Data)");
    return 1;

/* in case something goes wrong with fread */
fread_error:
    fclose(infile);
    perror("Fread error in FUN(Init_Graph_Data)");
    return 1;
}

std::vector<std::vector<int>> ReadFileTXT(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Error opening File");
        return {};
    }

    char line[256];
    std::vector<std::vector<int>> info;

    while (fgets(line, sizeof(line), file))
    {
        std::vector<int> row;

        std::istringstream iss(line);
        int number;
        while (iss >> number)
            row.push_back(number);

        info.push_back(row);
    }
    fclose(file);
    return info;
}

int Init_Ground_Truth_Data(const char *file_path, groundTruth *GT)
{
    std::cout << "Try Initializing GroundTruth..." << std::endl;
    FILE *infile = fopen(file_path, "rb");
    if (infile == NULL)
    {
        perror("Error opening Ground Truth");
        return 1;
    }
    int size, garbage;
    int **array = NULL;

    if(fread(&size, sizeof(int), 1, infile)!=1)
        goto memmory_error;
    fseek(infile, 0, SEEK_SET);

    array = (int **)malloc(sizeof(int *) * size);
    if (array == NULL)
    {
        perror("Allocation error in Init Ground Truth Data");
        fclose(infile);
        return 1;
    }
    for (int i = 0; i < size; i++)
    {
        array[i] = (int *)malloc(sizeof(int) * size);
        if (array[i] == NULL)
        {
            perror("Allocation error in Init Ground Truth Data");
            fclose(infile);
            return 1;
        }
    }

    for (int i = 0; i < size; i++)
    {
        if(fread(&garbage, sizeof(int), 1, infile)!=1)
            goto fread_error;
        if(fread(array[i], sizeof(int), size, infile)!=size)
            goto fread_error;
    }

    GT->array = array;
    GT->size = size;

    fclose(infile);
    std::cout << "Initialize GroundTruth Complete!" << std::endl;
    return 0;

/* in case something goes wrong with memory */
memmory_error:
    fclose(infile);
    perror("No memmory in FUN(Init_Graph_Data)");
    return 1;

/* in case something goes wrong with fread */
fread_error:
    fclose(infile);
    perror("Fread error in FUN(Init_Graph_Data)");
    return 1;
}