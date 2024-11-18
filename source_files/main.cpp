#include "struct.hpp"
#include "fun.hpp"

#include <stdio.h>
#include <iostream>
#include <iterator>


int main(){

    const char *base_path = "Datasets/Small_Set/dummy-data.bin";
    const char *query_path = "Datasets/Small_Set/dummy-queries.bin"; 

    const char *output_path = "Datasets/Small_Set/dummy-groundtruth.txt";
    const char *binary_output_path = "Datasets/Small_Set/dummy-groundtruth.bin";

    Graph G;
    Query Q;
    Ground_Truth GT;

    if(Init_Graph_Data(&G,base_path) == 1) return 1;
    if(Init_Query_Data(&Q,query_path,G.Filters_Size) == 1) return 1;

    //Done
    //CreateKNNGraphBruteForce(&G,&Q,100,output_path,binary_output_path);

    Init_Ground_Truth_Data(&GT,binary_output_path);


    //printf("%d\n",Q.usefull_number_of_indexes);

    // int *Vamana_Map ;
    // int Vamana_Map_Size = G.Filters_Size;
    // Vamana_Map = FindMedoid(&G,0.9);
    // for(int i = 0; i<Vamana_Map_Size; i++){
    //     std::cout << "Key : " << i << " Value : " << Vamana_Map[i] << std::endl;
    // }
    
    Delete_Query(&Q);
    Delete_Graph(&G);
    //free(Vamana_Map);

    return 0;
}