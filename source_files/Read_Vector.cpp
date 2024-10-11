#include "Library.hpp"
// Function to read fvecs file using dynamically allocated arrays
float** fvecs_read(const std::string& filename, int& num_vectors, int& vector_dim, std::pair<int, int> bounds = {1, -1}) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "I/O error: Unable to open the file " << filename << std::endl;
        return nullptr;
    }

    // Read the dimension of the vectors (int)
    int d;
    file.read(reinterpret_cast<char*>(&d), sizeof(int));
    int vec_size_in_bytes = sizeof(int) + d * sizeof(float);
    vector_dim = d;  // Save the vector dimension for later use

    // Determine the number of vectors in the file
    file.seekg(0, std::ios::end);
    int total_bytes = file.tellg();
    int total_vectors = total_bytes / vec_size_in_bytes;

    // Adjust the bounds
    int start_idx = bounds.first;
    int end_idx = (bounds.second == -1) ? total_vectors : bounds.second;

    // Ensure valid indices
    assert(start_idx >= 1 && end_idx <= total_vectors);
    if (end_idx < start_idx) {
        std::cerr << "Invalid range: end index is less than start index." << std::endl;
        return nullptr;
    }

    num_vectors = end_idx - start_idx + 1;

    // Move to the starting position
    file.seekg((start_idx - 1) * vec_size_in_bytes, std::ios::beg);

    // Allocate memory for the array of pointers (each pointing to a vector)
    float** vectors = (float**)malloc(num_vectors * sizeof(float*));
    if (!vectors) {
        std::cerr << "Memory allocation error for vectors array." << std::endl;
        file.close();
        return nullptr;
    }

    // Allocate and read each vector
    for (int i = 0; i < num_vectors; ++i) {
        // Allocate memory for each vector (of size d)
        vectors[i] = (float*)malloc(d * sizeof(float));
        if (!vectors[i]) {
            std::cerr << "Memory allocation error for vector " << i << std::endl;
            // Free already allocated memory in case of failure
            for (int j = 0; j < i; ++j) {
                free(vectors[j]);
            }
            free(vectors);
            file.close();
            return nullptr;
        }

        // Skip the dimension integer (already known)
        file.ignore(sizeof(int));

        // Read the vector of floats
        file.read(reinterpret_cast<char*>(vectors[i]), d * sizeof(float));
    }

    file.close();
    return vectors;
}

// Function to free the dynamically allocated memory
void free_fvecs(float** vectors, int num_vectors) {
    for (int i = 0; i < num_vectors; ++i) {
        free(vectors[i]);
    }
    free(vectors);
}