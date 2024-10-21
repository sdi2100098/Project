#include "Library.hpp"

result_greedy* Greedy_Search(Graph *s, const float *x_q, int k, int L) {
    int minvalue,count = 0;
    double min, p;
    std::set<int> V; // Visited nodes
    std::set<int> Lset; 
    std::vector<int> temp_vector;
    std::vector<int> result={0};

    // Initialize Lset with the starting node
    Lset.insert(0); 

    // Continue until Lset is empty
    while (!result.empty()) {
        // Reset temp vector for this iteration
        temp_vector.clear();
        min = std::numeric_limits<double>::infinity();
        
        // Find the closest node in Lset
        for (int value : result) {
            p = EuclidianDistance(s->nodes_array[value].vector, x_q, s->dimension);
            if (min > p) {
                min = p;
                minvalue = value;
            }
        }

        // Insert the found closest node into the visited set
        V.insert(minvalue);

        for (auto &OutEdge : s->nodes_array[minvalue].edges) 
            Lset.insert(OutEdge);

        // If Lset exceeds L, prune it
        if (Lset.size() > L) {
            while(1){
                min = std::numeric_limits<double>::infinity();
                for (int value : Lset) {
                    p = EuclidianDistance(s->nodes_array[value].vector, x_q, s->dimension);
                    if (min > p) {
                        min = p;
                        minvalue = value;
                    }
                }
                temp_vector.push_back(minvalue);
                Lset.erase(minvalue);
                if(temp_vector.size()==L)
                    break;
            }
            // Clear Lset and add back only the closest L elements
            Lset.clear();
            for (auto &element : temp_vector)
                Lset.insert(element);
        }

        // Prepare result for closest neighbors (Optional)
        result.clear();
        std::set_difference(Lset.begin(), Lset.end(), V.begin(), V.end(), std::back_inserter(result));

    }
    temp_vector.clear();
    while(1){
        min = std::numeric_limits<double>::infinity();
        for (int value : Lset) {
            p = EuclidianDistance(s->nodes_array[value].vector, x_q, s->dimension);
            if (min > p) {
                min = p;
                minvalue = value;
            }
        }
        temp_vector.push_back(minvalue);
        Lset.erase(minvalue);
        if(temp_vector.size() == k)
            break;
    }
    

    // Prepare the result structure to return
    result_greedy* result_g = new result_greedy;
    
    for(auto &LsetElement : temp_vector){
        result_g->L.insert(LsetElement);
    }
    result_g->V = V;
    return result_g;
}
