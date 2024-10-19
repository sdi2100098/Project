#include "Library.hpp"

std::set<int> Greedy_Search(Graph *s,const float *x_q,int *k,int L,int index) {
    std::set<int>V;
    std::set<int>set_L;
    set_L.insert(index);
    while (true) {
        float min;
        for(int i=0;i <size(set_L);i++) {
            float p = EuclidianDistance(s->nodes_array[index].vector,x_q,s->dimension);
            if(i == 0) {
                min = p;
            }
            else {
                if(min > p) {
                    min = p;
                }
            }
        }
        V.insert(index);
        set_L = s->nodes_array[index].edges;
    }
    return V;
}