#include "struct.hpp"
#include "fun.hpp"
#include "json.hpp"

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <iterator>

using json = nlohmann::json;

int main()
{

    // Open the JSON configuration file
    std::ifstream configFile("Config_File/config.json"); // Ensure this is the correct path to your JSON file
    if (!configFile.is_open())
    {
        std::cerr << "Could not open config.json" << std::endl;
        return 1;
    }

    // Define a JSON object and read from the file
    json config;
    configFile >> config;
    configFile.close();

    int R = config["R"];
    int L = config["L"];
    int k = config["k"];
    double a = config["a"];

    const char *base_path = "Datasets/Small_Set/dummy-data.bin";
    const char *query_path = "Datasets/Small_Set/dummy-queries.bin";

    //const char *output_path = "Datasets/Small_Set/dummy-groundtruth.txt";
    const char *binary_output_path = "Datasets/Small_Set/dummy-groundtruth.bin";

    Graph G;
    //Query Q;
    //Ground_Truth GT;
    int *Map;



    Map = Filtered_Vamana(base_path, &G, L, R, a);
    if(!Map)
        return 1;
    if(GroundTruth(query_path,binary_output_path,&G,k,L,Map)==1)
        return 1;

    // printf("filters %d\n",G.Filters_Size);

    // if(Init_Graph_Data(&G,base_path) == 1)
    //     return 1;

    // if(Init_Query_Data(&Q, query_path, G.Filters_Size) == 1)
    //     return 1;

    // if(Init_Ground_Truth_Data(&GT,binary_output_path) == 1)
    //     return 1;


    // int x;
    // for(int i = 0; i < Q.Filters_Size; i++){
    //     printf("\n\nFilter %d\n",i);
    //     for(int j = 0; j < (int)Q.Filters[i].size(); j++){
    //         x = Q.Filters[i][j];
    //         printf("Query %d| ",x);
    //         for(int k = 0; k < GT.array[x].K; k++){
    //             printf("%d ",GT.array[x].K_NBH_array[k]);
    //         }
    //         printf("\n");
    //     }
    // }

    // for(int i = 0; i < GT.Size; i++){
    //     printf("Query %d|",i);
    //     for(int j = 0; j < GT.array[i].K; j++){
    //         printf("%d ",GT.array[i].K_NBH_array[j]);
    //     }
    //     printf("\n");
    // }
    // printf("\n");

    // for(int i = 0; i < Q.number_of_indexes; i++)
    //     printf("%d ",Q.index_array[i].filter);
    // printf("\n");

    // int sum = 0;
    // for (int i = 0; i < Q.Filters_Size; i++)
    // {
    //     sum += Q.Filters[i].size();
    //     if (Q.Filters[i].size() != 0)
    //         printf("%d = %d\n", i, (int)Q.Filters[i].size());
    // }
    // printf("\nSum = %d\n", sum);

    // int *Vamana_Map;
    // int Vamana_Map_Size = G.Filters_Size;
    // Vamana_Map = FindMedoid(&G, 0.9);
    // for (int i = 0; i < Vamana_Map_Size; i++)
    // {
    //     std::cout << "Key : " << i << " Value : " << Vamana_Map[i] << std::endl;
    // }




    //Done
    //CreateKNNGraphBruteForce(&G,&Q,100,output_path,binary_output_path);



    //printf("%d\n",Q.usefull_number_of_indexes);

    // int *Vamana_Map ;
    // int Vamana_Map_Size = G.Filters_Size;
    // Vamana_Map = FindMedoid(&G,0.9);
    // for(int i = 0; i<Vamana_Map_Size; i++){
    //     std::cout << "Key : " << i << " Value : " << Vamana_Map[i] << std::endl;
    // }
    
    // Delete_Query(&Q);
    Delete_Graph(&G);
    // Delete_Ground_Truth(&GT);
    //free(Vamana_Map);

    return 0;
}