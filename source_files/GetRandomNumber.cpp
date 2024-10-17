#include "Library.hpp"
int GetRandomNumber(const int max,const int exclude){
    int number;
    srand(time(NULL)); // make the seed
    do{
        number = rand() % max;
    }while(number == exclude); // if number is the same as exclude repeat
    return number;
}