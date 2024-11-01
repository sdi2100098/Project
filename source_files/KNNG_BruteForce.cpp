#include "Library.hpp"

void CreateKNNGraphBruteForce(Graph G,int k){
    FILE *output_file = fopen("Datasets/Test_Set/Test_groundtruth.txt","w");
    if(output_file == NULL){
        perror("Error oopening file");
        return;
    }
    for(int i = 0 ; i < G.number_of_nodes; i++){
        G.nodes_array[i].edges.clear();
        std::vector<std::pair<double, int>> closest_neighbors;
        for(int j =0; j< G.number_of_nodes ; j++){
            if(i!=j){
                double distance = EuclidianDistance(G.nodes_array[i].vector,G.nodes_array[j].vector,G.dimension);
                closest_neighbors.push_back({distance,j});
            }
        }
        std::sort(closest_neighbors.begin(),closest_neighbors.end());
        for(int l = 0; l < k ; l++){
            G.nodes_array[i].edges.insert(closest_neighbors[l].second);
            fprintf(output_file, "%d ", closest_neighbors[l].second);
        }
        fprintf(output_file, "\n");
    }
}