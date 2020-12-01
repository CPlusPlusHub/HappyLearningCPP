#ifndef __NEURON_HPP
#define __NEURON_HPP
#include <stdio.h>
#include <vector>
#include <cmath>

class Neuron
{
private:
    /* data */
public:
    Neuron(int);
    ~Neuron();
    double output;
    double delta;
    std::vector<double> weights;
    void initializeWeights(int);
};


#endif