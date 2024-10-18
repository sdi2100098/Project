#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <iostream>
#include <stdbool.h>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <string>
#include <cassert>
#include <iomanip>  // Include this header for std::fixed and std::setprecision
#include <cstdlib>  // For malloc and free
#include <cassert>  // For assert
#include <cmath> // for the sqrt and pow
#include <time.h>
#include <set>


typedef struct node { /* node of each graph */ 
    float* vector;
    std::set<int> edges; // use set to have unique edges for every vector
}node;

typedef struct graph{
    node* nodes_array; /* WTF HASH MAP */
    int R; /* out-degree number */
    int number_of_nodes; /* rows */
    int dimension;  /* columns */
}Graph;

typedef struct query{ /* DELULU IS NOT THE SOLULU ! STRUCTES > CLASSES */
    float** vectors_array;
    int number_of_vectors; /* rows */
    int dimension; /* columns */
}Query;



int Init_Graph_Data(const char *, Graph *);
int Init_Query_Data(const char *, Query *);
int GetRandomNumber(const int ,const int );

void free_fvecs(float **,int);
float EuclidianDistance(const float *,const float *,const int );
int* Greedy_Search(node *s,Query *query,int k,int L);
int *RandomPermutation(Graph *);

#endif