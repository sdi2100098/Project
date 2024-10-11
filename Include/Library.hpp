#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cassert>
#include <iomanip>  // Include this header for std::fixed and std::setprecision
#include <cstdlib>  // For malloc and free
#include <cassert>  // For assert

float** fvecs_read(const std::string& ,  int& , int&,std::pair<int, int> );
void free_fvecs(float **,int);
int WriteToTxtFile(float **,std::string& ,int &,int &);