#include "fun.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void saveGraphToBinaryFile(Graph *G, int *Map, char *graph_binary_path)
{
    FILE *file = fopen(graph_binary_path, "wb");
    if (!file)
    {
        perror("Failed to open file for writing");
        return;
    }

    // Write the number of indexes
    fwrite(&G->number_of_indexes, sizeof(int), 1, file);

    // Write the Filters_Size
    fwrite(&G->Filters_Size, sizeof(int), 1, file);

    // Write the contents of the Map array
    fwrite(Map, sizeof(int), G->Filters_Size, file);

    // Write the index_array data
    for (int i = 0; i < G->number_of_indexes; i++)
    {
        const node &currentNode = G->index_array[i];

        // Write the filter for this node
        fwrite(&currentNode.filter, sizeof(int), 1, file);

        // Write the size of the edges set
        int edgeCount = currentNode.edges.size();
        fwrite(&edgeCount, sizeof(int), 1, file);

        // Write each edge in the set
        for (int edge : currentNode.edges)
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

    // Read the number of indexes
    if (fread(&G->number_of_indexes, sizeof(int), 1, file)!=-1){
        perror("Error reading number of indexes in Load Graph Binary File");
        fclose(file);
        return;
    }

    // Read the Filters_Size
    if (fread(&G->Filters_Size, sizeof(int), 1, file)!=-1){
        perror("Error reading Filters_Size in Load Graph Binary File");
        fclose(file);
        return;
    }

    // Allocate memory for the Map array and read its contents
    *Map = new int[G->Filters_Size];
    if (fread(*Map, sizeof(int), G->Filters_Size, file)!=-1){
        perror("Error readin Map in Load Graph Binary File");
        fclose(file);
        return; 
    }

    // Allocate memory for the index_array
    G->index_array = new node[G->number_of_indexes];

    // Read the index_array data
    for (int i = 0; i < G->number_of_indexes; i++)
    {
        node &currentNode = G->index_array[i];

        // Read the filter for this node
        if(fread(&currentNode.filter, sizeof(int), 1, file)!=1){
            perror("Error reading the filter for this node in Load Graph Binary File");
            fclose(file);
            return;
        }

        // Read the size of the edges set
        int edgeCount;
        if (fread(&edgeCount, sizeof(int), 1, file)!=-1){
            perror("Error reading the size of edges for this noode in Load Graph Binary File");
            fclose(file);
            return;
        }

        // Populate the edges set
        currentNode.edges.clear();
        for (int j = 0; j < edgeCount; j++)
        {
            int edge;
            if(fread(&edge, sizeof(int), 1, file)!=1){
                perror("Error reading the edge in Load Graph Binary File");
                fclose(file);
                return;
            }
            currentNode.edges.insert(edge);
        }
    }

    fclose(file);
}
