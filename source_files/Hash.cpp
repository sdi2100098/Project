#include "Library.hpp"
#define M (1ULL << 32) //Define a large number
#define P 31 //Define a prime number

int Hash(const float *vector_array,int dimension) {
    int hash = 0; //Initialize the hash 
    for(int i = 0;i <= dimension-1;i++) {
        double d = (double)vector_array[i];//Covert the float to double for more accuracy
        hash = hash + (d * pow(P,i));
    }
    hash = floor(hash);
    hash = hash % M;
    return hash;
}