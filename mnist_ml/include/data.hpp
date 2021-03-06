#ifndef __DATA_H
#define __DATA_H

#include <vector>
#include "stdint.h"
#include "stdio.h"

class data{
    std::vector<uint8_t> * feature_vector;
    std::vector<double> * normalized_feature_vector;
    std::vector<int> * class_vector;
    uint8_t label;
    int enum_label; 
    double distance;
    public:
    data();
    ~data();

    void set_normalized_feature_vector(std::vector<double> *);
    void set_feature_vector(std::vector<uint8_t> *);
    void set_class_vector(int);

    void append_to_feature_vector(uint8_t);
    void set_label(uint8_t);
    void set_enumerated_label(int);
    void set_distance(double);
    double get_distance();
    int get_feature_vector_size();
    uint8_t get_label();
    uint8_t get_enumerate_label();

    std::vector<double> * get_normalized_feature_vector();
    std::vector<uint8_t> * get_feature_vector();
    std::vector<int> * get_class_vector();
};
#endif