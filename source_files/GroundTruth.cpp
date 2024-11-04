#include "Library.hpp"

int GroundTruth(const char *Query_path, const char *Ground_Truth_path, Graph *G, int k, int L, int s)
{

    std::cout << std::endl;
    std::set<int> Temp_Set = {};
    int result, sum, accuracy = 0;
    groundTruth GT = {.array = NULL, .size = 0};
    Query Q = {.vectors_array = NULL, .number_of_vectors = 0, .dimension = 0};

    result = Init_Query_Data(Query_path, &Q);
    if (result == 1)
        return 1;

    result = Init_Ground_Truth_Data(Ground_Truth_path, &GT);
    if (result == 1)
        return 1;

    result_greedy *Result;

    for (int i = 0; i < Q.number_of_vectors; i++)
    {
        sum = 0;
        Result = Greedy_Search(G, Q.vectors_array[i], k, L, s); // Use for each vector of the graph the greedy search function

        Temp_Set.clear();
        for (std::set<std::pair<double, int>>::iterator it = Result->L.begin(); it != Result->L.end(); it++)
        {
            Temp_Set.insert(it->second);
        }
        // Seeing if the vectors of the groundtruth and the query are the same
        for (int j = 0; j < GT.size; j++)
        {
            if (Temp_Set.find(GT.array[i][j]) != Temp_Set.end())
            {
                sum++;
            }
        }
        if ((double)sum / Temp_Set.size() >= 0.9)
        {
            printf("\033[0;32m");
            accuracy++;
        }
        else
            printf("\033[0;31m");
        std::cout << "Accuracy index" << i << " : " << (double)sum / Temp_Set.size() * 100 << "%" << std::endl;
        delete Result;
    }
    if (accuracy >= 90)
        printf("\033[0;32m");
    else
        printf("\033[0;31m");
    printf("Tottal Accuracy %d\n", accuracy); // Accuracy needs to be > 0.9*number_of_vectors
    printf("\033[0m");

    Delete_Query(&Q);
    Delete_GroundTruth(&GT);
    return 0;
}
