#include "acutest.h"
#include "Library.hpp"

void Test_Init_Graph()
{
    const char *base_filename = "Datasets/Small_Set/siftsmall_base.fvecs";
    Graph G;
    G.R = 4;
    int Return_Number = Init_Graph_Data(base_filename, &G);

    TEST_ASSERT((&G) != NULL);          // Test that the Graph isn't equal to NULL
    TEST_ASSERT(G.nodes_array != NULL); // Test that the array of Nodes isn't equal to NULL
    for (int i = 0; i < G.number_of_nodes; i++)
    {
        TEST_ASSERT(G.nodes_array[i].vector != NULL);      // Test that the vector for all nodes aren't equal to NULL
        TEST_ASSERT(G.nodes_array[i].edges.size() == G.R); // Test that the size of the set is in fact equal to R
    }
    TEST_ASSERT(!Return_Number); // If everything went fine it should return zero
    Delete_Graph(&G);            // Free the memory
}

// void Test_Init_Query -> Job For my sweet Friends Gripioths and Koyvelas

void Test_Set_Difference()
{
    std::set<int> Set_1 = {};
    std::set<int> Set_2 = {1, 2};
    std::set<int> Difference = {};
    Set_Difference(&Set_1, &Set_2, &Difference);
    TEST_ASSERT(Difference.empty());
    std::set<int> Set_1_1 = {1, 2, 3};
    std::set<int> Set_2_1 = {1, 2};
    std::set<int> Difference_1 = {};
    Set_Difference(&Set_1_1, &Set_2_1, &Difference_1);
    TEST_ASSERT(Difference_1.find(3) != Difference_1.end());
}

void Test_RandomPermutation()
{
    Graph G;
    G.R = 2; // Initialize R
    const char *base_filename = "Datasets/Small_Set/siftsmall_base.fvecs";

    int Return_Number = Init_Graph_Data(base_filename, &G);
    std::vector<int> permutation = RandomPermutation(&G);

    std::vector<bool> Testvector(G.number_of_nodes, false);
    // check that no number in permutation is out of bounds
    for (int index = 0; index < permutation.size(); index++)
    {
        TEST_ASSERT(permutation[index] >= 0 && permutation[index] < G.number_of_nodes);
        Testvector[index] = true;
    }
    for (int i = 0; i < permutation.size(); i++)
        TEST_ASSERT(Testvector[i] == true);
    Delete_Graph(&G);
}

void Test_EuclideanDistance()
{
    int Size = 10;
    double Distance;
    float Firstvector[Size] = {99.298075, 52.821333, 45.21735, 30.724207, 26.445719, 20.399573, 58.699165, 34.701088, 66.892703, 58.89266};
    float Secondvector[Size] = {35.538892, 38.504338, 79.524579, 32.751777, 32.773157, 55.701575, 16.653934, 23.826345, 52.985472, 88.023222};
    Distance = EuclidianDistance(Firstvector, Secondvector, Size);

    TEST_ASSERT(abs(98.31397043632872 - Distance) < 0.00001);
}

void Test_RandomNumber()
{
    int number, exclude, maxVal;
    exclude = 10;
    maxVal = 100;
    number = GetRandomNumber(maxVal, exclude);
    TEST_ASSERT(number != exclude);
}

TEST_LIST = {
    {"Initialization of Graph", Test_Init_Graph},
    {"Random Permutation", Test_RandomPermutation},
    {"EculideanDistance", Test_EuclideanDistance},
    {"Random Number", Test_RandomNumber},
    {"Set_Difference", Test_Set_Difference},
    {NULL, NULL}};
