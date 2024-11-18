#ifndef STRUCT_HPP
#define STRUCT_HPP

#include <set>
#include <vector>

#define NO_FILTER -1

typedef struct node{ /* node of each graph */
    int filter;
    float *vector;
    std::set<int> edges; // use set to have unique edges for every vector
}node;

typedef struct graph{
    node *index_array;   /* WTF HASH MAP */
    int R;               /* out-degree number */
    int number_of_indexes; /* rows */
    int dimension;       /* columns */
    std::vector<int> *Filters; /*An array to hold vectors base on their filters */ 
    int Filters_Size;
    //double **Distances;  /* Array to hold Distances*/
}Graph;

typedef struct query_node{
    int filter;
    float *vector;
}query_node;

typedef struct query{ /* DELULU IS NOT THE SOLULU ! STRUCTES > CLASSES */ // not true !
    query_node *index_array;
    int number_of_indexes; /* rows */
    int dimension;         /* columns */
    std::vector<int> *Filters; /*An array to hold vectors base on their filters */
    int Filters_Size;
    int NO_FILTERS_POTITION;
    //double **Distances;
}Query;

typedef struct neighbor{
    int K;
    int *K_NBH_array; //neighbor
}Neighbor;

typedef struct ground_truth{
    Neighbor *array;
    int Size;
}Ground_Truth;

#endif