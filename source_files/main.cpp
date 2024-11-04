#include "Library.hpp"

int main(int argv, char **argc)
{
    const char *base_filename = "Datasets/Small_Set/siftsmall_base.fvecs";
    const char *query_filename = "Datasets/Small_Set/siftsmall_query.fvecs";
    const char *ground_truth_filename = "Datasets/Small_Set/siftsmall_groundtruth.ivecs";
    int count = 0, s;
    int return_number, fun_result = -1, fun_result_query, check = 0;
    Graph G;

    // int x = 0;
    // x = Right_Exec(argv, argc);

    // return x;

    s = Vamana(base_filename, &G, 200, 25);
    fun_result = GroundTruth(query_filename, ground_truth_filename, &G, 100, 200, s);

    Delete_Graph(&G);

    return 0;
}