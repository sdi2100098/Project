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


double EuclideanDistance(const float *, const float *, const int );
std::vector<int> RandomPermutation(Graph *);
int CreateKNNGraphBruteForce(Graph *,Query *, int, const char *, const char *);


/*Medoid Function*/
int* FindMedoid(Graph *,float);



/*Test Functions*/
void Test_EuclideanDistance();

#endif