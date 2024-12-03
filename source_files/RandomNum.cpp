#include <fun.hpp>
#include <time.h>
#include <stdlib.h>

int GetRandomNumber(const int max, const int exclude)
{
    int number;
    number = rand() % max;
    return number;
}
