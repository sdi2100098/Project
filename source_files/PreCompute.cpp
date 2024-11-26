#include "fun.hpp"
#include "json.hpp"

#include <stdio.h>
#include <iostream>
#include <fstream>

using json = nlohmann::json;

int main()
{

    /*
    Creat 3 .bin files
    1)dummy-groundtruth.bin ,we compute the K(number) of Nearest Neighboors
    2)precompute_Graph.bin ,we compute all the posible destances in Graph (every vector with every vector) n=#vector ,nxn array
    3)precompute_Query.bin ,same as above but only with query (every query with evey in base) #number of vectors in Graph x #number of querys
    */

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

    int k = config["k"];

    const char *base_path = "Datasets/Small_Set/dummy-data.bin";
    const char *query_path = "Datasets/Small_Set/dummy-queries.bin";

    const char *output_path = "Datasets/Small_Set/dummy-groundtruth.txt";
    const char *binary_output_path = "Datasets/Small_Set/dummy-groundtruth.bin";

    Query Q;
    Graph G;

    if (Init_Graph_Data(&G, base_path, false) == 1)
        return 1;
    if (Init_Query_Data(&Q, query_path, G.Filters_Size, false) == 1)
        return 1;

    if (CreateKNNGraphBruteForce(&G, &Q, k, output_path, binary_output_path) == 1)
        goto precompute_error;

    if (Graph_Graph_Dinstance_Precompute(&G) == 1)
        goto precompute_error;

    if (Graph_Query_Dinstance_Precompute(&G, &Q) == 1)
        goto precompute_error;

    // Delete_Graph(&G);
    // Delete_Query(&Q);

    return 0;

precompute_error:
    // Delete_Graph(&G);
    // Delete_Query(&Q);
    return 1;
}