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
    int Return_Number = Init_Query_Data(base_filename, &Q);

    TEST_ASSERT(!Return_Number);
    TEST_ASSERT(Q.vectors_array != NULL);   // Checking that the array is not NULL
    TEST_ASSERT(Q.number_of_vectors == 10); // We know that we have 10 vectors in 2-dimensional space
    TEST_ASSERT(Q.dimension == 2);
    for (int i = 0; i < Q.number_of_vectors; i++)
    {
        TEST_ASSERT(Q.vectors_array[i] != NULL); // Check for every vector that it is not NULL
    }
    Delete_Query(&Q);
}

void Test_Init_GroundTruth(){
    const char *base_fiflename = "Datasets/Small_Set/siftsmall_groundtruth.ivecs";
    groundTruth GT = {.array = NULL,.size = 0};

    int Return_Number = Init_Ground_Truth_Data(base_fiflename,&GT);

    TEST_ASSERT(!Return_Number); 
    TEST_ASSERT(GT.array != NULL); // Checking that the array is not NULL
    TEST_ASSERT(GT.size == 100); // We know we have 100 x 100 array

    for(int i = 0; i<GT.size; i++)
        TEST_ASSERT(GT.array[i] != NULL); // Check for every vector that it is not NULL
    Delete_GroundTruth(&GT);
}


void TestReadTxt(){
    const char *outputfilename = "Datasets/Test_Set/Test_groundtruth.txt";
    std::vector<std::vector<int>> result = ReadFileTXT(outputfilename);
    TEST_ASSERT(result.size()>0); // Ensure that the vector is not empty after calling the Function
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
        //For each vector we know which of each neighbors is the closest. So we just check with a switch case
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
    std::set<std::pair<double,int>> Set_1 = {};
    std::set<int> Set_2 = {1, 2};
    std::set<int> Difference = {};
    Set_Difference(&Set_1, &Set_2, &Difference); // The difference of the sets above should be the empty set
    TEST_ASSERT(Difference.empty());
    std::set<std::pair<double,int>> Set_1_1 = {{0.1,1},{2.51, 2}, {0.4,3}};
    std::set<int> Set_2_1 = {1, 2};
    std::set<int> Difference_1 = {};
    Set_Difference(&Set_1_1, &Set_2_1, &Difference_1); // The difference between these twwo sets should only be the number 3
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
        TEST_ASSERT(permutation[index] >= 0 && permutation[index] < G.number_of_nodes); // Ensure the index is not out of bounds
        Testvector[index] = true;
    }
    for (int i = 0; i < permutation.size(); i++)
        TEST_ASSERT(Testvector[i] == true); // Ensure that all elements exist inside the vector
    Delete_Graph(&G);
}

void Test_EuclideanDistance()
{
    int Size = 10;
    double Distance;
    float Firstvector[Size] = {99.298075, 52.821333, 45.21735, 30.724207, 26.445719, 20.399573, 58.699165, 34.701088, 66.892703, 58.89266};
    float Secondvector[Size] = {35.538892, 38.504338, 79.524579, 32.751777, 32.773157, 55.701575, 16.653934, 23.826345, 52.985472, 88.023222};
    Distance = EuclidianDistance(Firstvector, Secondvector, Size);

    TEST_ASSERT(abs(98.31397043632872 - Distance) < 0.00001); // Ensure that there isn't a big error marggin when calculating the Euclidean Distance for two random vectors
}

void Test_RandomNumber()
{
    int number, exclude, maxVal;
    exclude = 10;
    maxVal = 100;
    number = GetRandomNumber(maxVal, exclude);
    TEST_ASSERT(number != exclude); // Ensure that the Function doesn't return the number we excluded specifically when calling it
}

void Test_Greedy_Search()
{
    const char *base_filename = "Datasets/Test_Set/random_vectors.fvecs";
    Graph G = {.nodes_array = NULL, .R = 2, .number_of_nodes = 0, .dimension = 0};
    int Return_Number = Init_Graph_Data(base_filename, &G);
    std::set<int> TempSet = {};
    result_greedy *res = NULL;                 // Initialize the results we are going to get from the greedy
    float *temp_xq = new float[2]{5.0, 5.0};   // Query is going to have the value of the center of the graph
    res = Greedy_Search(&G, temp_xq, 2, 5, 4); // Calling Greedy_Search for the k=2,L=5 and s=4
    std::set<int> V = {0, 3, 4, 6, 9};         // What V will contain given the above
    std::set<int> L = {4, 9};                  // What L will contain given the above
    TEST_ASSERT(res->V == V);
    for(auto &element : res->L){
        TempSet.insert(element.second);
    }
    TEST_ASSERT(TempSet == L);
    Delete_Graph(&G);
    free(res);
    delete temp_xq;
}

void Test_Robust_Prune()
{
    const char *base_filename = "Datasets/Test_Set/random_vectors.fvecs";
    Graph G = {.nodes_array = NULL, .R = 5, .number_of_nodes = 0, .dimension = 0};

    Init_Graph_Data(base_filename, &G);

    std::set<int> test_set = {0, 5, 9};
    Robust_Prune(0, &test_set, 1, &G);

    std::set<int> right_result = {7, 9};

    TEST_ASSERT(G.nodes_array[0].edges == right_result); // We know after runniing robust Prune by hand that the Result for this specific example should be {7,9}
}

void Test_Vamana()
{
    srand(time(NULL)); // make the seed
    int fun_result, R = 9, L = 10, k = 7, s, accuracy = 0,total_accuracy = 0;
    const char *base_filename = "Datasets/Test_Set/random_vectors.fvecs", *output_filename = "Datasets/Test_Set/Test_groundtruth.txt";
    std::vector<std::vector<int>> GroundTruthVector;
    std::set<int> Tempset;
    Graph G;
    fun_result = Vamana(base_filename, &G, L, R); // Vamana algorithm 
    GroundTruthVector = ReadFileTXT(output_filename); // Save the GroundTruth into a Vector 
    s = Medoid(&G); // Find Medoid
    result_greedy *Results;

    for (int i = 0; i < G.number_of_nodes; i++)
    {
        accuracy = 0;
        if (i >= GroundTruthVector.size())
        {
            break;
        }

        Results = Greedy_Search(&G, G.nodes_array[i].vector, k, L, s);
        Tempset.clear();
        for(std::set<std::pair<double,int>>::iterator it = Results->L.begin(); it != Results->L.end(); it++)
            Tempset.insert(it->second); // Save the indexes into a second set

        std::vector<int> &GroundTruthRow = GroundTruthVector[i];
        for(auto &element : GroundTruthRow){
            if(Tempset.find(element)!=Tempset.end())
                accuracy++; // Increment the individual accuracy for each vector
        }
        if((double)accuracy/Tempset.size() > 0.83) // No individual vector has a better accuracy than 83 %
            total_accuracy++;
        delete Results;
    }
    TEST_ASSERT(fun_result == s);

    for (int index = 0; index < G.number_of_nodes; index++)
        TEST_ASSERT(G.nodes_array[index].edges.size() <= R); // There shouldn't exists any vector with more than R edges

    TEST_ASSERT(total_accuracy > 8) ; // Check that at least 8 out of 10 vector has a better accuracy than 83%
}

TEST_LIST = {
    {"Initialization of Graph", Test_Init_Graph},
    {"Initialization of Query", Test_Init_Query},
    {"Initialization of Ground Truth",Test_Init_GroundTruth},
    {"Read TXT", TestReadTxt},
    {"Medoid", Test_Medoid},
    {"Random Permutation", Test_RandomPermutation},
    {"EculideanDistance", Test_EuclideanDistance},
    {"Random Number", Test_RandomNumber},
    {"Set_Difference", Test_Set_Difference},
    {"Argument Min Distance", Test_Argument_Min_Distance},
    {"Greedy_Search", Test_Greedy_Search},
    {"Robust Prune", Test_Robust_Prune},
    {"Vamana", Test_Vamana},
    {NULL, NULL}};
