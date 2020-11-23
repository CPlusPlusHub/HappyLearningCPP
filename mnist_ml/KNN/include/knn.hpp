#ifndef __KNN_HPP
#define __KNN_HPP
#include "common.hpp"



class knn:public common_data
{
private:
    /* data */
    int k;
    std::vector <data *> *neighbors;

public:
    knn(/* args */int);
    knn();
    ~knn();

    void find_knearest(data *query_point);
    void set_k(int val);
    int predict();
    double calculate_distance(data *query_point, data *input);
    double validation_performance();
    double test_performance();

};
#endif