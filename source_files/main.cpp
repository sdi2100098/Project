#include "Library.hpp"

int main(void){

    std::string input_filename = "Datasets/siftsmall_base.fvecs";
    std::string output_filename = "siftsmall_base.txt";
    int count = 0;
    float ***vectors = (float***) malloc(2*sizeof(float **));
    int *num_vectors = (int*) malloc(2*sizeof(int));
    int *vector_dim = (int*) malloc(2*sizeof(int));

    // Read the vectors using the fvecs_read function
    while (count < 2) {
        if (count == 1){
            input_filename = "Datasets/siftsmall_query.fvecs";
            output_filename = "siftsmall_query.txt";
        }
        vectors[count] = fvecs_read(input_filename, num_vectors[count], vector_dim[count],{1, -1});
        WriteToTxtFile(vectors[count],output_filename,num_vectors[count],vector_dim[count]);
        count ++;
    }
    std::cout << *vectors[0][0] << std::endl << *(vectors+1)[0][0]<<std::endl ;
    return 0;
}