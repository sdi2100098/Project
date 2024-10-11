#include <iostream>
#include "Library.hpp"

int main(void){

    // Example usage:
    std::vector<std::vector<float>> vectors;
    std::vector<float> myvector;
    std::string input_filename = "Datasets/siftsmall_base.fvecs";
    std::string output_filename = "siftsmall_base.txt";
    
    // Read vectors and write to text file
    vectors = fvecs_read(input_filename, output_filename, {1, -1});  // Read all vectors
    myvector = vectors.front();
    std::cout << "Vectors have been written to " << output_filename << std::endl;
    std::cout << myvector.front() << std::endl;
    return 0;
}