#ifndef FUN_HPP
#define FUN_HPP

#include "struct.hpp"
#include <stdbool.h>

/* For read datas of eny cind */
/* return 0:succes,1:fail */
int Init_Graph_Data(Graph *, const char *, bool);
int Init_Query_Data(Query *, const char *, int, bool);
int Init_Ground_Truth_Data(Ground_Truth *, const char *);

/* Read The .bin Data for the Above Fucntions */
/* return 0:succes,1:fail */
int Init_Precompute_Dinstance(Graph *, Query *);

/* For free memmory for the structs */
void Delete_Graph(Graph *);
void Delete_Query(Query *);
void Delete_Ground_Truth(Ground_Truth *);

double EuclideanDistance(const float *, const float *, const int);
int Argument_Min_Distance(Graph *, Query *, std::set<int> *, int);
void Set_Difference(std::set<std::pair<float, int>> *, std::set<int> *, std::set<int> *);
std::vector<int> RandomPermutation(Graph *);
int GroundTruth(const char *, const char *, Graph *, int, int, int *);

/* For PreComputeFun.cpp */
int CreateKNNGraphBruteForce(Graph *, Query *, int, const char *);
int Graph_Graph_Dinstance_Precompute(Graph *);
int Graph_Query_Dinstance_Precompute(Graph *, Query *);

/*Medoid Function*/
int *FindMedoid(Graph *, int);

/*Robust Function*/
void Filtered_Robust_Prune(int, std::set<int> *, float, Graph *);

/*Greedy Search Function*/
Result_greedy *Filtered_Greedy_Search(Graph *, int, int, int, int *, Query *);

int *Filtered_Vamana(const char *, Graph *, int, int, double);

/*Test Functions*/
void Test_EuclideanDistance();

#endif