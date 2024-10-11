#include <iostream>
#include "Library.hpp"

int main(void){

    std::string filename = "Datasets/siftsmall_base.fvecs";
    
    // // Read all vectors
    // std::vector<std::vector<float>> vectors = fvecs_read(filename);

    // Example of reading a specific range of vectors (e.g., from 5 to 10)
    std::pair<int, int> range = {5, 10};
    std::vector<std::vector<float>> vectors_in_range = fvecs_read(filename, range);

    // Example of printing the first vector
    if (!vectors_in_range.empty()) {
        for (const auto& value : vectors_in_range[0]) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}