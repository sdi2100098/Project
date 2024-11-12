#include "struct.hpp"
#include "fun.hpp"

#include <stdio.h>
#include <iostream>
#include <iterator>
#include <set>


int main(){

    const char *base_path = "Datasets/Small_Set/dummy-data.bin";

    printf("Main %s\n",base_path);

    Graph G;

    if(Init_Graph_Data(&G,base_path) == 1) return 1;
    std::unordered_map<int,int> Vamana_Map;
    std::cout << FindMedoid(&G,1,&Vamana_Map) << std::endl;
    for(auto &key : Vamana_Map){
        std::cout << "Key : " << key.first << " Value : " << key.second << std::endl;
    }
    Delete_Graph(&G);

    return 0;
}