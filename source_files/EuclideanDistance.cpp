#include <immintrin.h> // For AVX
#include <fun.hpp>
#include <math.h>

float EuclideanDistance(const float *vector_1, const float *vector_2, const int vectorSize) {
    __m256 sum_vec = _mm256_setzero_ps(); // Initialize a vector of zeros
    int index = 0;

    // Process 8 elements at a time
    for (; index <= vectorSize - 8; index += 8) {
        __m256 v1 = _mm256_loadu_ps(vector_1 + index); // Load 8 floats from vector_1
        __m256 v2 = _mm256_loadu_ps(vector_2 + index); // Load 8 floats from vector_2
        __m256 diff = _mm256_sub_ps(v1, v2);           // Compute differences
        __m256 sq = _mm256_mul_ps(diff, diff);         // Square differences
        sum_vec = _mm256_add_ps(sum_vec, sq);          // Accumulate squares
    }

    // Sum up the elements in the vector register
    alignas(32) float temp[8];
    _mm256_store_ps(temp, sum_vec);

    float sum = 0.0f;
    for (int i = 0; i < 8; i++) {
        sum += temp[i];
    }

    // Handle remaining elements
    for (; index < vectorSize; index++) {
        float difference = vector_1[index] - vector_2[index];
        sum += difference * difference;
    }

    return sqrtf(sum); // Use sqrtf for float precision
}