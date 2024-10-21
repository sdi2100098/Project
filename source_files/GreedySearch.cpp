#include "Library.hpp"

result_greedy *Greedy_Search(Graph *s, int xq, int k, int L)
{
    int minvalue;
    std::set<int> V; // Visited nodes
    std::set<int> Lset;
    std::vector<int> temp_vector;
    std::set<int> difference_L_V = {0};

    // Initialize Lset with the starting node
    Lset.insert(0);

    // Continue until Lset is empty
    while (!difference_L_V.empty())
    {
        // Reset temp vector for this iteration
        temp_vector.clear();
        minvalue = Argument_Min_Distance(s, &difference_L_V, xq);

        // Insert the found closest node into the visited set
        V.insert(minvalue);

        for (auto &OutEdge : s->nodes_array[minvalue].edges)
            Lset.insert(OutEdge);

        // If Lset exceeds L, prune it
        if (Lset.size() > L)
        {
            while (1)
            {
                minvalue = Argument_Min_Distance(s, &Lset, xq);
                temp_vector.push_back(minvalue);
                Lset.erase(minvalue);
                if (temp_vector.size() == L)
                    break;
            }

            // Clear Lset and add back only the closest L elements
            Lset.clear();
            for (auto &element : temp_vector)
                Lset.insert(element);
        }

        // Prepare difference_L_V for closest neighbors (Optional)
        difference_L_V.clear();
        Set_Difference(&Lset, &V, &difference_L_V);
    }
    temp_vector.clear();
    while (1)
    {
        minvalue = Argument_Min_Distance(s, &Lset, xq);
        temp_vector.push_back(minvalue);
        Lset.erase(minvalue);
        if (temp_vector.size() == k)
            break;
    }

    // Prepare the result structure to return
    result_greedy *result_g = new result_greedy;

    for (auto &LsetElement : temp_vector)
        result_g->L.insert(LsetElement);
    result_g->V = V;
    return result_g;
}
