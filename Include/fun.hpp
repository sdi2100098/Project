#ifndef FUN_HPP
#define FUN_HPP

#include "struct.hpp"

/* For read datas of eny cind */
/* return 0:succes,1:fail */
int Init_Graph_Data(Graph *,const char *);
int Init_Query_Data(Query *,const char *,int);
int Init_Ground_Truth_Data(Ground_Truth *,const char *);

/* For free memmory for the structs */
void Delete_Graph(Graph *);
void Delete_Query(Query *);
void Delete_Ground_Truth(Ground_Truth *);

double EuclideanDistance(const float *, const float *, const int);
int Argument_Min_Distance(Graph *, std::set<int> *, float *);
void Set_Difference(std::set<std::pair<double, int>> *, std::set<int> *, std::set<int> *);
std::vector<int> RandomPermutation(Graph *);
int CreateKNNGraphBruteForce(Graph *,Query *, int, const char *, const char *);
int GroundTruth(const char *, const char *, Graph *, int , int , int *);


/*Medoid Function*/
int *FindMedoid(Graph *, float);

/*Robust Function*/
void Filtered_Robust_Prune(int, std::set<int> *, float, Graph *);

/*Greedy Search Function*/
Result_greedy *Filtered_Greedy_Search(Graph *, int, int, int, int *, Query *);

int* Filtered_Vamana(const char *, Graph *, int, int, double);

int* StichedVamanaIndexing(const char *, Graph *, int , int ,int , double );

/*Test Functions*/
void Test_EuclideanDistance();

#endif