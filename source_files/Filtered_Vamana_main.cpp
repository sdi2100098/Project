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

    std::string base_path_string = config["base_path"].get<std::string>();
    const char *base_path = base_path_string.c_str();
    std::string query_path_string = config["query_path"].get<std::string>();
    const char *query_path =  query_path_string.c_str();
    std::string binary_output_path_string = config["binary_output_path"].get<std::string>();
    const char *binary_output_path = binary_output_path_string.c_str();
    std::string graph_binary_path_string = config["graph_binary_path"].get<std::string>();
    const char *graph_binary_path = graph_binary_path_string.c_str();

    Graph G;
    /*Initialize G to an Empty Graph*/
    int result = Init_Graph_Data(&G, base_path, true);
    if (result == 1)
    {
        perror("Error in Init_Graph");
        return 1;
    }
    int *Map;

    Map = Filtered_Vamana(&G, L, R, a);
    if (!Map)
    {
        Delete_Graph(&G, true);
        return 1;
    }
    saveGraphToBinaryFile(&G,Map,graph_binary_path);
    Delete_Graph(&G, true);

    return 0;
}