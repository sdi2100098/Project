#include "Library.hpp"

int main(void){

    std::string input_filename = "Datasets/siftsmall_base.fvecs";
    std::string output_filename = "siftsmall_base.txt";
    int count = 0;
    float **vectors_base ;
    float **vectors_query;
    int *num_vectors = (int*) malloc(2*sizeof(int));
    int *vector_dim = (int*) malloc(2*sizeof(int));

    // Read the vectors using the fvecs_read function
    while (count < 2) {
        if (count == 1){
            input_filename = "Datasets/siftsmall_query.fvecs";
            output_filename = "siftsmall_query.txt";
        }
        if(!count)
            vectors_base = fvecs_read(input_filename, num_vectors[count], vector_dim[count],{1, -1});
        else
            vectors_query = fvecs_read(input_filename, num_vectors[count], vector_dim[count],{1, -1});
        count ++;
    }
    std::cout << vectors_base[0][0] << std::endl << vectors_query[0][0]<<std::endl ;
    return 0;
}