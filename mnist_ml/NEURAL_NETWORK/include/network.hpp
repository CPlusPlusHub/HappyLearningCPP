#ifndef __NETWORK_HPP
#define __NETWORK_HPP

#include "data.hpp"
#include "neuron.hpp"
#include "layer.hpp"
#include "common.hpp"

class Network
{
private:
    /* data */
public:
    Network(std::vector<int> spec, int, int, double);
    Network();

    std::vector<Layer *> layers;
    double learningRate;
    double testPerformance;

    std::vector<double> fprop(data *d);
    double activate(std::vector<double>, std::vector<double>);
    double transfer(double);
    double transferDerivative(double);
    void bprop(data *d);
    void updateWeights(data *data);
    int predict(data *);
    void train(int);
    double test();
    void validate();
};

#endif