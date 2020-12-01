#include "network.hpp"
#include "layer.hpp"
#include "data_handler.hpp"
#include <numeric>

Network::Network(std::vector<int> spec, int inputSize, int numClasses, double learningRate){
    for(int i = 0; i < spec.size(); i++){
        if(i == 0){
            layers.push_back(new Layer(inputSize, spec.at(0)));
        }
        else{
            layers.push_back(new Layer(spec.at(i-1), spec.at(i)));
        }
    }
    layers.push_back(new Layer(spec.at(spec.size() - 1), numClasses));
    this->learningRate = learningRate;
}

Network:: ~Network(){

}

double Network::activate(std::vector<double> weights, std::vector<double> inputs){
    double activation = weights.back();
    for(int i = 0; i < weights.size() - 1; i++){
        activation += weights[i] * inputs[i];
    }
    return activation;
}

double Network::transfer(double activation){
     return 1.0 / (1.0 + exp(-activation));
}

double Network::transferDerivative(double output){
    return output * (1 - output);
}

std::vector<double> Network::fprop(data *d){
    std::vector<double> inputs = *(d->get_normalized_feature_vector());
    for(int i = 0; i < layers.size(); i++){
        Layer *layer = layers.at(i);
        std::vector<double> newInputs;
        for(Neuron *n: layer->neurons){
            double activation = this->activate(n->weights, inputs);
            n->output = this->transfer(activation);
            newInputs.push_back(n->output);
        }
        inputs = newInputs;
    }
    return inputs;
}