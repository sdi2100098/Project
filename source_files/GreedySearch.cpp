#include "Library.hpp"

std::set<int> Greedy_Search(Graph *s,const float *x_q,int &k,int L) {
    std::set<int>V = {}; //Initialize the sets
    std::set<int>set_L = {}; 
    set_L.insert(0); //Insert s
    while (true) {
        float min = 1000000000000;
        int minvalue;
        for(int value : set_L) {
            float p = EuclidianDistance(s->nodes_array[value].vector,x_q,s->dimension);
            if(min > p) {
                min = p;
                minvalue = value;
            }
        }
        V.insert(minvalue);
        set_L.clear();
        set_L.insert(s->nodes_array[minvalue].edges.begin(),s->nodes_array[minvalue].edges.end());
    }
    k = set_L.size();
    return V;
}