#include "fun.hpp"
#include <time.h>
#include <stdlib.h>
#include <iostream>

int* StichedVamanaIndexing(const char *file_path, Graph *G, int L_small, int R_small,int R_stitched, double a) {
    int *s = NULL;
    Result_greedy *result_greedy = NULL;
    /*Initialize G to an Empty Graph*/
    int result = Init_Graph_Data(G, file_path);
    if (result == 1)
    {
        perror("Error in Init_Graph");
        return NULL;
    }

    
}