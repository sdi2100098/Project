#include "Library.hpp"

int main(void){

    std::string input_filename;
    int count = 0;
    float **vectors_base ;
    float **vectors_query;
    int *num_vectors = (int*) malloc(2*sizeof(int));
    int *vector_dim = (int*) malloc(2*sizeof(int));

    // Read the vectors using the fvecs_read function
    while (count < 2) {
        std::cout << "Give path for file : " ; // Here the path is given from the user
        std::cin >> input_filename;
        if(!count)
            vectors_base = fvecs_read(input_filename, num_vectors[count], vector_dim[count],{1, -1});
        else
            vectors_query = fvecs_read(input_filename, num_vectors[count], vector_dim[count],{1, -1});
        if(!vectors_base || !vectors_query){ // In case the pointer is null print error message and retake the path
            std::cout << "You gave wrong path. Please try again!"<<std::endl;
            count--;
        }
        count ++;
    }
    std::cout << vectors_base[0][0] << std::endl << vectors_query[0][0]<<std::endl ;
    return 0;
}