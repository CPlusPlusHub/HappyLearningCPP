#ifndef __COMMON_HPP
#define __COMMON_HPP
#include "data.hpp"
#include <vector>
class common_data
{
private:
    /* data */
protected:
    std::vector<data *> * training_data;
    std::vector<data *> * test_data;
    std::vector<data *> * validation_data;

public:
    common_data
(/* args */);
    ~common_data
();
    void set_training_data(std::vector<data *> * vect);
    void set_test_data(std::vector<data *> * vect);
    void set_validation_data(std::vector<data *> * vect);
};

common_data::common_data(/* args */)
{

}

common_data::~common_data()
{
    
}

#endif