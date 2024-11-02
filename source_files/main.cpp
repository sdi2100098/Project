#include "Library.hpp"

int main(int argv, char **argc)
{
    srand(time(NULL)); // make the seed
    const char *base_filename = "Datasets/Small_Set/siftsmall_base.fvecs";
    const char *query_filename = "Datasets/Small_Set/siftsmall_query.fvecs";
    const char *ground_truth_filename = "Datasets/Small_Set/siftsmall_groundtruth.ivecs";
    int count = 0;
    int return_number, fun_result = -1, fun_result_query, check = 0;
    Graph G;



    // int x = 0;
    // x = Right_Exec(argv, argc);

    // return x;


    fun_result = Vamana(base_filename, &G, 150, 15);

    Delete_Graph(&G);

    return 0;
}