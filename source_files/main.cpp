#include "Library.hpp"

int main(void){

    std::string input_filename = "Datasets/siftsmall_base.fvecs";
    std::string output_filename = "siftsmall_base.txt";
    
    int num_vectors=0;
    int vector_dim=0;

    // Read the vectors using the fvecs_read function

    float** vectors = fvecs_read(input_filename, num_vectors, vector_dim,{1, -1});
    WriteToTxtFile(vectors,output_filename,num_vectors,vector_dim);
    
    return 0;
}