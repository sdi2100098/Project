#include "Library.hpp"
int WriteToTxtFile(float **vectors,std::string& output_filename,int &num_vectors,int &vector_dim){
    if (!vectors) {
            std::cerr << "Error reading fvecs file." << std::endl;
            return 1;
        }

        // Open the output file and write the results
        std::ofstream output_file(output_filename);
        output_file.precision(7);  // Set precision for floating point numbers
        output_file << num_vectors << " " << vector_dim << "\n";  // Write the number of vectors and their dimension

        for (int i = 0; i < num_vectors; ++i) {
            for (int j = 0; j < vector_dim; ++j) {
                output_file << vectors[i][j] << " ";  // Write each value followed by a space
            }
            output_file << "\n";  // Newline after each vector
        }

        output_file.close();

        // Free the allocated memory
        free_fvecs(vectors, num_vectors);
        return 0;
}