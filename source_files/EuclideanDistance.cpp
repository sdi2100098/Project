#include <math.h>
#include "fun.hpp"

double EuclideanDistance(const float *vector_1, const float *vector_2, const int vectorSize)
{
    double sum = 0.0;
    double difference = 0.0;
    for (int index = 0; index < vectorSize; index++)
    {
        difference = (double)vector_1[index] - vector_2[index]; // calculate the difference (x0-x1)
        sum += (difference * difference);                       // pow(difference, 2);                              // raise the difference to the power of 2 (x0-x1)^2
    }
    return sqrt(sum); // return the correct Euclidean Distance
}