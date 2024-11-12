#ifndef STRUCT_HPP
#define STRUCT_HPP

#include <set>
#include <vector>


typedef struct node{ /* node of each graph */
    int filter;
    float *vector;
    std::set<int> edges; // use set to have unique edges for every vector
}node;

typedef struct graph{
    node *nodes_array;   /* WTF HASH MAP */
    int R;               /* out-degree number */
    int number_of_nodes; /* rows */
    int dimension;       /* columns */
    std::vector<int> *Filters; /*An array to hold vectors*/ 
    int Filters_Size;
    //double **Distances;  /* Array to hold Distances*/
}Graph;

typedef struct query_node{
    int filter;
    float *vector;
}query_node;

typedef struct query{ /* DELULU IS NOT THE SOLULU ! STRUCTES > CLASSES */ // not true !
    query_node *nodes_array;
    int number_of_nodes; /* rows */
    int dimension;         /* columns */
    //double **Distances;
}Query;


#endif