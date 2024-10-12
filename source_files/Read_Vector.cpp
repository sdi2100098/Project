#include "Library.hpp"

/* Function to read fvecs file using dynamically allocated arrays.If something goes wrong return NULL and exit the program else return the vector array */
float **Read_Data(const char *file_path, int *rows, int *columns){

    FILE *infile = fopen(file_path,"rb");

    *rows = 0;
    *columns = 0;

    if(infile == NULL){
        perror("Error opening file");
        return NULL;
    }

    int dimantion, garbage;

    /* read dimantion and compute the byte size of a vector */
    fread(&dimantion,sizeof(int),1,infile);
    *columns = dimantion;
    unsigned int vecsize_bytes = sizeof(float) * (dimantion+1);

    /* compute the size of the file in bytes and find the number of vectors */
    fseek(infile, 0, SEEK_END);
    int total_size_bytes = ftell(infile);
    int vectors_number = total_size_bytes / vecsize_bytes;
    *rows = vectors_number;

    /* alocate memmory for the vectors */
    float **vector_arr = (float **)malloc(sizeof(float*) * vectors_number);
    if(vector_arr == NULL)
        goto memmory_error;

    for(int i = 0; i < vectors_number; i++){
        vector_arr[i] = (float *)malloc(sizeof(float) * dimantion);
        if(vector_arr[i] == NULL) 
            goto memmory_error;
    }

    /* read the vectors and store it but ignore the dimantion */
    fseek(infile, 0, SEEK_SET);
    for(int i = 0; i < vectors_number; i++){
        fread(&garbage,sizeof(int),1,infile);
        fread(vector_arr[i],sizeof(float),dimantion,infile);
    }

    fclose(infile);
    return vector_arr;

    /* in case something goes wrong with memory */
    memmory_error:

    fclose(infile);
    perror("No memmory");
    return NULL;
}