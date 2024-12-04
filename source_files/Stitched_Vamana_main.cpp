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
    int k = config["k"];
    int L_small = config["L_small"];
    int L = config["L"];
    int R_small = config["R_small"];
    int R_stitched = config["R_stitched"];
    double a = config["a"];

    const char *base_path = "Datasets/Small_Set/dummy-data.bin";
    const char *query_path = "Datasets/Small_Set/dummy-queries.bin";
    const char *binary_output_path = "Datasets/Small_Set/dummy-groundtruth.bin";

    Graph G;
    int *Map;

    StichedVamana(base_path, &G, L_small, R_small, R_stitched, a);
    Map = FindMedoid(&G, threshold);
    if (!Map)
    {
        Delete_Graph(&G, true);
        return 1;
    }

    if (GroundTruth(query_path, binary_output_path, &G, k, L, Map) == 1)
    {
        free(Map);
        Delete_Graph(&G, true);
        return 1;
    }

    Delete_Graph(&G, true);

    return 0;
}