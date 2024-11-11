#ifndef STRUCT_HPP
#define STRUCT_HPP

#include <set>

typedef struct node
{ /* node of each graph */
    float filter;
    float *vector;
    std::set<int> edges; // use set to have unique edges for every vector
} node;

typedef struct graph
{
    node *nodes_array;   /* WTF HASH MAP */
    int R;               /* out-degree number */
    int number_of_nodes; /* rows */
    int dimension;       /* columns */
    //double **Distances;  /* Array to hold Distances*/
} Graph;


#endif