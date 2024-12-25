#include "fun.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

void saveGraphToBinaryFile(Graph *G, int *Map, const char *graph_binary_path)
{
    FILE *file = fopen(graph_binary_path, "wb");
    if (!file)
    {
        perror("Failed to open file for writing");
        return;
    }

    // Write the number of indexes
    fwrite(&(G->number_of_indexes), sizeof(int), 1, file);

    // Write the Filters_Size
    fwrite(&(G->Filters_Size), sizeof(int), 1, file);

    // Write the dimension
    fwrite(&(G->dimension), sizeof(int), 1, file);

    fwrite(&(G->R), sizeof(int), 1, file);

    // Write the contents of the Map array
    fwrite(Map, sizeof(int), G->Filters_Size, file);

    // Write the index_array data
    for (int i = 0; i < G->number_of_indexes; i++)
    {
        // Write the filter for this node
        fwrite(&(G->index_array[i].filter), sizeof(int), 1, file);

        // Write the vector data (fixed size G->dimension)
        fwrite(G->index_array[i].vector, sizeof(float), G->dimension, file);

        // Write the size of the edges set
        int edgeCount = G->index_array[i].edges.size();
        fwrite(&edgeCount, sizeof(int), 1, file);

        // Write each edge in the set
        for (int edge : G->index_array[i].edges)
        {
            fwrite(&edge, sizeof(int), 1, file);
        }
    }

    fclose(file);
}

void loadGraphFromBinaryFile(Graph *G, int **Map, const char *graph_binary_path)
{
    FILE *file = fopen(graph_binary_path, "rb");
    if (!file)
    {
        perror("Failed to open file for reading");
        return;
    }

    if (fread(&(G->number_of_indexes), sizeof(int), 1, file) != 1)
    {
        perror("Error reading number_of_indexes");
        fclose(file);
        return;
    }

    if (fread(&(G->Filters_Size), sizeof(int), 1, file) != 1)
    {
        perror("Error reading Filters_Size");
        fclose(file);
        return;
    }

    if (fread(&(G->dimension), sizeof(int), 1, file) != 1)
    {
        perror("Error reading dimension");
        fclose(file);
        return;
    }

    if (fread(&(G->R), sizeof(int), 1, file) != 1)
    {
        perror("Error reading R");
        fclose(file);
        return;
    }

    *Map = (int *)malloc(G->Filters_Size * sizeof(int));
    if (fread(*Map, sizeof(int), G->Filters_Size, file) != (size_t)G->Filters_Size)
    {
        perror("Error reading Map");
        fclose(file);
        return;
    }

    G->index_array = new node[G->number_of_indexes]();
    for (int i = 0; i < G->number_of_indexes; i++)
    {
        if (fread(&(G->index_array[i].filter), sizeof(int), 1, file) != 1)
        {
            perror("Error reading filter");
            fclose(file);
            return;
        }

        // Allocate memory and read the vector data (fixed size G->dimension)
        G->index_array[i].vector = (float *)malloc(G->dimension * sizeof(float));
        if (fread(G->index_array[i].vector, sizeof(float), G->dimension, file) != (size_t)G->dimension)
        {
            perror("Error reading vector data");
            fclose(file);
            return;
        }

        int edgeCount;
        if (fread(&edgeCount, sizeof(int), 1, file) != 1)
        {
            perror("Error reading edgeCount");
            fclose(file);
            return;
        }

        for (int j = 0; j < edgeCount; j++)
        {
            int edge;
            if (fread(&edge, sizeof(int), 1, file) != 1)
            {
                perror("Error reading edge");
                fclose(file);
                return;
            }
            G->index_array[i].edges.insert(edge);
        }
    }

    fclose(file);
}
