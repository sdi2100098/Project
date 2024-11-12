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
    Delete_Graph(&G);

    return 0;
}