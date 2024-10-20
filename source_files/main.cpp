#include "Library.hpp"

int main(){

    const char *base_filename = "Datasets/siftsmall_base.fvecs";
    const char *query_filename = "Datasets/siftsmall_query.fvecs";
    int count = 0;
    int return_number, fun_result = -1;
    Graph G;

    //give the R VERY IMPORTANT
    G.R = 65;

    Query Q;
    

    // fun_result = Init_Query_Data(query_filename,&Q);

    // printf("%d\n",fun_result);

    //if(fun_result == 1) return 1;
    fun_result = Init_Graph_Data(base_filename,&G);


    /* SEE HOW A SET IS WORKING VIA A FUNCTION */
    std::set<int> x;
    x.insert(10);
    x.insert(3);
    x.insert(20);

    Test(&x);

    std::set<int>::iterator it;
    for(it = x.begin(); it != x.end(); it++)
        printf("%d,",*it);
    printf("\n");

    std::cout << "Now Printing Results from Greedy Function " << std::endl;
    result_greedy *GreedyFunction = new result_greedy;
    GreedyFunction = Greedy_Search(&G,G.nodes_array[15].vector,65,80);
    std::cout << "Visited Nodes : ";
    for(auto &V_element : GreedyFunction->V)
        std::cout << V_element << " ";
    std::cout << std::endl;
    std::cout << "Visited Nodes Size : " << GreedyFunction->V.size() << std::endl;
    std::cout << "L Set : ";
    for(auto &L_element : GreedyFunction->L)
        std::cout << L_element << " ";
    std :: cout << std::endl;
    std::cout << "L Set Size : " << GreedyFunction->L.size() << std::endl;


    // if (return_number)
    //     std :: cout << "Problem" << std::endl;
    // std :: cout << "All good" << std :: endl;
    // std :: cout << "METADATA rows : " << Q.number_of_vectors <<  " colums:" <<  Q.dimension << std::endl ;
    // for(int index = 0; index < 10; index ++){
    //     std::cout << "For index : " << index << std::endl;
    //     for(auto &element : G.nodes_array[index].edges)
    //         std :: cout << element << " ";
    //     std::cout << std::endl;
    // }
    // std::vector<int> array;
    // array = RandomPermutation(&G);
    // std :: cout << "Random Permuation : ";
    // for(auto &element : array)
    //     std :: cout << element << " ";
    // std :: cout << std::endl << "Count is : " << array.size() << std:: endl;


    // for(int i = 0; i < 5; i++){
    //     printf("\n");
    //     for(int j = 0; j < vector_dim[0]; j++){
    //         printf("%.1f ",vectors_base[i][j]);
    //     }
    // }


    // for(int i = 0; i < 10; i++){
    //     printf("\n");
    //     for(int j = 0; j < vector_dim[0]; j++){
    //         printf("%.4f ",vectors_base[i][j]);
    //     }
    // }
    // // Sample example for the Euclidian Distance
    // float vector_1[3] = {5,3,0};
    // float vector_2[3] = {2,-2,sqrt(2)};
    // int vectorSize = 3;
    // float distance = 0.0;
    // distance = EuclidianDistance(vector_1,vector_2,vectorSize);
    // std::cout << std::endl << "Calculate distance for two different vectors : ";
    // std::cout << distance << std::endl;
    delete GreedyFunction;
    return 0;
}