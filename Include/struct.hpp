#ifndef STRUCT_HPP
#define STRUCT_HPP

#include <set>
#include <vector>
#include <unordered_map>

typedef struct node
{ /* node of each graph */
    int filter;
    float *vector;
    std::set<int> edges; // use set to have unique edges for every vector
} node;

typedef struct graph
{
    node *nodes_array;   /* WTF HASH MAP */
    int R;               /* out-degree number */
    int number_of_nodes; /* rows */
    int dimension;       /* columns */
    std::vector<int> *Filters; /*An array to hold vectors*/ 
    int Filters_Size;
    //double **Distances;  /* Array to hold Distances*/
} Graph;


#endif