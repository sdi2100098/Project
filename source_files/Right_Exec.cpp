#include "Library.hpp"

#define GARBAGE 0

int Right_Exec(int argc, char **argv)
{

    if (argc != 7)
    { /* give less or more than the needed arguments */
        printf("Right Execution|Need 6 argument + ./build (7 in totall)\n");
        return 1;
    }

    int first_path = GARBAGE, secont_path = GARBAGE, k = GARBAGE, L = GARBAGE, R = GARBAGE;
    float a = GARBAGE;

    first_path = atoi(argv[1]);
    secont_path = atoi(argv[2]);

    if (first_path != GARBAGE || secont_path != GARBAGE)
    {
        printf("Right Execution|./build <base path> <query path> <k> <L> <R> <a>\n");
        return 1;
    }

    return 0;
}