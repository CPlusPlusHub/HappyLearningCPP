#include "knn.hpp"
#include <cmath>
#include <limits>
#include "cstdlib"
#include "stdint.h"
#include <map>
#include <algorithm>
#include <data_handler.hpp>

knn::knn(/* args */int val){
    k = val;
}

knn::knn(){
    
}

knn::~knn(){
    free(neighbors);
}

void knn::find_knearest(data *query_point){
    neighbors = new std::vector<data *>;
    double min = std::numeric_limits<double>::max();
    double previous_min = -1;
    int index = 0;
    for(size_t n = 0; n < k; n++){
        index = 0;
        min = std::numeric_limits<double>::max();
        for(size_t i = 0; i < training_data->size(); i++){
            double distance = calculate_distance(query_point,training_data->at(i));
            if(distance < min and distance > previous_min){
                index = i;
                min = distance;
            }
        }
        training_data->at(index)->set_distance(min);
        neighbors->push_back(training_data->at(index));
        previous_min = min;
    }
}

void knn::set_k(int val){
    k = val;
}

int knn::predict(){
    std::map<uint8_t,double> count;
    for(auto d: *neighbors){
        if(count.find(d->get_label()) == count.end()){
            count[d->get_label()] = 1 / d->get_distance();
        }else{
            count[d->get_label()] += 1 / d->get_distance();
        }
    }
    int best_label = 0;
    double best_score = 0;
    for(auto kv:count){
        if(kv.second > best_score){
            best_label = kv.first;
            best_score = kv.second;
        }
    }
    delete neighbors;
    return best_label;
}

double knn::calculate_distance(data *query_point, data *input){
    int size = query_point->get_feature_vector_size();
    int size_ = input->get_feature_vector_size();
    if(size != size_){
        printf("the size of two data container is not equal. Can not cal distance\n");
        exit(1);
    }
    double distance = 0.0;

#ifdef EUCLID
    for(size_t i = 0; i < size; i++){
        distance += pow(input->get_feature_vector()->at(i)-query_point->get_feature_vector()->at(i),2);
    }
    return sqrt(distance);
#elif define MANHATTAN
/* Calculate MANHATTAN distance*/
    for (size_t i = 0; i < size; i++){
        distance += abs(input->get_feature_vector()->at(i)-query_point->get_feature_vector()->at(i));
    }
    return distance;
#endif
}

double knn::validation_performance(){
    printf("Validation Performance K Nearest k is %d",k);
    double current_performance = 0;
    int count = 0;
    int index = 0;
    for(data * query_point : *validation_data){
        find_knearest(query_point);
        int prediction = predict();
        if(prediction == query_point->get_label()){
            count ++;
        }
        index ++;
        current_performance = (double) count * 100.0 / (double) index;
        printf("%d:%d | Current Performance Accuracy : %.3f %%\n", index, validation_data->size(), current_performance);
    }
    // int index = validation_data->size()
    current_performance = (double) count * 100.0 / validation_data->size();
    printf("Validation Performance Accuracy : %.3f %%\n",current_performance);
    return current_performance;
}
double knn::test_performance(){
    printf("Test Performance K Nearest k is %d",k);
    double current_performance = 0;
    int count = 0;
    int index = 0;
    for( auto query_point : *test_data){
        find_knearest(query_point);
        int prediction = predict();
        if(prediction == query_point->get_label()){
            count++;
        }
        index ++;
        current_performance = (double) count * 100.0 / (double) index;
        printf("%d:%d | Current Performance Accuracy : %.3f %%\n",index, test_data->size(), current_performance);
    }
    current_performance = (double) count * 100.0 / test_data->size();
    printf("Test Performance Accuracy : %.3f %%\n", current_performance);
    return current_performance;
}

int main(){
    data_handler *dh = new data_handler();
    dh->read_feature_vector("../mnist_data/t10k-images-idx3-ubyte");
    dh->read_feature_labels("../mnist_data/t10k-labels-idx1-ubyte");
    dh->split_data();
    dh->count_classes(); 
    knn * knearest = new knn();

    knearest->set_training_data(dh->get_training_data());
    knearest->set_validation_data(dh->get_validation_data());
    knearest->set_test_data(dh->get_test_data());
    double performance = 0.0;
    double best_performance = 0.0;
    int best_k = 0;
    for(size_t i = 1; i <= 4; i++){
        knearest->set_k(i);
        performance = knearest->validation_performance();
        if(performance > best_performance){
            best_performance = performance;
            best_k = i;
        }
    }
    knearest->set_k(best_k);
    knearest->test_performance();
}