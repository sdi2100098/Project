#include "Library.hpp"

int GroundTruth(const char *Query_path,const char *Ground_Truth_path,Graph *G,int k , int L , int s){
    int result,sum;
    groundTruth GT = {.array=NULL,.size = 0};
    Query Q = {.vectors_array = NULL, .number_of_vectors = 0 , .dimension = 0};

    result = Init_Query_Data(Query_path,&Q);
    if(result == 1)
        return 1;

    result = Init_Ground_Truth_Data(Ground_Truth_path,&GT);
    if(result == 1)
        return 1;

    result_greedy *Result;
    for(int i = 0; i<Q.number_of_vectors; i++){
        sum = 0;
        Result = Greedy_Search(G,Q.vectors_array[i],k,L,s);
        for(int j = 0; j<GT.size; j++){
            if(Result->L.find(GT.array[i][j])!=Result->L.end())
                sum++;
        }
        std::cout << "Accuracy : " << (double)sum/GT.size << "%%" << std::endl;
    }


    Delete_Query(&Q);
    Delete_GroundTruth(&GT);
    return 0;
}

