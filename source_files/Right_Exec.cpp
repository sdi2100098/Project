#include "Library.hpp"

#define GARBAGE 0

int Right_Exec(int argc, char **argv)
{

    if (argc != 5)
    { /* give less or more than the needed arguments */
        printf("Right Execution|Need 4 argument + ./build (5 in totall)\n");
        return 1;
    }

    int  k = GARBAGE, L = GARBAGE, R = GARBAGE;
    float a = GARBAGE;

    
    k = atoi(argv[1]);
    L = atoi(argv[2]);
    R = atoi(argv[3]);

    a = atof(argv[4]);

    if (k == GARBAGE || L == GARBAGE || R == GARBAGE || a == GARBAGE)
    {
        printf("Right Execution|./build <k> <L> <R> <a>\n");
        return 1;
    }

    if(R < 0 || L < 0 || k < 0 || a < 0){
        printf("Numerical Arguments must be positive\n");
        return 1;
    }
    
    if(L < k){
        printf("L must be greater than or equal to k\n");
        return 1;
    }

    if(a < 1){
        printf("a must be greater or equal to 1\n");
        return 1;
    }

    if(R < 12){
        printf("R must be at least equal to 13\n");
        return 1;
    }

    return 0;
}