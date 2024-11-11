#ifndef FUN_HPP
#define FUN_HPP

#include "struct.hpp"

/* For read datas of eny cind */
/* return 0:succes,1:fail */
int Init_Graph_Data(Graph *,const char *);

/* For free memmory for the structs */
void Delete_Graph(Graph *);

#endif