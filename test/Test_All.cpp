#include "acutest.h"
#include "fun.hpp"

void Test_EuclideanDistance()
{
    int Size = 10;
    double Distance;
    float Firstvector[Size] = {99.298075, 52.821333, 45.21735, 30.724207, 26.445719, 20.399573, 58.699165, 34.701088, 66.892703, 58.89266};
    float Secondvector[Size] = {35.538892, 38.504338, 79.524579, 32.751777, 32.773157, 55.701575, 16.653934, 23.826345, 52.985472, 88.023222};
    Distance = EuclideanDistance(Firstvector, Secondvector, Size);

    TEST_ASSERT(abs(98.31397043632872 - Distance) < 0.00001); // Ensure that there isn't a big error marggin when calculating the Euclidean Distance for two random vectors
}


TEST_LIST = { 
    {"EculideanDistance", Test_EuclideanDistance}, 
    {NULL, NULL}};