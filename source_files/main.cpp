#include <iostream>
#include "Library.hpp"

int main(void){

    // Example usage:
    std::string input_filename = "Datasets/siftsmall_base.fvecs";
    std::string output_filename = "output.txt";
    
    // Read vectors and write to text file
    fvecs_read(input_filename, output_filename, {1, -1});  // Read all vectors
    std::cout << "Vectors have been written to " << output_filename << std::endl;
    std::cout << "Hello" << std::endl;
    return 0;
}