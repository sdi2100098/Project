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

    int threshold = 1;
    int L_small = config["L_small"];
    int R_small = config["R_small"];
    int R_stitched = config["R_stitched"];
    double a = config["a"];

    std::string base_path_string = config["base_path"].get<std::string>();
    const char *base_path = base_path_string.c_str();
    
    std::string graph_binary_path_string = config["graph_binary_path"].get<std::string>();
    const char *graph_binary_path = graph_binary_path_string.c_str();

    Graph G;
    int *Map;

    /*Initialize G to an Empty Graph*/
    int result = Init_Graph_Data(&G, base_path, true);

    if (result == 1)
    {
        perror("Error in Init_Graph");
        return 1;
    }
    
    StichedVamana(&G, L_small, R_small, R_stitched, a);
    Map = FindMedoid(&G, threshold);
    if (!Map)
    {
        Delete_Graph(&G, true);
        return 1;
    }
    saveGraphToBinaryFile(&G,Map,graph_binary_path);
    Delete_Graph(&G, true);

    return 0;
}