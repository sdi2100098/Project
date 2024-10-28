#include "acutest.h"
#include "Library.hpp"

void Test_Init_Graph()
{
    const char *base_filename = "Datasets/Test_Set/random_vectors.fvecs";
    Graph G = {.nodes_array = NULL, .R = 2, .number_of_nodes = 0, .dimension = 0};
    int Return_Number = Init_Graph_Data(base_filename, &G);

    TEST_ASSERT(!Return_Number);          // If everything went fine it should return zero
    TEST_ASSERT(G.nodes_array != NULL);   // Test that the array of Nodes isn't equal to NULL
    TEST_ASSERT(G.number_of_nodes == 10); // We know that we have 10 vectors in 2-dimensional space
    TEST_ASSERT(G.dimension == 2);
    for (int i = 0; i < G.number_of_nodes; i++)
    {
        TEST_ASSERT(G.nodes_array[i].vector != NULL);      // Test that the vector for all nodes aren't equal to NULL
        TEST_ASSERT(G.nodes_array[i].edges.size() == G.R); // Test that the size of the set is in fact equal to R
    }
    Delete_Graph(&G); // Free the memory
}

void Test_Init_Query() 
{
    const char *base_filename = "Datasets/Test_Set/random_vectors.fvecs";
    Query Q = {.vectors_array = NULL, .number_of_vectors = 0, .dimension = 0};
    int Return_Number = Init_Query_Data(base_filename,&Q);

    TEST_ASSERT(!Return_Number);
    TEST_ASSERT(Q.number_of_vectors == 10);
    TEST_ASSERT(Q.dimension == 2);
    for(int i = 0; i < Q.number_of_vectors; i++) 
    {
        for(int j = 0; j < Q.dimension; j++)
        {
            TEST_ASSERT(Q.vectors_array[i][j] != NULL);
        }
    }
    Delete_Query(&Q);
}

void Test_Medoid()
{
    const char *base_filename = "Datasets/Test_Set/random_vectors.fvecs";
    Graph G = {.nodes_array = NULL, .R = 2, .number_of_nodes = 0, .dimension = 0};
    int Return_Number = Init_Graph_Data(base_filename, &G);
    int MedoidResult = Medoid(&G);
    TEST_ASSERT(MedoidResult == 4); // We know that the vector with index 4 is the Medoid
    Delete_Graph(&G);
}

void Test_Argument_Min_Distance()
{
    const char *base_filename = "Datasets/Test_Set/random_vectors.fvecs";
    Graph G = {.nodes_array = NULL, .R = 2, .number_of_nodes = 0, .dimension = 0};
    int Return_Number = Init_Graph_Data(base_filename, &G);
    std::vector<int> Closest_neighbors;
    int count = 0;
    for (int i = 0; i < G.number_of_nodes; i++)
    {
        int index = Argument_Min_Distance(&G, &(G.nodes_array[i].edges), G.nodes_array[i].vector);
        Closest_neighbors.push_back(index);
    }
    for (auto &element : Closest_neighbors)
    {
        switch (count)
        {
        case 0:
            TEST_ASSERT(element == 3);
            break;

        case 1:
            TEST_ASSERT(element == 7);
            break;

        case 2:
            TEST_ASSERT(element == 5);
            break;

        case 3:
            TEST_ASSERT(element == 6);
            break;

        case 4:
            TEST_ASSERT(element == 9);
            break;

        case 5:
            TEST_ASSERT(element == 7);
            break;

        case 6:
            TEST_ASSERT(element == 9);
            break;

        case 7:
            TEST_ASSERT(element == 6);
            break;

        case 8:
            TEST_ASSERT(element == 0);
            break;

        case 9:
            TEST_ASSERT(element == 6);
            break;
        }
        count++;
    }
}
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
    Graph G = {.nodes_array = NULL, .R = 2, .number_of_nodes = 0, .dimension = 0};
    const char *base_filename = "Datasets/Test_Set/random_vectors.fvecs";

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
    {"Medoid", Test_Medoid},
    {"Random Permutation", Test_RandomPermutation},
    {"EculideanDistance", Test_EuclideanDistance},
    {"Random Number", Test_RandomNumber},
    {"Set_Difference", Test_Set_Difference},
    {"Argument Min Distance", Test_Argument_Min_Distance},
    {NULL, NULL}};
