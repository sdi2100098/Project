#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <iostream>
#include <stdbool.h>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <string>
#include <cassert>
#include <iomanip> // Include this header for std::fixed and std::setprecision
#include <cstdlib> // For malloc and free
#include <cassert> // For assert
#include <math.h>  // for the sqrt and pow
#include <time.h>
#include <set>
#include <limits>
#include <algorithm>
#include <iterator>

typedef struct node
{ /* node of each graph */
    float *vector;
    std::set<int> edges; // use set to have unique edges for every vector
} node;

typedef struct graph
{
    node *nodes_array;   /* WTF HASH MAP */
    int R;               /* out-degree number */
    int number_of_nodes; /* rows */
    int dimension;       /* columns */
    int **Distances;     /* Array to hold Distances*/
} Graph;

typedef struct query
{ /* DELULU IS NOT THE SOLULU ! STRUCTES > CLASSES */ // not true !
    float **vectors_array;
    int number_of_vectors; /* rows */
    int dimension;         /* columns */
} Query;

typedef struct groundTruth
{
    int **array;
    int size;
} groundTruth;

typedef struct result_GreedySearch
{
    std::set<int> V;
    std::set<std::pair<double, int>> L;
} result_greedy;

void CreateKNNGraphBruteForce(Graph, int, const char *);
int Init_Graph_Data(const char *, Graph *);
int Init_Query_Data(const char *, Query *);
int Init_Ground_Truth_Data(const char *, groundTruth *);
std::vector<std::vector<int>> ReadFileTXT(const char *);
int GetRandomNumber(const int, const int);

double EuclidianDistance(const float *, const float *, const int);
void Robust_Prune(int, std::set<int> *, float, Graph *);
int Vamana(const char *, Graph *, int, int);
int Argument_Min_Distance(Graph *, std::set<int> *, float *);
int Medoid(Graph *);
void Set_Difference(std::set<std::pair<double, int>> *, std::set<int> *, std::set<int> *);
int CallThread(Graph *);
void *Medoid_Find(void *);
result_greedy *Greedy_Search(Graph *, float *, int, int, int);
std::vector<int> RandomPermutation(Graph *);
int Right_Exec(int, char **);
int GroundTruth(const char *, const char *, Graph *, int, int, int);

/* Function to Free memmory */
void Delete_Graph(Graph *);
void Delete_Query(Query *);
void Delete_GroundTruth(groundTruth *);

// Functions For Testing
void Test_RandomNumber();
void Test_RandomPermutation();
void Test_EuclideanDistance();
void Test_Set_Difference();
void Test_Init_Graph();
void Test_Init_Query();
void Test_Init_GroundTruth();
void TestReadTxt();
void Test_Medoid();
void Test_Argument_Min_Distance();
void Test_Greedy_Search();
void Test_Robust_Prune();
void Test_Vamana();
#endif