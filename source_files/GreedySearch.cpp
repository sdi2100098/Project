#include "Library.hpp"

result_greedy Greedy_Search(Graph *s,const float *x_q,int *k,int L) {
    std::set<int>V = {}; //Initialize the sets
    std::vector<int>vector_L ; 
    vector_L.push_back(0); //Insert s
    std::vector<int> result;
    while (!result.empty()) {
        double min = std::numeric_limits<double>::infinity();
        int minvalue;
        for(int value : vector_L) {
            double p = EuclidianDistance(s->nodes_array[value].vector,x_q,s->dimension);
            if(min > p) {
                min = p;
                minvalue = value;
            }

        }
        V.insert(minvalue);
        std::copy(*(s->nodes_array[minvalue].edges.begin()),*(s->nodes_array[minvalue].edges.end()), std::back_inserter(vector_L));
        if(vector_L.size() > L) {
            std::vector<int>temp_vector;
            for(int i = 0;i < L;i++) {
                double min = std::numeric_limits<double>::infinity();
                int minvalue;
                for(int value : vector_L) {
                    double p = EuclidianDistance(s->nodes_array[value].vector,x_q,s->dimension);
                    if(min > p) {
                        min = p;
                        minvalue = value;
                    }
                }
                temp_vector.push_back(minvalue);

                auto newEnd = std::remove(vector_L.begin(), vector_L.end(), minvalue);
                vector_L.erase(newEnd, vector_L.end());
            }
            vector_L.clear();
            vector_L = temp_vector;
        }
        std::set_difference(vector_L.begin(), vector_L.end(),V.begin(), V.end(),std::back_inserter(result));
    }
    result_greedy result_g;
    result_g.L = vector_L;
    result_g.V = V;
    return result_g;
}