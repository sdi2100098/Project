#include "fun.hpp"
#include <iostream>
#include <stdlib.h>

Result_greedy *Filtered_Greedy_Search(Graph *G, int xq, int k, int L, int *S, Query *Q){

    /* Initialize L <- 0 and V <- 0 */
    std::set<std::pair<double, int>> L_kal = {{}};
    std::set<std::pair<double, int>> Temp = {{}},MedoidSet = {{}};
    std::set<int> V = {};
    std::set<int> Difference_L_V = {};

    int p_star, i,filter;
    double distance;
    float *vector;

    /* Ground Truth */
    if (Q == NULL){
        vector = G->index_array[xq].vector;
        filter = G->index_array[xq].filter;
    }
    else{
        vector = Q->index_array[xq].vector;
        filter = Q->index_array[xq].filter;
        if(filter == -1)
            filter = rand() % (Q->Filters_Size-1);
    }


    for(int s = 0; s < G->Filters_Size; s++){ /* For every starting point in Medoids (only filters)*/
        distance = EuclideanDistance(G->index_array[s].vector,vector,G->dimension);
        if(Q == NULL && s == G->index_array[xq].filter){/* Not Graound Truth and F_s ∩ F_x */ 
            L_kal.insert({distance,S[s]});/* L <- L U {s} */
        }
        else if(Q != NULL && (s == Q->index_array[xq].filter || Q->index_array[xq].filter == -1)){/* Graound Truth */
            /* Has filter(or not) F_s ∩ F_x */
            L_kal.insert({distance,S[s]});/* L <- L U {s} */
        }
    }
    for(auto &element :L_kal)
        MedoidSet.insert({element.first,element.second}); // To store the Medoid starting nodes so we don't remove them later

    Set_Difference(&L_kal,&V,&Difference_L_V); /* Update diff */

    /* while L\V != 0 */
    while (Difference_L_V.size() != 0)
    {
        i = 0;

        /* p* <- atg min d(Xp,Xq) for p in L\V */
        p_star = Argument_Min_Distance(G, &Difference_L_V, vector);
        
        if(p_star == -1)
            p_star = S[filter];

        /* V <- V U {p*} */
        V.insert(p_star);


        /* Let Nout'(p*) <- {p'ε Νout(p*) : Fp' ∩ Fq != 0 ,p' not in V} */
        Temp.clear();
        for(std::set<int>::iterator it = G->index_array[p_star].edges.begin(); it != G->index_array[p_star].edges.end(); it++){ /* p'ε Νout(p*) */
            if(Q == NULL){ /* Not Ground Truth */
                if(G->index_array[*it].filter == G->index_array[xq].filter && V.find(*it) == V.end()){ /* Fp' ∩ Fq != 0 ,p' not in V */
                    distance = EuclideanDistance(G->index_array[*it].vector,vector,G->dimension);
                    Temp.insert({distance,*it});
                }
            }
            /* NOW WE MUST DO THE SAME IN CASE WE ARE IN GROUND TRUTH */
            else if(Q){
                if((G->index_array[*it].filter == Q->index_array[xq].filter || Q->index_array[xq].filter == -1) && V.find(*it) == V.end()){ /* Fp' ∩ Fq != 0 ,p' not in V */
                    distance = EuclideanDistance(G->index_array[*it].vector,vector,G->dimension);
                    Temp.insert({distance,*it});
                }
            }
        }

        for(std::set<std::pair<double,int>>::iterator it = Temp.begin(); it != Temp.end(); it++){ /* L <- L U Nout'(p*) */
            L_kal.insert({it->first, it->second});
        }

        if ((int)L_kal.size() > L){ /* |L kaligrafiko| > L */

            Temp.clear();
            /* L kaligrafiko retain closest L points to Xq */
            for (std::set<std::pair<double, int>>::iterator it = L_kal.begin(); it != L_kal.end() && i < L; i++, it++){
                Temp.insert({it->first, it->second});
            }

            L_kal.clear();
            for(auto &element : MedoidSet){
                if(V.find(element.second) == V.end())
                    L_kal.insert({element.first,element.second});
            }
            for (std::set<std::pair<double, int>>::iterator it = Temp.begin(); it != Temp.end(); it++)
            {
                L_kal.insert({it->first, it->second});
            }
        }
        Difference_L_V.clear();
        Set_Difference(&L_kal, &V, &Difference_L_V);
    }

    Result_greedy *RG = new Result_greedy;
    RG->L = {};

    i = 0;
    /* closect k points from L kaligrafiko + V */
    for (std::set<std::pair<double, int>>::iterator it = L_kal.begin(); it != L_kal.end() && i < k; i++, it++)
    {
        RG->L.insert({it->first, it->second});
    }
    RG->V = V;

    return RG;
}