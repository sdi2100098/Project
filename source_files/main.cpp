#include "Library.hpp"

int main(){

    const char *input_filename = "Datasets/siftsmall_base.fvecs";
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
    // Sample example for the Euclidian Distance
    float vector_1[3] = {5,3,0};
    float vector_2[3] = {2,-2,sqrt(2)};
    float distance = 0.0;
    distance = EuclidianDistance(vector_1,vector_2,3);
    std::cout << std::endl << "Calculate distance for two different vectors : ";
    std::cout << distance << std::endl;
    return 0;
}