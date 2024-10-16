#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <iostream>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <fstream>
#include <vector>
#include <string>
#include <cassert>
#include <iomanip>  // Include this header for std::fixed and std::setprecision
#include <cstdlib>  // For malloc and free
#include <cassert>  // For assert
#include <cmath> // for the sqrt and pow


typedef struct node { /* node of each graph */ 
    float* vector;
    int* edges;
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



int Init_Graph_Data(const char *file_path, Graph *graph);
int Init_Query_Data(const char *file_path, Query *query);

void free_fvecs(float **,int);
float EuclidianDistance(const float *,const float *,const int );

#endif