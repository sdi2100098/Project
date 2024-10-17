#include "Library.hpp"
#define M (1ULL << 32) //Define a large number
#define P 31 //Define a prime number

int Hash(Query *query,int vector) {
    int hash = 0; //Initialize the hash 
    for(int i = query->dimension;i = 1;i--) {
        double d = (double)query->vectors_array[vector][query->dimension - i];//Covert the float to double for more accuracy
        hash = hash + (d * pow(P,query->dimension - i));
    }
    hash = floor(hash);
    hash = hash % M;
    return hash;
}