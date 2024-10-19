#include "acutest.h"
#include "Library.hpp"

void Test_RandomPermutation(){
    Graph G;
    G.number_of_nodes = 100; // Initliaze the number of nodes for the test
    std::vector<int> permutation = RandomPermutation(&G);

    std::vector<bool> Testvector(G.number_of_nodes,false);
    // check that no number in permutation is out of bounds
    for(int index = 0; index < permutation.size(); index++){
        TEST_ASSERT(permutation[index]>=0 && permutation[index]<G.number_of_nodes) ;
        Testvector[index] = true;
    }
    for(int i = 0; i < permutation.size(); i++)
        TEST_ASSERT(Testvector[i] == true);
}
    
TEST_LIST = {
    {"Random Permutation",Test_RandomPermutation},
    {NULL,NULL}
};
