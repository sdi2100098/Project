#include "Library.hpp"

int main(int argc, char **argv)
{
    
    int fun_result = -1, s =-1;
    Graph G;

    // Create a JSON object to store parsed data
    Json::Value root;

    // Open the JSON file
    std::ifstream config_file("Config_File/config.json", std::ifstream::binary);
    config_file >> root;  // Read the JSON into 'root'

    const char *base_filename = "Datasets/Small_Set/siftsmall_base.fvecs";
    const char *query_filename = "Datasets/Small_Set/siftsmall_query.fvecs";
    const char *ground_truth_filename = "Datasets/Small_Set/siftsmall_groundtruth.ivecs";

    int k = root["k"].asInt();
    int L = root["L"].asInt();
    int R = root["R"].asInt();
    float a = root["a"].asFloat();
    
    
    s = Vamana(base_filename, &G, L, R,a);
    fun_result = GroundTruth(query_filename, ground_truth_filename, &G, k, L, s);


    Delete_Graph(&G);


    if(fun_result==1)
        return 1;

    return 0;
}