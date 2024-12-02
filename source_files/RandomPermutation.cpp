#include "struct.hpp"
#include "stdlib.h"

std::vector<int> RandomPermutation(Graph *G, bool Is_stitch, int filter)
{
    int maxVal = (Is_stitch == true) ? G->Filters[filter].size() : G->number_of_indexes; // Total number of nodes
    std::vector<int> permutation(maxVal);                                                // Vector to store the permutation

    // Fill the vector with the values 0 to maxVal-1
    for (int i = 0; i < maxVal; i++)
        permutation[i] = (Is_stitch == false) ? i : G->Filters[filter][i];
    for (int i = maxVal - 1; i > 0; i--)
    {
        // Generate a random number in the range [0, i]
        int j = rand() % (i + 1);
        std::swap(permutation[i], permutation[j]); // Swap the current element with a random earlier element
    }

    return permutation; // Return the random permutation
}