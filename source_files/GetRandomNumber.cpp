int GetRandomNumber(const int min,const int max,const int exclude){
    int number;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::unifrom_int_distribution<> distrib(min,max);
    while(number==exclude)
        number = distrib(gen);
    return number;
}