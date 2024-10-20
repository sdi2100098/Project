#include "Library.hpp"

result_greedy Greedy_Search(Graph *s, const float *x_q, int k, int L) {
    std::set<int> V; // Initialize the visited set
    std::vector<int> vector_L; // Candidate set L
    vector_L.push_back(0); // Assuming s->start node is 0 (this should be dynamic)

    std::vector<int> result; // Initialize result vector to store differences

    // Main loop
    while (!vector_L.empty()) {
        double min_distance = std::numeric_limits<double>::infinity();
        int closest_node = -1;

        // Find the closest node in vector_L that hasn't been visited
        for (int node : vector_L) {
            double dist = EuclidianDistance(s->nodes_array[node].vector, x_q, s->dimension);
            if (dist < min_distance) {
                min_distance = dist;
                closest_node = node;
            }
        }

        // Add closest node to visited set
        V.insert(closest_node);

        // Expand the search space by adding the neighbors (edges) of the closest node
        vector_L.insert(vector_L.end(), 
            s->nodes_array[closest_node].edges.begin(), 
            s->nodes_array[closest_node].edges.end());

        // If vector_L has grown beyond the limit L, retain the closest L points
        if (vector_L.size() > L) {
            std::vector<int> temp_vector;
            for (int i = 0; i < L; ++i) {
                double min_distance = std::numeric_limits<double>::infinity();
                int closest_temp_node = -1;

                // Find the closest point in vector_L
                for (int node : vector_L) {
                    double dist = EuclidianDistance(s->nodes_array[node].vector, x_q, s->dimension);
                    if (dist < min_distance) {
                        min_distance = dist;
                        closest_temp_node = node;
                    }
                }

                // Add this closest node to the temp_vector and remove it from vector_L
                temp_vector.push_back(closest_temp_node);
                vector_L.erase(std::remove(vector_L.begin(), vector_L.end(), closest_temp_node), vector_L.end());
            }

            // Replace vector_L with the closest L nodes
            vector_L = temp_vector;
        }

        // Calculate the set difference: vector_L - V (i.e., unvisited nodes)
        result.clear();
        std::set_difference(vector_L.begin(), vector_L.end(), V.begin(), V.end(), std::back_inserter(result));

        // If the result is empty, stop the loop
        if (result.empty()) {
            break;
        }
    }

    // Prepare the result to return
    result_greedy result_g;
    result_g.L = vector_L; // Final set of nodes
    result_g.V = V;        // Visited nodes set

    return result_g;
}