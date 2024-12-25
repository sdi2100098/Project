#include "fun.hpp"

float Distance_Function(float *Distances,const float *vector_1,const float *vector_2,const int Index,const int Dimension){
    float Distance;
    
    if(Distances[Index]==-1.0f){
        Distance = EuclideanDistance(vector_1,vector_2,Dimension);
        Distances[Index] = Distance;
    }
    else
        Distance = Distances[Index];

    return Distance;
}