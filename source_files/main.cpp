#include "Library.hpp"
using json = nlohmann::json;

int main(int argc, char **argv)
{
    
    int fun_result = -1, s =-1;
    Graph G;


    // Open the JSON configuration file
    std::ifstream configFile("Config_File/config.json");  // Ensure this is the correct path to your JSON file
    if (!configFile.is_open()) {
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

    const char *base_filename = "Datasets/Small_Set/siftsmall_base.fvecs";
    const char *query_filename = "Datasets/Small_Set/siftsmall_query.fvecs";
    const char *ground_truth_filename = "Datasets/Small_Set/siftsmall_groundtruth.ivecs";
    
    
    s = Vamana(base_filename, &G, L, R,a);
    fun_result = GroundTruth(query_filename, ground_truth_filename, &G, k, L, s);


    Delete_Graph(&G);


    if(fun_result==1)
        return 1;

    return 0;
}