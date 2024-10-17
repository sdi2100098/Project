#include "Library.hpp"

/* Function to read fvecs file using dynamically allocated arrays.If something goes wrong return NULL and exit the program else return the vector array */
int Init_Graph_Data(const char *file_path, Graph *graph){

    FILE *infile = fopen(file_path,"rb");

    if(infile == NULL){
        perror("Error opening file");
        return 1;
    }

    int dimension, garbage,random_number;

    /* read dimension and compute the byte size of a vector */
    fread(&dimension,sizeof(int),1,infile);
    long vecsize_bytes = (sizeof(float) * (dimension)) + sizeof(int);

    /* compute the size of the file in bytes and find the number of vectors */
    fseek(infile, 0, SEEK_END);
    long total_size_bytes = ftell(infile);
    int vectors_number = total_size_bytes / vecsize_bytes;



    /* fvecs, create the graph */
    
    /* alocate memmory for the (nodes_array) */
    node* nodes_array = (node*)malloc(vectors_number * sizeof(node));
    if(nodes_array == NULL) goto memmory_error;

    /* for every node in nodes_array alocate memory for the vector and for the edges*/
    for(int i = 0; i < vectors_number; i++){
        nodes_array[i].vector = (float *)malloc(dimension * sizeof(float));
        if(nodes_array[i].vector == NULL) goto memmory_error;
        // nodes_array[i].edges = (int *)malloc(graph->R * sizeof(int));
        // if(nodes_array[i].edges == NULL) goto memmory_error;
    }

    /* Initilize the Struct */
    fseek(infile, 0, SEEK_SET);
    for(int i = 0; i < vectors_number; i++){
        fread(&garbage,sizeof(int),1,infile);
        fread(nodes_array[i].vector,sizeof(float),dimension,infile);
    }


    graph->nodes_array = nodes_array;
    graph->number_of_nodes = vectors_number;
    graph->dimension = dimension;

    srand(time(NULL)); // make the seed
    for(int index = 0; index < graph->number_of_nodes; index++){
        graph->nodes_array[index].edges = {}; // we need to Initialize the set . Otherwise we have undefined behaviour
        while(graph->nodes_array[index].edges.size() < graph->R){ // while the size of set is smaller than R
            random_number = GetRandomNumber(graph->number_of_nodes,index); // min = 0, max = number of Vectors, number to exclude is the index of the current node
            try{
                graph->nodes_array[index].edges.insert(random_number); // insert the element
            }catch(const std::bad_alloc& error){goto memmory_error;}
        }
    }

    /* All went well well */
    fclose(infile);
    return 0; 

    /* in case something goes wrong with memory */
    memmory_error:

    fclose(infile);
    perror("No memmory");
    return 1;
}

/*
Read the Query Data from the file and Initilize the Query struct so we can use it in our program 
If all goes good return 0 else return 1
*/
int Init_Query_Data(const char *file_path, Query *query){

    FILE *infile = fopen(file_path,"rb");

    if(infile == NULL){
        perror("Error opening file");
        return 1;
    }

    int dimension, garbage, number_of_vectors;

    /* read dimension and compute the byte size of a vector */
    fread(&dimension,sizeof(int),1,infile);
    long vecsize_bytes = (sizeof(float) * (dimension)) + sizeof(int);

    /* compute the size of the file in bytes and find the number of vectors */
    fseek(infile, 0, SEEK_END);
    long total_size_bytes = ftell(infile);
    number_of_vectors = total_size_bytes / vecsize_bytes;

    /* alocate memmory for the vectors */
    float **vectors_array = (float **)malloc(sizeof(float*) * number_of_vectors);
    if(vectors_array == NULL) goto memmory_error;

    for(int i = 0; i < number_of_vectors; i++){
        vectors_array[i] = (float *)malloc(sizeof(float) * dimension);
        if(vectors_array[i] == NULL) goto memmory_error;
    }

    /* Initilize the Struct */
    fseek(infile, 0, SEEK_SET);
    for(int i = 0; i < number_of_vectors; i++){
        fread(&garbage,sizeof(int),1,infile);
        fread(vectors_array[i],sizeof(float),dimension,infile);
    }

    query->vectors_array = vectors_array;
    query->dimension = dimension;
    query->number_of_vectors = number_of_vectors;

    /* All went well well */
    fclose(infile);
    return 0; 

    /* in case something goes wrong with memory */
    memmory_error:

    fclose(infile);
    perror("No memmory");
    return 1;
}