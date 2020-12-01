#include "layer.hpp"

Layer::Layer(int previousLayerSize, int currentLayerSize){
    for(int i = 0; i < currentLayerSize; i++){
        this->neurons.push_back(new Neuron(previousLayerSize));
    }
    this->currentLayerSize = currentLayerSize;
}