#include "Library.hpp"

int main(){

    const char *base_filename = "Datasets/siftsmall_base.fvecs";
    const char *query_filename = "Datasets/siftsmall_query.fvecs";
    int count = 0;
    int return_number, fun_result = -1;
    Graph G;

    //give the R VERY IMPORTANT
    G.R = 3;

    Query Q;
    

    // fun_result = Init_Query_Data(query_filename,&Q);

    // printf("%d\n",fun_result);

    //if(fun_result == 1) return 1;
    fun_result = Init_Graph_Data(base_filename,&G);



    std::set<int> test_set;
    test_set.insert(0);
    test_set.insert(30);
    test_set.insert(40);

    Robust_Prune(1,&test_set,1.1,&G);

    //printf("After Pnure %d\n",G.nodes_array[1].edges.size());



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
    return 0;
}