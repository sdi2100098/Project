#include "Library.hpp"

int main(void){

    const char *input_filename = "/root/Project/Project1/Project-1/Datasets/siftsmall_base.fvecs";
    int count = 0;
    float **vectors_base ;
    float **vectors_query;
    int *num_vectors = (int*) malloc(2*sizeof(int));
    int *vector_dim = (int*) malloc(2*sizeof(int));


    vectors_base = Read_Data(input_filename, &num_vectors[count], &vector_dim[count]);


    printf("METADATA rows:%d colums:%d\n",num_vectors[0],vector_dim[0]);

    for(int i = 0; i < 10; i++){
        printf("\n");
        for(int j = 0; j < vector_dim[0]; j++){
            printf("%.4f ",vectors_base[i][j]);
        }
    }


    // Read the vectors using the fvecs_read function
    // while (count < 2) {
    //     //std::cout << "Give path for file : " ; // Here the path is given from the user
    //     //std::cin >> input_filename;
    //     //scanf("%s",input_filename);
    //     if(!count)
    //         vectors_base = Read_Data(input_filename, &num_vectors[count], &vector_dim[count]);
    //     else
    //         vectors_query = Read_Data(input_filename, &num_vectors[count], &vector_dim[count]);
    //     if(!vectors_base || !vectors_query){ // In case the pointer is null print error message and retake the path
    //         return 1;
    //     }
    //     count ++;
    // }


    //std::cout << vectors_base[0][0] << std::endl << vectors_query[0][0]<<std::endl ;
    return 0;
}