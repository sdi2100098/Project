#include "Library.hpp"

int main()
{

    const char *base_filename = "Datasets/siftsmall_base.fvecs";
    const char *query_filename = "Datasets/siftsmall_query.fvecs";
    int count = 0;
    int return_number, fun_result = -1, fun_result_query, check = 0;
    Graph G;

    Query Q;

    // fun_result_query = Init_Query_Data(query_filename, &Q);

    // L = 30, R = 20
    fun_result = Vamana(base_filename, &G, 30, 20);
    std::cout << "Check if all went well : " << fun_result << std::endl;
    std::cout << "Printing number of edges after Vamana : " << G.nodes_array[15].edges.size();
    std::cout << std::endl;

    // check = CallThread(&G);
    // std ::cout << "Medoid : " << check << std::endl;
    // std::cout << "Now Printing Results from Greedy Function " << std::endl;
    // result_greedy *GreedyFunction = NULL;
    // GreedyFunction = Greedy_Search(&G, 15, 20, 30);
    // std::cout << "Visited Nodes : ";
    // for (auto &V_element : GreedyFunction->V)
    //     std::cout << V_element << " ";
    // std::cout << std::endl;
    // std::cout << "Visited Nodes Size : " << GreedyFunction->V.size() << std::endl;
    // std::cout << "L Set : ";
    // for (auto &L_element : GreedyFunction->L)
    //     std::cout << L_element << " ";
    // std ::cout << std::endl;
    // std::cout << "L Set Size : " << GreedyFunction->L.size() << std::endl;
    // std::cout << "Printing number of edges before : " << G.nodes_array[15].edges.size();
    // std::cout << std::endl;
    // Robust_Prune(15, &(GreedyFunction->V), 1.1, &G);
    // std::cout << "Printing number of edges after Robust Prune : " << G.nodes_array[15].edges.size();
    // std::cout << std::endl;

    // delete GreedyFunction;

    Delete_Graph(&G);

    return 0;
}