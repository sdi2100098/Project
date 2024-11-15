#include "struct.hpp"
#include "fun.hpp"

#include <stdio.h>
#include <iostream>
#include <iterator>
#include <set>


int main(){

    const char *base_path = "Datasets/Small_Set/dummy-data.bin";
    const char *query_path = "Datasets/Small_Set/dummy-queries.bin"; 

    Graph G;
    Query Q;

    if(Init_Graph_Data(&G,base_path) == 1) return 1;

    if(Init_Query_Data(&Q,query_path) == 1) return 1;

    // CreateKNNGraphBruteForce(G,100,"Datasets/Small_Set/dummy-groundtruth.txt","Datasets/Small_Set/dummy-groundtruth.bin");
    int *Vamana_Map ;
    int Vamana_Map_Size = G.Filters_Size;
    Vamana_Map = FindMedoid(&G,1);
    for(int i = 0; i<Vamana_Map_Size; i++){
        std::cout << "Key : " << i << " Value : " << Vamana_Map[i] << std::endl;
    }
    
    Delete_Query(&Q);
    Delete_Graph(&G);

    return 0;
}