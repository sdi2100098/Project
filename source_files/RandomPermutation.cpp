#include "Library.hpp"

// NOTE : Needs fixing since We don't check if random Number exists in permuation table. Maybe do it with vector to check faster and easier
int *RandomPermutation(Graph *G){
    int *permutation = (int*)malloc(G->number_of_nodes * sizeof(int)); 
    int maxVal = G->number_of_nodes;
    int randomNumber;
    for (int index = 0; index < maxVal; index ++){
        randomNumber = GetRandomNumber(maxVal,index); // Get a random index but exclude the same index
        permutation[index] = randomNumber;
    }
    return permutation;
}