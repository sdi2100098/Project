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


void Test_EuclideanDistance(){
    int Size = 10;
    double Distance;
    float Firstvector[Size] = {99.298075,52.821333,45.21735,30.724207,26.445719,20.399573,58.699165,34.701088,66.892703,58.89266};
    float Secondvector[Size] = {35.538892,38.504338,79.524579,32.751777,32.773157,55.701575,16.653934,23.826345,52.985472,88.023222};
    Distance = EuclidianDistance(Firstvector,Secondvector,Size);

    TEST_ASSERT(abs(98.31397043632872-Distance)<0.00001);

}
    
TEST_LIST = {
    {"Random Permutation",Test_RandomPermutation},
    {"EculideanDistance",Test_EuclideanDistance},
    {NULL,NULL}
};
