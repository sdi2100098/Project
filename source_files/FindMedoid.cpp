#include "fun.hpp"

int FindMedoid(Graph *G,int t,std::unordered_map<float,int> *M){
    /*Initiaalize M be an empty map*/
    std::unordered_map<float,int> Result_Map;
    std::unordered_map<float,int> T;
    std::vector<int> P_f;

    /*Initializze T to a zero map , T is intended as a counter*/
    for(int i = 0; i < G->number_of_nodes; i++)
        T[i] = 0 ;

    /*foreach f in F, the set of all filters*/
    for(int i = 0; i < G->Filters_Size; i++){
        /*Let P_f denote the ids of all points matching filter f*/
        P_f = G->Filters[i];

        /*Let R_f <--t randomyl sampled data point ids from P_f*/
    }


    //Return M
    *M = Result_Map;

    //All is Good
    return 0;
}