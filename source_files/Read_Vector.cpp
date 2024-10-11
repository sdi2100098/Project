#include "Library.hpp"

// Function to read fvecs file and save output to a readable text file
std::vector<std::vector<float>> fvecs_read(const std::string& filename, const std::string& output_filename, std::pair<int, int> bounds = {1, -1}) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "I/O error: Unable to open the file " << filename << std::endl;
        return {};
    }

    // Read the dimension of the vectors (int)
    int d;
    file.read(reinterpret_cast<char*>(&d), sizeof(int));  // Vector length (number of floats per vector)
    int vec_size_in_bytes = sizeof(int) + d * sizeof(float);  // Each vector: 1 int + d floats

    // Determine the total number of vectors in the file
    file.seekg(0, std::ios::end);
    int total_bytes = file.tellg();
    int total_vectors = total_bytes / vec_size_in_bytes;

    // Adjust the bounds (range of vectors to read)
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

    // Read vectors from the fvecs file
    for (int i = 0; i < num_vectors; ++i) {
        file.ignore(sizeof(int));  // Skip the dimension integer (already known)
        file.read(reinterpret_cast<char*>(vectors[i].data()), d * sizeof(float));  // Read the vector
    }

    file.close();

    // Write vectors and metadata (number of vectors, vector length) to a readable text file
    std::ofstream output_file(output_filename);
    if (!output_file.is_open()) {
        std::cerr << "I/O error: Unable to open the output file " << output_filename << std::endl;
        return {};
    }

    // Write the number of vectors and the length of each vector as the first two rows
    output_file << num_vectors << "\n";  // Number of vectors
    output_file << d << "\n";            // Length of each vector

    // Write the vectors to the file
    for (const auto& vec : vectors) {
        for (float val : vec) {
            output_file << val << " ";  // Write each value followed by a space
        }
        output_file << "\n";  // Newline after each vector
    }

    output_file.close();
    return vectors;
}