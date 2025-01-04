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

    std::string base_path_string = config["base_path"].get<std::string>();
    const char *base_path = base_path_string.c_str();
    std::string query_path_string = config["query_path"].get<std::string>();
    const char *query_path =  query_path_string.c_str();
    std::string binary_output_path_string = config["binary_output_path"].get<std::string>();
    const char *binary_output_path = binary_output_path_string.c_str();

    Query Q;
    Graph G;

    if (Init_Graph_Data(&G, base_path) == 1)
        return 1;
    if (Init_Query_Data(&Q, query_path, G.Filters_Size) == 1)
        return 1;

    if (CreateKNNGraphBruteForce(&G, &Q, k, binary_output_path) == 1)
        goto precompute_error;

    Delete_Graph(&G);
    Delete_Query(&Q);

    return 0;

precompute_error:
    Delete_Graph(&G);
    Delete_Query(&Q);
    return 1;
}