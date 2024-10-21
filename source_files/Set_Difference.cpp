#include "Library.hpp"

// Function to Calculate the Difference between Sets
void Set_Difference(std::set<int> *L, std::set<int> *V, std::set<int> *Difference_Set)
{
    for (std::set<int>::iterator it = L->begin(); it != L->end(); it++)
    {
        if (V->find(*it) == V->end())
            Difference_Set->insert(*it);
    }
}
