#include "Library.hpp"

int main(int argc, char **argv)
{
    
    int fun_result = -1, s =-1;
    Graph G;

    fun_result = Right_Exec(argc, argv);

     if(fun_result==1)
        return 1;

    const char *base_filename = "Datasets/Small_Set/siftsmall_base.fvecs";
    const char *query_filename = "Datasets/Small_Set/siftsmall_query.fvecs";
    const char *ground_truth_filename = "Datasets/Small_Set/siftsmall_groundtruth.ivecs";

    int k = atoi(argv[1]);
    int L = atoi(argv[2]);
    int R = atoi(argv[3]);
    float a = atof(argv[4]);
    
    
    s = Vamana(base_filename, &G, L, R,a);
    fun_result = GroundTruth(query_filename, ground_truth_filename, &G, k, L, s);


    Delete_Graph(&G);


    if(fun_result==1)
        return 1;

    return 0;
}