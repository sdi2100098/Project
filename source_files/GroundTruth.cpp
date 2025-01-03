#include "fun.hpp"
#include <iostream>
#include <chrono>

int GroundTruth(const char *Query_path, const char *Ground_Truth_path, Graph *G, int k, int L, int *S)
{
    std::cout << std::endl;
    std::set<int> Temp_Set = {};
    int result, sum, accuracy_filtered = 0, accuracy_unfiltered = 0;
    Ground_Truth GT;
    Query Q;

    result = Init_Query_Data(&Q, Query_path, G->Filters_Size);
    if (result == 1)
        return 1;

    result = Init_Ground_Truth_Data(&GT, Ground_Truth_path);
    if (result == 1)
        return 1;

    Result_greedy *Result;

    double total_time_filtered = 0.0;
    double total_time_unfiltered = 0.0;
    int filtered_count = 0, unfiltered_count = 0;

    for (int i = 0; i < Q.number_of_indexes; i++)
    {
        sum = 0;
        Result = Filtered_Greedy_Search(G, i, k, L, S, &Q); // Greedy search

        Temp_Set.clear();
        for (std::set<std::pair<float, int>>::iterator it = Result->L.begin(); it != Result->L.end(); it++)
        {
            Temp_Set.insert(it->second);
        }

        // Track time for query processing
        auto start_time = std::chrono::high_resolution_clock::now();

        // Check if the query is filtered or unfiltered
        if (Q.index_array[i].filter == -1) // Unfiltered query
        {
            unfiltered_count++;
            // Comparing with Ground Truth
            for (int j = 0; j < GT.array[i].K; j++)
            {
                if (Temp_Set.find(GT.array[i].K_NBH_array[j]) != Temp_Set.end())
                {
                    sum++;
                }
            }
            if ((double)sum / GT.array[i].K >= 0.9)
                accuracy_unfiltered++;
        }
        else // Filtered query
        {
            filtered_count++;
            // Comparing with Ground Truth
            for (int j = 0; j < GT.array[i].K; j++)
            {
                if (Temp_Set.find(GT.array[i].K_NBH_array[j]) != Temp_Set.end())
                {
                    sum++;
                }
            }
            if ((double)sum / GT.array[i].K >= 0.9)
                accuracy_filtered++;
        }

        // Calculate the time taken for this query (filtered or unfiltered)
        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end_time - start_time;
        if (Q.index_array[i].filter == -1)
        {
            total_time_unfiltered += duration.count();
        }
        else
        {
            total_time_filtered += duration.count();
        }

        delete Result;
    }

    // Calculate the accuracy and print the results
    printf("\033[0;32m");
    printf("\nUnfiltered Queries Accuracy: %d/%d Passed Test", accuracy_unfiltered, unfiltered_count);
    if((double) accuracy_unfiltered / unfiltered_count >= 0.9)
        printf("\033[0;32m");
    else
        printf("\033[0;31m");
    printf(" ~= %.2f%%\n", (double)accuracy_unfiltered / unfiltered_count * 100);
    
    printf("\nFiltered Queries Accuracy: %d/%d Passed Test", accuracy_filtered, filtered_count);
    if((double) accuracy_filtered / filtered_count >= 0.9)
        printf("\033[0;32m");
    else
        printf("\033[0;31m");
    printf(" ~= %.2f%%\n", (double)accuracy_filtered / filtered_count * 100);

    // Calculate average time per query
    double avg_time_unfiltered = (unfiltered_count > 0) ? total_time_unfiltered / unfiltered_count : 0.0;
    double avg_time_filtered = (filtered_count > 0) ? total_time_filtered / filtered_count : 0.0;
    
    printf("\nAverage Time per Unfiltered Query: %.6f seconds\n", avg_time_unfiltered);
    printf("Average Time per Filtered Query: %.6f seconds\n", avg_time_filtered);

    if ((double)(accuracy_filtered + accuracy_unfiltered) / Q.number_of_indexes >= 0.9)
        printf("\033[0;32m");
    else
        printf("\033[0;31m");

    printf("%d/%d Total Queries Passed Test", accuracy_filtered + accuracy_unfiltered, Q.number_of_indexes); // Total accuracy needs to be > 0.9*number_of_indexes
    std::cout << " ~= " << (int)((accuracy_filtered + accuracy_unfiltered) / (double)Q.number_of_indexes * 100) << "%\n" << std::endl;
    printf("\033[0m");

    Delete_Query(&Q);
    Delete_Ground_Truth(&GT);
    return 0;
}
