#include "Library.hpp"
#include <pthread.h>
#define MAX_THREAD 5
// This is the same as the Medoid but we decided to experiment and do it with Multithreading to save some time

typedef struct medoid
{
    double Distance;
    int NodeArrayPos;
} medoid;

typedef struct Data
{
    Graph *G;
    int start;
    int end;
    int Thread_Result_Index;
} Data;

medoid thread_result[MAX_THREAD];

void *Medoid_Find(void *d)
{
    Data *data = (Data *)d;
    double sum;
    int Min_index;

    // Init Min
    double min = std::numeric_limits<double>::max();
    for (int i = data->start; i < data->end; i++)
    {
        sum = 0.0;
        for (int j = 0; j < data->G->number_of_nodes; j++)
        {
            sum += EuclidianDistance(data->G->nodes_array[i].vector, data->G->nodes_array[j].vector, data->G->dimension); // Sum the distances
        }
        // Recalculate Min and save index of Medoid
        if (sum < min)
        {
            min = sum;
            Min_index = i;
        }
    }
    thread_result[data->Thread_Result_Index].Distance = min;           // Save min Distance
    thread_result[data->Thread_Result_Index].NodeArrayPos = Min_index; // Save Position of Vector with min Distance

    pthread_exit(0); // Exit the thread
}

int CallThread(Graph *graph)
{
    // Create and Init Graph
    // Create Data Array and initialize it
    Data D[MAX_THREAD];
    for (int i = 0; i < MAX_THREAD; i++)
    {
        D[i].G = graph;
        D[i].start = i * (graph->number_of_nodes / MAX_THREAD);
        D[i].end = D[i].start + (graph->number_of_nodes / MAX_THREAD);
        D[i].Thread_Result_Index = i;
    }

    pthread_t Thread_Array[MAX_THREAD];
    for (int i = 0; i < MAX_THREAD; i++)
    {
        pthread_create(&Thread_Array[i], NULL, &Medoid_Find, &D[i]);
    }
    for (int i = 0; i < MAX_THREAD; i++)
    {
        pthread_join(Thread_Array[i], NULL);
    }
    double resultMin = thread_result[0].Distance;
    int resultIndexMin = thread_result[0].NodeArrayPos;
    for (int i = 1; i < MAX_THREAD; i++)
    {
        if (thread_result[i].Distance < resultMin)
        {
            resultMin = thread_result[i].Distance;
            resultIndexMin = thread_result[i].NodeArrayPos;
        }
    }
    medoid Result = {.Distance = resultMin, .NodeArrayPos = resultIndexMin};
    return Result.NodeArrayPos;
}