#include "struct.hpp"
#include "fun.hpp"

#include <stdio.h>
#include <iostream>
#include <iterator>


int main(){

    const char *base_path = "Datasets/Small_Set/dummy-data.bin";
    const char *query_path = "Datasets/Small_Set/dummy-queries.bin"; 

    Graph G;
    Query Q;

    if(Init_Graph_Data(&G,base_path) == 1) return 1;

    //printf("filters %d\n",G.Filters_Size);

    if(Init_Query_Data(&Q,query_path,G.Filters_Size) == 1) return 1;

    int sum = 0;
    for(int i = 0; i < Q.Filters_Size; i++){
        sum += Q.Filters[i].size();
        if(Q.Filters[i].size() != 0)
            printf("%d = %d\n",i,(int)Q.Filters[i].size());
    }
    printf("\nSum = %d\n",sum);

    // CreateKNNGraphBruteForce(G,100,"Datasets/Small_Set/dummy-groundtruth.txt","Datasets/Small_Set/dummy-groundtruth.bin");
    // std::unordered_map<int,int> Vamana_Map;
    // std::cout << FindMedoid(&G,1,&Vamana_Map) << std::endl;
    
    Delete_Query(&Q);
    Delete_Graph(&G);

    return 0;
}