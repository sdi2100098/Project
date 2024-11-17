#ifndef FUN_HPP
#define FUN_HPP

#include "struct.hpp"

/* For read datas of eny cind */
/* return 0:succes,1:fail */
int Init_Graph_Data(Graph *, const char *);
int Init_Query_Data(Query *, const char *, int);

/* For free memmory for the structs */
void Delete_Graph(Graph *);
void Delete_Query(Query *);

double EuclideanDistance(const float *, const float *, const int);
int Argument_Min_Distance(Graph *, std::set<int> *, int);
std::vector<int> RandomPermutation(Graph *);
void CreateKNNGraphBruteForce(Graph, int, const char *, const char *);

/*Medoid Function*/
int *FindMedoid(Graph *, float);

/*Robust Function*/
void Filtered_Robust_Prune(int, std::set<int> *, float, Graph *);

int Filtered_Vamana(const char *, Graph *, int, int, double);

/*Test Functions*/
void Test_EuclideanDistance();

#endif