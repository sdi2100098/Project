#include "Library.hpp"

std::vector<std::vector<float>> fvecs_read(const std::string& filename, std::pair<int, int> bounds = {1, -1}) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "I/O error: Unable to open the file " << filename << std::endl;
        return {};
    }

    // Read the dimension of the vectors (int)
    int d;
    file.read(reinterpret_cast<char*>(&d), sizeof(int));
    int vec_size_in_bytes = sizeof(int) + d * sizeof(float);

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
        return {};
    }

    int num_vectors = end_idx - start_idx + 1;

    // Move to the starting position
    file.seekg((start_idx - 1) * vec_size_in_bytes, std::ios::beg);

    // Prepare to store the vectors
    std::vector<std::vector<float>> vectors(num_vectors, std::vector<float>(d));

    for (int i = 0; i < num_vectors; ++i) {
        // Skip the dimension integer (already known)
        file.ignore(sizeof(int));

        // Read the vector of floats
        file.read(reinterpret_cast<char*>(vectors[i].data()), d * sizeof(float));
    }

    file.close();
    return vectors;
}
