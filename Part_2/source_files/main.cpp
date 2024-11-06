#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cstdint>

int main() {
    // Specify file paths
    const char* binFilename = "dummy-data.bin";  // Binary file input
    const char* txtFilename = "output.txt";   // Text file output

    // Open the binary file in binary mode
    std::ifstream binFile(binFilename, std::ios::binary);
    if (!binFile.is_open()) {
        std::cerr << "Error: Could not open the binary file " << binFilename << std::endl;
        return 1;
    }

    // Read the number of vectors (4 bytes)
    uint32_t num_vectors = 0;
    binFile.read(reinterpret_cast<char*>(&num_vectors), sizeof(num_vectors));

    // Constants for vector dimensions and attributes
    const int vector_num_dimensions = 102;
    const int vector_data_size = vector_num_dimensions * sizeof(float);

    // Open the text file for output
    std::ofstream txtFile(txtFilename);
    if (!txtFile.is_open()) {
        std::cerr << "Error: Could not create the output text file " << txtFilename << std::endl;
        return 1;
    }

    // Write the number of vectors to the text file
    txtFile << "Number of vectors: " << num_vectors << "\n\n";

    // Buffer to store one vector's data (102 float32 values)
    std::vector<float> vector_data(vector_num_dimensions);

    // Loop over each vector and read its data
    for (uint32_t i = 0; i < num_vectors; ++i) {
        // Read 102 float values for the current vector
        binFile.read(reinterpret_cast<char*>(vector_data.data()), vector_data_size);

        // Check if the read was successful
        if (!binFile) {
            std::cerr << "Error reading vector data for vector #" << i << std::endl;
            break;
        }

        // Write vector data to the text file
        txtFile << "Vector #" << i + 1 << ":\n";
        txtFile << "  C (Categorical Attribute): " << vector_data[0] << "\n";
        txtFile << "  T (Timestamp Attribute): " << vector_data[1] << "\n";
        txtFile << "  Vector (100 dimensions): [";
        
        // Output the 100-dimensional vector in a formatted way
        for (int j = 2; j < vector_num_dimensions; ++j) {
            txtFile << std::fixed << std::setprecision(6) << vector_data[j];
            if (j < vector_num_dimensions - 1) {
                txtFile << ", ";
            }
        }
        txtFile << "]\n\n";
    }

    // Close the files
    binFile.close();
    txtFile.close();

    std::cout << "Data successfully saved to " << txtFilename << std::endl;

    return 0;
}
