#include <stdio.h>
#include <set>
#include <vector>
#include <iterator>
#include "fun.hpp"

int CreateKNNGraphBruteForce(Graph *G, Query *Q, int K, const char *binary_filename)
{

    // Open the binary output file
    FILE *binary_file = fopen(binary_filename, "wb");
    if (binary_file == NULL)
    {
        perror("Error in CreateKNNGraphBruteForce (fopen)");
        return 1;
    }

    int x, temp_K, sum;
    int *Querys_with_Filter = (int *)malloc(sizeof(int) * Q->Filters_Size);
    int *Querys_Actual_KNN = (int *)malloc(sizeof(int) * Q->Filters_Size);

    /* save the meta data */
    fwrite(&Q->Filters_Size, sizeof(int), 1, binary_file);

    /* For every filter save the number of Vectors in Query */
    sum = 0;
    for (int i = 0; i < Q->Filters_Size; i++)
    {
        x = (int)Q->Filters[i].size();
        sum += x;
        Querys_with_Filter[i] = (int)Q->Filters[i].size();
    }
    fwrite(&sum, sizeof(int), 1, binary_file);

    fwrite(Querys_with_Filter, sizeof(int), Q->Filters_Size, binary_file);

    /* For every filter save the number of actuale K closest neig */
    for (int i = 0; i < Q->Filters_Size - 1; i++)
    {

        if (Querys_with_Filter[i] == 0)
        {
            Querys_Actual_KNN[i] = 0;
            continue;
        }

        x = (int)G->Filters[i].size();
        Querys_Actual_KNN[i] = (x > K) ? K : x;
    }
    Querys_Actual_KNN[Q->Filters_Size - 1] = (K > G->number_of_indexes) ? G->number_of_indexes : K; /* The last is the no filter so i must compare with all the athers in base 10.000 */

    /* For every filter save the actuale number of K nearesrt Neighbor */
    fwrite(Querys_Actual_KNN, sizeof(int), Q->Filters_Size, binary_file);

    std::set<std::pair<float, int>> closest_neighbors = {{}};
    std::vector<int> closest_index = {};
    float distance;

    for (int i = 0; i < Q->Filters_Size; i++)
    { /* For every filter in Query */

        if (i == Q->NO_FILTERS_POTITION)
            break;

        for (int j = 0; j < (int)Q->Filters[i].size(); j++)
        { /* For every Vector that has this filter in Query */

            closest_neighbors.clear();

            for (int k = 0; k < (int)G->Filters[i].size(); k++)
            { /* For every Vector that has the same filter in Graph */
                distance = EuclideanDistance(Q->index_array[Q->Filters[i][j]].vector, G->index_array[G->Filters[i][k]].vector, Q->dimension);
                closest_neighbors.insert({distance, G->Filters[i][k]});
            }

            /* Take only the first K indexes from (closest_neighbors) */
            closest_index.clear();

            temp_K = 0;
            for (std::set<std::pair<float, int>>::iterator it = closest_neighbors.begin(); it != closest_neighbors.end() && temp_K < K; it++, temp_K++)
            {
                closest_index.push_back(it->second);
            }

            /* Write the data */
            fwrite(&Q->Filters[i][j], sizeof(int), 1, binary_file);
            for (int k = 0; k < (int)closest_index.size(); k++)
            {
                fwrite(&closest_index[k], sizeof(int), 1, binary_file);
            }
        }
    }

    /* Here i loop for the No filters Vector in Querys and every ather Vector in Grapgh */
    for (int i = 0; i < (int)Q->Filters[Q->NO_FILTERS_POTITION].size(); i++)
    { /* Every Vector with no Filter in Query */

        closest_neighbors.clear();
        closest_index.clear();

        for (int j = 0; j < G->number_of_indexes; j++)
        { /* Every Vector in Grapgh */
            distance = EuclideanDistance(Q->index_array[Q->Filters[Q->NO_FILTERS_POTITION][i]].vector, G->index_array[j].vector, Q->dimension);
            closest_neighbors.insert({distance, j});
        }

        temp_K = 0;
        for (std::set<std::pair<float, int>>::iterator it = closest_neighbors.begin(); it != closest_neighbors.end() && temp_K < K; it++, temp_K++)
        {
            closest_index.push_back(it->second);
        }

        fwrite(&Q->Filters[Q->NO_FILTERS_POTITION][i], sizeof(int), 1, binary_file);
        for (int k = 0; k < (int)closest_index.size(); k++)
        {
            fwrite(&closest_index[k], sizeof(int), 1, binary_file);
        }
    }

    free(Querys_with_Filter);
    free(Querys_Actual_KNN);

    // Close the files
    fclose(binary_file);
    return 0;
}

