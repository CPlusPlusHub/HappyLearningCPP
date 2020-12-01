#include "neuron.hpp"
#include <random>

double generateRandomNumber(double min, double max){
    double random = (double) rand() / RAND_MAX;
    return min + random * (max - min);
}

Neuron::Neuron(int previousLayerSize){
    initializeWeights(previousLayerSize);
}

void Neuron::initializeWeights(int previousLayerSize){
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0.0, 1.0);
    for(int i = 0; i < previousLayerSize + 1; i++){ // add one is to add bias
        weights.push_back(generateRandomNumber(-1.0,1.0));
    }
}