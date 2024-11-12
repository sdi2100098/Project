#include <algorithm>
#include "stdio.h"
#include <utility> // for std::pair
#include <cstring> // for perror
#include "fun.hpp"

void CreateKNNGraphBruteForce(Graph G, int k, const char *filename, const char *binary_filename)
{
    // Open the text output file
    FILE *output_file = fopen(filename, "w");
    if (output_file == NULL)
    {
        perror("Error opening text output file");
        return;
    }

    // Open the binary output file
    FILE *binary_file = fopen(binary_filename, "wb");
    if (binary_file == NULL)
    {
        perror("Error opening binary output file");
        fclose(output_file); // Close the text file if binary file opening fails
        return;
    }

    // Iterate through each node in the graph
    for (int i = 0; i < G.number_of_nodes; i++)
    {
        // Finding the closest neighbors of each node
        G.nodes_array[i].edges.clear();
        std::vector<std::pair<double, int>> closest_neighbors;

        for (int j = 0; j < G.number_of_nodes; j++)
        {
            if (i != j)
            {
                // Calculate the distance between node i and node j
                double distance = EuclideanDistance(G.nodes_array[i].vector, G.nodes_array[j].vector, G.dimension);
                closest_neighbors.push_back({distance, j});
            }
        }

        // Sort neighbors based on distance (ascending order)
        std::sort(closest_neighbors.begin(), closest_neighbors.end());
        // Write the k closest neighbors to the text and binary files
        for (int l = 0; l < k; l++)
        {
            int neighbor_index = closest_neighbors[l].second;

            // Write to text file
            fprintf(output_file, "%d ", neighbor_index);

            // Write to binary file (write each neighbor index as an integer)
            fwrite(&neighbor_index, sizeof(int), 1, binary_file);
        }

        // Newline for the next node in the text file
        fprintf(output_file, "\n\n");
    }

    // Close the files
    fclose(output_file);
    fclose(binary_file);
}
