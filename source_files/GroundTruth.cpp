#include "fun.hpp"
#include <iostream>

int GroundTruth(const char *Query_path, const char *Ground_Truth_path, Graph *G, int k, int L, int *S)
{

    std::cout << std::endl;
    std::set<int> Temp_Set = {};
    int result, sum, accuracy = 0;
    Ground_Truth GT;
    Query Q;

    result = Init_Query_Data(&Q, Query_path, G->Filters_Size);
    if (result == 1)
        return 1;

    result = Init_Ground_Truth_Data(&GT, Ground_Truth_path);
    if (result == 1)
        return 1;

    Result_greedy *Result;

    for (int i = 0; i < Q.number_of_indexes; i++)
    {
        sum = 0;
        Result = Filtered_Greedy_Search(G, i, k, L, S, &Q); // Use for each vector of the graph the greedy search function

        Temp_Set.clear();
        for (std::set<std::pair<float, int>>::iterator it = Result->L.begin(); it != Result->L.end(); it++)
        {
            Temp_Set.insert(it->second);
        }
        // Seeing if the vectors of the groundtruth and the query are the same
        for (int j = 0; j < GT.array[i].K; j++)
        {
            if (Temp_Set.find(GT.array[i].K_NBH_array[j]) != Temp_Set.end())
            {
                sum++;
            }
        }
        if ((double)sum / GT.array[i].K >= 0.9)
        {
            accuracy++;
        }
        else
            delete Result;
    }
    if ((double)accuracy / Q.number_of_indexes >= 0.9)
        printf("\033[0;32m");
    else
        printf("\033[0;31m");
    printf("%d/%d Passed Test", accuracy, Q.number_of_indexes); // Accuracy needs to be > 0.9*number_of_indexes
    std::cout << " ~= " << (int)((accuracy / (double)Q.number_of_indexes) * 100) << "%\n" << std::endl;
    printf("\033[0m");

    Delete_Query(&Q);
    Delete_Ground_Truth(&GT);
    return 0;
}