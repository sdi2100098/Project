#include "Library.hpp"

// Function to Calculate the Difference between Sets
void Set_Difference(std::set<std::pair<double,int>> *L, std::set<int> *V, std::set<int> *Difference_Set)
{
    for (std::set<std::pair<double,int>>::iterator it = L->begin(); it != L->end(); it++)
    {
        if (V->find(it->second) == V->end())
            Difference_Set->insert(it->second);
    }
}
