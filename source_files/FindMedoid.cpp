#include "fun.hpp"
#include <stdlib.h>
#include <limits>


int FindMedoid(Graph *G,int t,std::unordered_map<int,int> *Vamana_Map){
    /*Initiaalize M be an empty map*/
    int RandomNum,RandomIndex;
    std::unordered_map<int,int> M;
    std::unordered_map<int,int> T;
    std::vector<int> P_f;
    std::set<int> R_f;
    int p_tonos , MinValue ;

    /*Initializze T to a zero map , T is intended as a counter*/
    for(int i = 0; i < G->number_of_nodes; i++)
        T[i] = 0 ;


    /*foreach f in F, the set of all filters*/
    for(int i = 0; i < G->Filters_Size; i++){
        /*Let P_f denote the ids of all points matching filter f*/
        P_f = G->Filters[i];
        
        //Error if t exceeds the Elements of Vector
        if((int)P_f.size() < t)
            return 1; 

        /*Let R_f <--t randomly sampled data point ids from P_f*/   
        R_f.clear();
        while((int)R_f.size() < t){
            RandomIndex = rand()%G->Filters[i].size();
            RandomNum = G->Filters[i][RandomIndex];
            R_f.insert(RandomNum);
        }

        /*p_tonos <-- arg min for p in R_f T[p]*/
        MinValue = std::numeric_limits<int>::max();
        for(auto &element : R_f){
            if(T[element] < MinValue){
                MinValue = T[element];
                p_tonos = element;
            }
        }

        /*Update M[f]<-- p_tonos and T[p_tonos] <-- T[p_tonos] + 1*/
        M[i] = p_tonos;
        T[p_tonos]++;
    }


    //Return M
    *Vamana_Map = M;

    //All is Good
    return 0;
}