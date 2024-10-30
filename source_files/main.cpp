#include "Library.hpp"

int main(int argv, char **argc)
{
    srand(time(NULL)); // make the seed
    const char *base_filename = "Datasets/Small_Set/siftsmall_base.fvecs";
    const char *query_filename = "Datasets/Small_Set/siftsmall_query.fvecs";
    int count = 0;
    int return_number, fun_result = -1, fun_result_query, check = 0;
    Graph G;
    Query Q;
    
    int x = 0;
    x = Right_Exec(argv,argc);

    return x;

    return 0;

    fun_result = Vamana(base_filename, &G, 30, 20);
    

    Delete_Graph(&G);

    return 0;
}