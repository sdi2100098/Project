#include "Library.hpp"
#define M (1ULL << 32)

int Hash(Query *query) {
    int p = 10;
    int hash = 0;
    for(int i = query->dimension;i = 1;i--) {
        hash = hash + floor(query->number_of_vectors*pow(p,query->dimension - i));
    }
    hash = hash % M;
}