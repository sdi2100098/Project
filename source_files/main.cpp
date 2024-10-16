#include "Library.hpp"

int main(){

    const char *base_filename = "Datasets/siftsmall_base.fvecs";
    const char *query_filename = "Datasets/siftsmall_query.fvecs";
    int count = 0;
    float **vectors_base ;
    float **vectors_query;
    int *num_vectors = (int*) malloc(2*sizeof(int));
    int *vector_dim = (int*) malloc(2*sizeof(int));
    Graph G;

    //give the R VERY IMPORTANT
    G.R = 2;

    Query Q;
    
    Init_Query_Data(query_filename,&Q);

    // G.nodes_array = Read_Data(,&G.number_of_nodes,); KLP

    printf("METADATA rows:%d colums:%d\n",Q.number_of_vectors,Q.dimension);



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