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

Network::~Network(){

}

Network::Network(){

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

void Network::bprop(data *d){
    for(int i = layers.size() - 1; i >= 0; i--){
        Layer *layer = layers.at(i);
        std::vector<double> errors; // 
        if(i != layers.size() - 1){
            for(int j = 0; j< layer->neurons.size(); j++){
                double error = 0.0;
                for(Neuron *n : layers.at(i + 1)->neurons){
                    error += n->delta * n->weights.at(j) ;
                }
                errors.push_back(error);
            }
        }else{ //i== layers.size() - 1
            for(int j = 0; j < layer->neurons.size(); j++){
                Neuron * n = layer->neurons.at(j);
                errors.push_back((double)d->get_class_vector()->at(j) - n->output);
            }
        }

        for(int j = 0 ; j < layer->neurons.size(); j++){
            layer->neurons.at(j)->delta = errors.at(j) * this->transferDerivative(layer->neurons.at(j)->output);
            //update neurons delta
        }
    }
}

void Network::updateWeights(data *d){
    std::vector<double> inputs = *d->get_normalized_feature_vector();
    for(int i = 0; i < layers.size(); i++){
        Layer *layer = layers.at(i);
        std::vector<double> newInputs;
        for(int j = 0; j < layer->neurons.size(); j++){
            Neuron *n = layer->neurons.at(j);
            for(int x; x < n->weights.size() - 1; x++){
                n->weights.at(x) += this->learningRate * n->delta * inputs.at(x);
            }
            n->weights.back() += this->learningRate * n->delta;
            newInputs.push_back(n->output);
        }
        inputs = newInputs;
    }
}

int Network::predict(data * d){
    std::vector<double> ans = this->fprop(d);
    return std::distance(ans.begin(),std::max_element(ans.begin(), ans.end()));
}

void Network::train(int epoches){
    for(int epoch = 0 ; epoch < epoches; epoch++){
        double sumLoss = 0.0;
        for(data* d: *training_data){
            std::vector<double> output = this->fprop(d);
            std::vector<int> expected = *d->get_class_vector();
            double loss = 0.0;
            for(int i = 0; i < output.size(); i++){
                loss += 0.5 * pow(output.at(i) - (double)expected.at(i), 2);
            }
            sumLoss += loss;
            this->bprop(d);
            this->updateWeights(d);
        }
        printf("Iteration: %d \t Error=%.4f\n", epoch, sumLoss);
    }

}

double Network::test(){
    double numCorrect = 0.0;
    double count = 0.0;
    for(data *d : *this->test_data)
    {
        count++;
        int index = predict(d);
        if(d->get_class_vector()->at(index) == 1) numCorrect++;
    }

    testPerformance = (numCorrect / count);
    return testPerformance;
}

void Network::validate(){
    double numCorrect = 0.0;
    double count = 0.0;
    for(data *d : *this->validation_data)
    {
        count++;
        int index = predict(d);
        if(d->get_class_vector()->at(index) == 1) numCorrect++;
    }

    double validationPerformance = (numCorrect / count);
    printf("Validation Performance: %.4f\n", validationPerformance);
}

int main(){
    data_handler *dh = new data_handler();
    dh->read_feature_vector("../../mnist_data/t10k-images-idx3-ubyte");
    dh->read_feature_labels("../../mnist_data/t10k-labels-idx1-ubyte");
    dh->count_classes(); 
    dh->split_data();
    std::vector<int> spec = {128,32};
    int inputSize = dh->get_feature_vector_size();
    int numClasses = dh->get_num_classes();
    double learningRate = 0.0001;
    printf("numClasses: %d inputSize:%d \n",numClasses,inputSize);
    Network * network = new Network(spec, inputSize, numClasses, learningRate);
    network->set_training_data(dh->get_training_data());
    network->set_validation_data(dh->get_validation_data());
    network->set_test_data(dh->get_test_data());
    network->train(100);
    network->validate();
    printf("Test Performance: %.3f\n", network->test());
    return 0;
}