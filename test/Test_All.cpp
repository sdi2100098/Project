#include "acutest.h"
#include "fun.hpp"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <unistd.h>

void Test_EuclideanDistance()
{
    int Size = 10;
    double Distance;
    float Firstvector[Size] = {99.298075, 52.821333, 45.21735, 30.724207, 26.445719, 20.399573, 58.699165, 34.701088, 66.892703, 58.89266};
    float Secondvector[Size] = {35.538892, 38.504338, 79.524579, 32.751777, 32.773157, 55.701575, 16.653934, 23.826345, 52.985472, 88.023222};
    Distance = EuclideanDistance(Firstvector, Secondvector, Size);

    TEST_ASSERT(abs(98.31397043632872 - Distance) < 0.00001); // Ensure that there isn't a big error margin when calculating the Euclidean Distance for two random vectors
}


void Test_FindMedoid()
{
    int number_of_indexes = 10,Filters_Size=10,dimension = 2,threshold = 1;
    int *Map ;
    std::vector<std::pair<float,float>> Test_Vector = {{5.16,6.36},{9.82,0.71},{2.96,0.30},{7.14,2.95},{3.73,4.44},{0.65,3.34},{2.52,2.29},{1.06,2.95},{9.58,4.75},{6.24,5.11}};
    std::vector<std::vector<int>> edges = {{3,6},{5,7},{3,5},{2,6},{1,9},{2,7},{0,9},{3,6},{0,6},{2,6}};
    Graph G;
    G.dimension = dimension;
    G.Filters_Size = Filters_Size;
    G.index_array = new node[number_of_indexes]();
    G.memo.rows = number_of_indexes;
    G.number_of_indexes = number_of_indexes;
    G.Filters =  new std::vector<int>[Filters_Size]();
    G.memo.Distances = (float**)malloc(G.memo.rows * sizeof(float *));
    for(int i =0 ; i<number_of_indexes; i++){
        G.index_array[i].vector = (float *)malloc(dimension * sizeof(float));
        G.memo.Distances[i] = (float*)malloc((i+1)*sizeof(float));
        for(auto &ele : edges[i])
            G.index_array[i].edges.insert(ele);
        G.index_array[i].filter = i;
        G.Filters[i].push_back(i);
    }
    for(int i =0; i<number_of_indexes; i++){
        for(int j =0 ; j<dimension; j++){
            G.index_array[i].vector[j] = (!j) ? Test_Vector[i].first:Test_Vector[i].second;
        }
    }
    for(int i =0; i<number_of_indexes; i++){
        for(int j =0; j<=i; j++)
            G.memo.Distances[i][j] = EuclideanDistance(G.index_array[i].vector,G.index_array[j].vector,dimension);    
    }
    Map = FindMedoid(&G,threshold);
    TEST_ASSERT(Map!=NULL);
    for(int i = 0; i < 10; i++)
        TEST_ASSERT(Map[i] == i);
    free(Map);
    Delete_Graph(&G,true);
}

void Test_Medoid(){
    int number_of_indexes = 10,Filters_Size=10,dimension = 2,medoid;
    std::vector<std::pair<float,float>> Test_Vector = {{5.16,6.36},{9.82,0.71},{2.96,0.30},{7.14,2.95},{3.73,4.44},{0.65,3.34},{2.52,2.29},{1.06,2.95},{9.58,4.75},{6.24,5.11}};
    std::vector<std::vector<int>> edges = {{3,6},{5,7},{3,5},{2,6},{1,9},{2,7},{0,9},{3,6},{0,6},{2,6}};
    Graph G;
    G.dimension = dimension;
    G.Filters_Size = Filters_Size;
    G.index_array = new node[number_of_indexes]();
    G.memo.rows = number_of_indexes;
    G.number_of_indexes = number_of_indexes;
    G.Filters =  new std::vector<int>[Filters_Size]();
    G.memo.Distances = (float**)malloc(G.memo.rows * sizeof(float *));
    for(int i =0 ; i<number_of_indexes; i++){
        G.index_array[i].vector = (float *)malloc(dimension * sizeof(float));
        G.memo.Distances[i] = (float*)malloc((i+1)*sizeof(float));
        for(auto &ele : edges[i])
            G.index_array[i].edges.insert(ele);
        G.index_array[i].filter = i;
        G.Filters[i].push_back(i);
    }
    for(int i =0; i<number_of_indexes; i++){
        for(int j =0 ; j<dimension; j++){
            G.index_array[i].vector[j] = (!j) ? Test_Vector[i].first:Test_Vector[i].second;
        }
    }
    for(int i =0; i<number_of_indexes; i++){
        for(int j =0; j<=i; j++)
            G.memo.Distances[i][j] = EuclideanDistance(G.index_array[i].vector,G.index_array[j].vector,dimension);    
    }
    for(int i = 0; i<G.Filters_Size; i++){
        medoid = Medoid(&G,i);
        TEST_ASSERT(medoid == i);
    }
    Delete_Graph(&G,true);
}

void Test_Argument_Min_Distance()
{
    int number_of_indexes = 10,Filters_Size=10,dimension = 2;
    std::vector<std::pair<float,float>> Test_Vector = {{5.16,6.36},{9.82,0.71},{2.96,0.30},{7.14,2.95},{3.73,4.44},{0.65,3.34},{2.52,2.29},{1.06,2.95},{9.58,4.75},{6.24,5.11}};
    std::vector<std::vector<int>> edges = {{3,6},{5,7},{3,5},{2,6},{1,9},{2,7},{0,9},{3,6},{0,6},{2,6}};
    Graph G;
    G.dimension = dimension;
    G.Filters_Size = Filters_Size;
    G.index_array = new node[number_of_indexes]();
    G.memo.rows = number_of_indexes;
    G.number_of_indexes = number_of_indexes;
    G.Filters =  new std::vector<int>[Filters_Size]();
    G.memo.Distances = (float**)malloc(G.memo.rows * sizeof(float *));
    for(int i =0 ; i<number_of_indexes; i++){
        G.index_array[i].vector = (float *)malloc(dimension * sizeof(float));
        G.memo.Distances[i] = (float*)malloc((i+1)*sizeof(float));
        for(auto &ele : edges[i])
            G.index_array[i].edges.insert(ele);
        G.index_array[i].filter = i;
        G.Filters[i].push_back(i);
    }
    for(int i =0; i<number_of_indexes; i++){
        for(int j =0 ; j<dimension; j++){
            G.index_array[i].vector[j] = (!j) ? Test_Vector[i].first:Test_Vector[i].second;
        }
    }
    for(int i =0; i<number_of_indexes; i++){
        for(int j =0; j<=i; j++)
            G.memo.Distances[i][j] = EuclideanDistance(G.index_array[i].vector,G.index_array[j].vector,dimension);    
    }

    for (int i = 0; i < G.number_of_indexes; i++)
    {
        int index = Argument_Min_Distance(&G,NULL, &(G.index_array[i].edges),i);
        switch (i)
        {
        case 0 : 
            TEST_ASSERT(index == 3);
            break;
        
        case 1 : 
            TEST_ASSERT(index == 7);
            break;

        case 2 : 
            TEST_ASSERT(index == 5);
            break;

        case 3 :
            TEST_ASSERT(index == 6);
            break;

        case 4 : 
            TEST_ASSERT(index == 9);
            break;


        case 5 : 
            TEST_ASSERT(index == 7);
            break;


        case 6 : 
            TEST_ASSERT(index == 9);
            break;

        case 7 :
            TEST_ASSERT(index == 6);
            break;

        case 8 :
            TEST_ASSERT(index == 0);
            break;

        case 9 :
            TEST_ASSERT(index == 6);
            break;
        }
    }
    Delete_Graph(&G,true);
}

void Test_Set_Difference()
{
    std::set<std::pair<float, int>> Set_1 = {};
    std::set<int> Set_2 = {1, 2};
    std::set<int> Difference = {};
    Set_Difference(&Set_1, &Set_2, &Difference); // The difference of the sets above should be the empty set
    TEST_ASSERT(Difference.empty());
    std::set<std::pair<float, int>> Set_1_1 = {{0.1, 1}, {2.51, 2}, {0.4, 3}};
    std::set<int> Set_2_1 = {1, 2};
    std::set<int> Difference_1 = {};
    Set_Difference(&Set_1_1, &Set_2_1, &Difference_1); // The difference between these twwo sets should only be the number 3
    TEST_ASSERT(Difference_1.find(3) != Difference_1.end());
}

void Test_RandomPermutation()
{
    int number_of_indexes = 10,Filters_Size=10,dimension = 2;
    std::vector<std::pair<float,float>> Test_Vector = {{5.16,6.36},{9.82,0.71},{2.96,0.30},{7.14,2.95},{3.73,4.44},{0.65,3.34},{2.52,2.29},{1.06,2.95},{9.58,4.75},{6.24,5.11}};
    std::vector<std::vector<int>> edges = {{3,6},{5,7},{3,5},{2,6},{1,9},{2,7},{0,9},{3,6},{0,6},{2,6}};
    Graph G;
    G.dimension = dimension;
    G.Filters_Size = Filters_Size;
    G.index_array = new node[number_of_indexes]();
    G.memo.rows = number_of_indexes;
    G.number_of_indexes = number_of_indexes;
    G.Filters =  new std::vector<int>[Filters_Size]();
    G.memo.Distances = (float**)malloc(G.memo.rows * sizeof(float *));
    for(int i =0 ; i<number_of_indexes; i++){
        G.index_array[i].vector = (float *)malloc(dimension * sizeof(float));
        G.memo.Distances[i] = (float*)malloc((i+1)*sizeof(float));
        for(auto &ele : edges[i])
            G.index_array[i].edges.insert(ele);
        G.index_array[i].filter = i;
        G.Filters[i].push_back(i);
    }
    for(int i =0; i<number_of_indexes; i++){
        for(int j =0 ; j<dimension; j++){
            G.index_array[i].vector[j] = (!j) ? Test_Vector[i].first:Test_Vector[i].second;
        }
    }
    for(int i =0; i<number_of_indexes; i++){
        for(int j =0; j<=i; j++)
            G.memo.Distances[i][j] = EuclideanDistance(G.index_array[i].vector,G.index_array[j].vector,dimension);    
    }

    std::vector<int> permutation = RandomPermutation(&G,false,0);

    std::vector<bool> Testvector(G.number_of_indexes, false);
    // check that no number in permutation is out of bounds
    for (int index = 0; index < (int)permutation.size(); index++)
    {
        TEST_ASSERT(permutation[index] >= 0 && permutation[index] < G.number_of_indexes); // Ensure the index is not out of bounds
        Testvector[index] = true;
    }
    for (int i = 0; i < (int)permutation.size(); i++)
        TEST_ASSERT(Testvector[i] == true); // Ensure that all elements exist inside the vector
    Delete_Graph(&G,true);
}

void Test_Filtered_Greedy_Search()
{   
    int number_of_indexes = 10,Filters_Size=10,dimension = 2,threshold = 1,k=1,L=2;
    int *Map ;
    std::vector<std::pair<float,float>> Test_Vector = {{5.16,6.36},{9.82,0.71},{2.96,0.30},{7.14,2.95},{3.73,4.44},{0.65,3.34},{2.52,2.29},{1.06,2.95},{9.58,4.75},{6.24,5.11}};
    std::vector<std::vector<int>> edges = {{3,6},{5,7},{3,5},{2,6},{1,9},{2,7},{0,9},{3,6},{0,6},{2,6}};
    Result_greedy *Return_Val;
    Graph G;
    G.R = 2;
    G.dimension = dimension;
    G.Filters_Size = Filters_Size;
    G.index_array = new node[number_of_indexes]();
    G.memo.rows = number_of_indexes;
    G.number_of_indexes = number_of_indexes;
    G.Filters =  new std::vector<int>[Filters_Size]();
    G.memo.Distances = (float**)malloc(G.memo.rows * sizeof(float *));
    for(int i =0 ; i<number_of_indexes; i++){
        G.index_array[i].vector = (float *)malloc(dimension * sizeof(float));
        G.memo.Distances[i] = (float*)malloc((i+1)*sizeof(float));
        for(auto &ele : edges[i])
            G.index_array[i].edges.insert(ele);
        G.index_array[i].filter = i;
        G.Filters[i].push_back(i);
    }
    for(int i =0; i<number_of_indexes; i++){
        for(int j =0 ; j<dimension; j++){
            G.index_array[i].vector[j] = (!j) ? Test_Vector[i].first:Test_Vector[i].second;
        }
    }
    for(int i =0; i<number_of_indexes; i++){
        for(int j =0; j<=i; j++)
            G.memo.Distances[i][j] = EuclideanDistance(G.index_array[i].vector,G.index_array[j].vector,dimension);    
    }
    Map = FindMedoid(&G,threshold);
    TEST_ASSERT(Map!=NULL);
    for(int i = 0; i < 10; i++){
        TEST_ASSERT(Map[i] == i);
        Return_Val = Filtered_Greedy_Search(&G,i,k,L,Map,NULL);
        TEST_ASSERT((int)Return_Val->L.size() <= k);
        TEST_ASSERT((int)Return_Val->V.size() <= G.R);
        TEST_ASSERT(*(Return_Val->V.begin()) == i);
        delete Return_Val;
    }
    
    
    
    free(Map);

    Delete_Graph(&G,true);
}

void Test_Filtered_Robust_Prune()
{
    int number_of_indexes = 10,Filters_Size=10,dimension = 2,threshold = 1,k=1,L=2;
    int *Map ;
    double a = 1.1;
    std::vector<std::pair<float,float>> Test_Vector = {{5.16,6.36},{9.82,0.71},{2.96,0.30},{7.14,2.95},{3.73,4.44},{0.65,3.34},{2.52,2.29},{1.06,2.95},{9.58,4.75},{6.24,5.11}};
    std::vector<std::vector<int>> edges = {{3,6},{5,7},{3,5},{2,6},{1,9},{2,7},{0,9},{3,6},{0,6},{2,6}};
    std::set<int> Temp_set;
    Result_greedy *Return_Val;
    Graph G;
    G.R = 2;
    G.dimension = dimension;
    G.Filters_Size = Filters_Size;
    G.index_array = new node[number_of_indexes]();
    G.memo.rows = number_of_indexes;
    G.number_of_indexes = number_of_indexes;
    G.Filters =  new std::vector<int>[Filters_Size]();
    G.memo.Distances = (float**)malloc(G.memo.rows * sizeof(float *));
    for(int i =0 ; i<number_of_indexes; i++){
        G.index_array[i].vector = (float *)malloc(dimension * sizeof(float));
        G.memo.Distances[i] = (float*)malloc((i+1)*sizeof(float));
        for(auto &ele : edges[i])
            G.index_array[i].edges.insert(ele);
        G.index_array[i].filter = i;
        G.Filters[i].push_back(i);
    }
    for(int i =0; i<number_of_indexes; i++){
        for(int j =0 ; j<dimension; j++){
            G.index_array[i].vector[j] = (!j) ? Test_Vector[i].first:Test_Vector[i].second;
        }
    }
    for(int i =0; i<number_of_indexes; i++){
        for(int j =0; j<=i; j++)
            G.memo.Distances[i][j] = EuclideanDistance(G.index_array[i].vector,G.index_array[j].vector,dimension);    
    }
    Map = FindMedoid(&G,threshold);
    TEST_ASSERT(Map!=NULL);
    for(int i = 0; i < 10; i++){
        TEST_ASSERT(Map[i] == i);
        Return_Val = Filtered_Greedy_Search(&G,i,k,L,Map,NULL);
        for(auto &ele : G.index_array[i].edges)
            Temp_set.insert(ele);
        Filtered_Robust_Prune(i,Return_Val->V,a,&G);
        TEST_ASSERT((int)G.index_array[i].edges.size() <= G.R);
        for(auto &ele : G.index_array[i].edges)
            TEST_ASSERT(Temp_set.find(ele) != Temp_set.end());
        delete Return_Val;
    }

     free(Map);

    Delete_Graph(&G,true);
}

void Test_Filtered_Vamana()
{
    int number_of_indexes = 10,Filters_Size=10,dimension = 2,k=1,L=2,R_stitched=2,R_small = 1,L_small = 1,threshold = 1;
    int *Map ;
    double a = 1.1;
    std::vector<std::pair<float,float>> Test_Vector = {{5.16,6.36},{9.82,0.71},{2.96,0.30},{7.14,2.95},{3.73,4.44},{0.65,3.34},{2.52,2.29},{1.06,2.95},{9.58,4.75},{6.24,5.11}};
    std::vector<std::vector<int>> edges = {{3,6},{5,7},{3,5},{2,6},{1,9},{2,7},{0,9},{3,6},{0,6},{2,6}};
    std::set<int> Temp_set;
    Result_greedy *Return_Val;
    Graph G;
    G.dimension = dimension;
    G.Filters_Size = Filters_Size;
    G.index_array = new node[number_of_indexes]();
    G.memo.rows = number_of_indexes;
    G.number_of_indexes = number_of_indexes;
    G.Filters =  new std::vector<int>[Filters_Size]();
    G.memo.Distances = (float**)malloc(G.memo.rows * sizeof(float *));
    for(int i =0 ; i<number_of_indexes; i++){
        G.index_array[i].vector = (float *)malloc(dimension * sizeof(float));
        G.memo.Distances[i] = (float*)malloc((i+1)*sizeof(float));
        for(auto &ele : edges[i])
            G.index_array[i].edges.insert(ele);
        G.index_array[i].filter = i;
        G.Filters[i].push_back(i);
    }
    for(int i =0; i<number_of_indexes; i++){
        for(int j =0 ; j<dimension; j++){
            G.index_array[i].vector[j] = (!j) ? Test_Vector[i].first:Test_Vector[i].second;
        }
    }
    for(int i =0; i<number_of_indexes; i++){
        for(int j =0; j<=i; j++)
            G.memo.Distances[i][j] = EuclideanDistance(G.index_array[i].vector,G.index_array[j].vector,dimension);    
    }
     // Save original stream buffers
    std::streambuf* cout_buffer = std::cout.rdbuf();
    int stdout_fd = dup(STDOUT_FILENO); // Duplicate stdout file descriptor

    // Redirect `std::cout` to /dev/null
    std::ofstream null_stream("/dev/null");
    std::cout.rdbuf(null_stream.rdbuf());

    // Redirect `stdout` (for printf) to /dev/null
    if (freopen("/dev/null", "w", stdout) == nullptr) {
        std::cerr << "Error: Failed to redirect stdout to /dev/null" << std::endl;
        exit(EXIT_FAILURE); // Exit if redirection fails
    }

    Map = FindMedoid(&G,threshold);
    TEST_ASSERT(Map!=NULL);
    StichedVamana(&G,L_small,R_small,R_stitched,a);
    for(int i = 0; i < 10; i++){
        TEST_ASSERT(Map[i] == i);
        Return_Val = Filtered_Greedy_Search(&G,i,k,L,Map,NULL);
        TEST_ASSERT(Return_Val->L.begin()->second == i);
        delete Return_Val;
    }

    //Restore `std::cout` and `stdout`
    std::cout.rdbuf(cout_buffer);
    fflush(stdout);
    dup2(stdout_fd, STDOUT_FILENO); // Restore stdout
    close(stdout_fd);
    free(Map);

    Delete_Graph(&G,true);
}

void Test_Stitched_Vamana(){
    int number_of_indexes = 10,Filters_Size=10,dimension = 2,k=1,L=2,R=2;
    int *Map ;
    double a = 1.1;
    std::vector<std::pair<float,float>> Test_Vector = {{5.16,6.36},{9.82,0.71},{2.96,0.30},{7.14,2.95},{3.73,4.44},{0.65,3.34},{2.52,2.29},{1.06,2.95},{9.58,4.75},{6.24,5.11}};
    std::vector<std::vector<int>> edges = {{3,6},{5,7},{3,5},{2,6},{1,9},{2,7},{0,9},{3,6},{0,6},{2,6}};
    std::set<int> Temp_set;
    Result_greedy *Return_Val;
    Graph G;
    G.dimension = dimension;
    G.Filters_Size = Filters_Size;
    G.index_array = new node[number_of_indexes]();
    G.memo.rows = number_of_indexes;
    G.number_of_indexes = number_of_indexes;
    G.Filters =  new std::vector<int>[Filters_Size]();
    G.memo.Distances = (float**)malloc(G.memo.rows * sizeof(float *));
    for(int i =0 ; i<number_of_indexes; i++){
        G.index_array[i].vector = (float *)malloc(dimension * sizeof(float));
        G.memo.Distances[i] = (float*)malloc((i+1)*sizeof(float));
        for(auto &ele : edges[i])
            G.index_array[i].edges.insert(ele);
        G.index_array[i].filter = i;
        G.Filters[i].push_back(i);
    }
    for(int i =0; i<number_of_indexes; i++){
        for(int j =0 ; j<dimension; j++){
            G.index_array[i].vector[j] = (!j) ? Test_Vector[i].first:Test_Vector[i].second;
        }
    }
    for(int i =0; i<number_of_indexes; i++){
        for(int j =0; j<=i; j++)
            G.memo.Distances[i][j] = EuclideanDistance(G.index_array[i].vector,G.index_array[j].vector,dimension);    
    }
     // Save original stream buffers
    std::streambuf* cout_buffer = std::cout.rdbuf();
    int stdout_fd = dup(STDOUT_FILENO); // Duplicate stdout file descriptor

    // Redirect `std::cout` to /dev/null
    std::ofstream null_stream("/dev/null");
    std::cout.rdbuf(null_stream.rdbuf());

    // Redirect `stdout` (for printf) to /dev/null
    if (freopen("/dev/null", "w", stdout) == nullptr) {
        std::cerr << "Error: Failed to redirect stdout to /dev/null" << std::endl;
        exit(EXIT_FAILURE); // Exit if redirection fails
    }

    Map = Filtered_Vamana(&G,L,R,a);
    TEST_ASSERT(Map!=NULL);
    for(int i = 0; i < 10; i++){
        TEST_ASSERT(Map[i] == i);
        Return_Val = Filtered_Greedy_Search(&G,i,k,L,Map,NULL);
        TEST_ASSERT(Return_Val->L.begin()->second == i);
        delete Return_Val;
    }

    //Restore `std::cout` and `stdout`
    std::cout.rdbuf(cout_buffer);
    fflush(stdout);
    dup2(stdout_fd, STDOUT_FILENO); // Restore stdout
    close(stdout_fd);
    free(Map);

    Delete_Graph(&G,true);
}

void Test_Vamana(){
    int number_of_indexes = 10,Filters_Size=10,dimension = 2,k=1,L=2,R=2,threshold = 1;
    int *Map ;
    double a = 1.1;
    std::vector<std::pair<float,float>> Test_Vector = {{5.16,6.36},{9.82,0.71},{2.96,0.30},{7.14,2.95},{3.73,4.44},{0.65,3.34},{2.52,2.29},{1.06,2.95},{9.58,4.75},{6.24,5.11}};
    std::vector<std::vector<int>> edges = {{3,6},{5,7},{3,5},{2,6},{1,9},{2,7},{0,9},{3,6},{0,6},{2,6}};
    std::set<int> Temp_set;
    Result_greedy *Return_Val;
    Graph G;
    G.dimension = dimension;
    G.Filters_Size = Filters_Size;
    G.index_array = new node[number_of_indexes]();
    G.memo.rows = number_of_indexes;
    G.number_of_indexes = number_of_indexes;
    G.Filters =  new std::vector<int>[Filters_Size]();
    G.memo.Distances = (float**)malloc(G.memo.rows * sizeof(float *));
    for(int i =0 ; i<number_of_indexes; i++){
        G.index_array[i].vector = (float *)malloc(dimension * sizeof(float));
        G.memo.Distances[i] = (float*)malloc((i+1)*sizeof(float));
        for(auto &ele : edges[i])
            G.index_array[i].edges.insert(ele);
        G.index_array[i].filter = i;
        G.Filters[i].push_back(i);
    }
    for(int i =0; i<number_of_indexes; i++){
        for(int j =0 ; j<dimension; j++){
            G.index_array[i].vector[j] = (!j) ? Test_Vector[i].first:Test_Vector[i].second;
        }
    }
    for(int i =0; i<number_of_indexes; i++){
        for(int j =0; j<=i; j++)
            G.memo.Distances[i][j] = EuclideanDistance(G.index_array[i].vector,G.index_array[j].vector,dimension);    
    }
     // Save original stream buffers
    std::streambuf* cout_buffer = std::cout.rdbuf();
    int stdout_fd = dup(STDOUT_FILENO); // Duplicate stdout file descriptor

    // Redirect `std::cout` to /dev/null
    std::ofstream null_stream("/dev/null");
    std::cout.rdbuf(null_stream.rdbuf());

    // Redirect `stdout` (for printf) to /dev/null
    if (freopen("/dev/null", "w", stdout) == nullptr) {
        std::cerr << "Error: Failed to redirect stdout to /dev/null" << std::endl;
        exit(EXIT_FAILURE); // Exit if redirection fails
    }

    Map = FindMedoid(&G,threshold);
    TEST_ASSERT(Map!=NULL);
    for(int i = 0; i < 10; i++){
        TEST_ASSERT(Map[i] == i);
        Vamana(&G,L,R,a,i,true);
        Return_Val = Filtered_Greedy_Search(&G,i,k,L,Map,NULL);
        TEST_ASSERT(Return_Val->L.begin()->second == i);
        delete Return_Val;
    }

    //Restore `std::cout` and `stdout`
    std::cout.rdbuf(cout_buffer);
    fflush(stdout);
    dup2(stdout_fd, STDOUT_FILENO); // Restore stdout
    close(stdout_fd);
    free(Map);

    Delete_Graph(&G,true);
}

void Test_Robust(){
    int number_of_indexes = 10,Filters_Size=10,dimension = 2,threshold = 1,k=1,L=2;
    int *Map ;
    double a = 1.1;
    std::vector<std::pair<float,float>> Test_Vector = {{5.16,6.36},{9.82,0.71},{2.96,0.30},{7.14,2.95},{3.73,4.44},{0.65,3.34},{2.52,2.29},{1.06,2.95},{9.58,4.75},{6.24,5.11}};
    std::vector<std::vector<int>> edges = {{3,6},{5,7},{3,5},{2,6},{1,9},{2,7},{0,9},{3,6},{0,6},{2,6}};
    std::set<int> Temp_set;
    Result_greedy *Return_Val;
    Graph G;
    G.R = 2;
    G.dimension = dimension;
    G.Filters_Size = Filters_Size;
    G.index_array = new node[number_of_indexes]();
    G.memo.rows = number_of_indexes;
    G.number_of_indexes = number_of_indexes;
    G.Filters =  new std::vector<int>[Filters_Size]();
    G.memo.Distances = (float**)malloc(G.memo.rows * sizeof(float *));
    for(int i =0 ; i<number_of_indexes; i++){
        G.index_array[i].vector = (float *)malloc(dimension * sizeof(float));
        G.memo.Distances[i] = (float*)malloc((i+1)*sizeof(float));
        for(auto &ele : edges[i])
            G.index_array[i].edges.insert(ele);
        G.index_array[i].filter = i;
        G.Filters[i].push_back(i);
    }
    for(int i =0; i<number_of_indexes; i++){
        for(int j =0 ; j<dimension; j++){
            G.index_array[i].vector[j] = (!j) ? Test_Vector[i].first:Test_Vector[i].second;
        }
    }
    for(int i =0; i<number_of_indexes; i++){
        for(int j =0; j<=i; j++)
            G.memo.Distances[i][j] = EuclideanDistance(G.index_array[i].vector,G.index_array[j].vector,dimension);    
    }
    Map = FindMedoid(&G,threshold);
    TEST_ASSERT(Map!=NULL);
    for(int i = 0; i < 10; i++){
        TEST_ASSERT(Map[i] == i);
        Return_Val = Filtered_Greedy_Search(&G,i,k,L,Map,NULL);
        for(auto &ele : G.index_array[i].edges)
            Temp_set.insert(ele);
        Robust_Prune(i,&(Return_Val)->V,a,&G);
        TEST_ASSERT((int)G.index_array[i].edges.size() <= G.R);
        for(auto &ele : G.index_array[i].edges)
            TEST_ASSERT(Temp_set.find(ele) != Temp_set.end());
        delete Return_Val;
    }

     free(Map);

    Delete_Graph(&G,true);
}

void Test_Greedy(){
    int number_of_indexes = 10,Filters_Size=10,dimension = 2,k=5,L=4,medoid;
    std::vector<std::pair<float,float>> Test_Vector = {{5.16,6.36},{9.82,0.71},{2.96,0.30},{7.14,2.95},{3.73,4.44},{0.65,3.34},{2.52,2.29},{1.06,2.95},{9.58,4.75},{6.24,5.11}};
    std::vector<std::vector<int>> edges = {{3,6},{5,7},{3,5},{2,6},{1,9},{2,7},{0,9},{3,6},{0,6},{2,6}};
    Result_greedy *Return_Val;
    Graph G;
    G.R = 2;
    G.dimension = dimension;
    G.Filters_Size = Filters_Size;
    G.index_array = new node[number_of_indexes]();
    G.memo.rows = number_of_indexes;
    G.number_of_indexes = number_of_indexes;
    G.Filters =  new std::vector<int>[Filters_Size]();
    G.memo.Distances = (float**)malloc(G.memo.rows * sizeof(float *));
    for(int i =0 ; i<number_of_indexes; i++){
        G.index_array[i].vector = (float *)malloc(dimension * sizeof(float));
        G.memo.Distances[i] = (float*)malloc((i+1)*sizeof(float));
        for(auto &ele : edges[i])
            G.index_array[i].edges.insert(ele);
        G.index_array[i].filter = i;
        G.Filters[i].push_back(i);
    }
    for(int i =0; i<number_of_indexes; i++){
        for(int j =0 ; j<dimension; j++){
            G.index_array[i].vector[j] = (!j) ? Test_Vector[i].first:Test_Vector[i].second;
        }
    }
    for(int i =0; i<number_of_indexes; i++){
        for(int j =0; j<=i; j++)
            G.memo.Distances[i][j] = EuclideanDistance(G.index_array[i].vector,G.index_array[j].vector,dimension);    
    }
    
    
    for(int i = 0; i < 10; i++){
        medoid = Medoid(&G,i);
        TEST_ASSERT(medoid == i);
        Return_Val = Greedy_Search(&G,i,k,L,medoid,NULL);
        
        TEST_ASSERT((int)Return_Val->L.size() <= k);
        for(auto &ele : Return_Val->V)
            TEST_ASSERT(ele >=0 && ele <= 10);
        delete Return_Val;
    }

    Delete_Graph(&G,true);
}

TEST_LIST = {
    {"EculideanDistance", Test_EuclideanDistance}, 
    {"FindMedoid", Test_FindMedoid}, 
    {"Medoid",Test_Medoid},
    {"Random Permutation", Test_RandomPermutation}, 
    {"Set_Difference", Test_Set_Difference}, 
    {"Argument Min Distance", Test_Argument_Min_Distance}, 
    {"Filtered_Greedy_Search", Test_Filtered_Greedy_Search}, 
    {"Filtered_Robust Prune", Test_Filtered_Robust_Prune}, 
    {"Filtered_Vamana", Test_Filtered_Vamana}, 
    {"Stitched_Vamana",Test_Stitched_Vamana},
    {"Vamana",Test_Vamana},
    {"Robust",Test_Robust},
    {"Greedy",Test_Greedy},
    {NULL, NULL}};