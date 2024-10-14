#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cassert>
#include <iomanip>  // Include this header for std::fixed and std::setprecision
#include <cstdlib>  // For malloc and free
#include <cassert>  // For assert

float **Read_Data(const char *file_path, int *rows, int *columns);
void free_fvecs(float **,int);
int WriteToTxtFile(float **,std::string& ,int &,int &);

// typedef struct node { //node of each graph 
//     float* vector;
//     int* edges;


// }node;

// node* graph; //explenation of how the graph will look
