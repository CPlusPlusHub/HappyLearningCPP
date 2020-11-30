#include "data.hpp"

data::data(){
    this->feature_vector = new std::vector<uint8_t>;
}

data::~data(){

}
void data::set_feature_vector(std::vector<uint8_t> *vect){
    this->feature_vector = vect;
}

void data::append_to_feature_vector(uint8_t val){
    this->feature_vector->push_back(val);
}

void data::set_label(uint8_t val){
    this->label = val;
}

void data::set_enumerated_label(int val){
    this->enum_label = val;
}

int data::get_feature_vector_size(){
    return this->feature_vector->size();
}

uint8_t data::get_label(){
    return this->label;
}

uint8_t data::get_enumerate_label(){
    return this->enum_label;
}

std::vector<uint8_t> * data::get_feature_vector(){
    return this->feature_vector;
}

void data::set_distance(double val){
    distance = val;
}

double data::get_distance(){
    return distance;
}

std::vector<double> * data::get_normalized_feature_vector(){
    return this->normalized_feature_vector;
}

void data::set_normalized_feature_vector(std::vector<double> * val){
    this->normalized_feature_vector = val;
}

void data::set_class_vector(int classCount){
    this->class_vector = new std::vector<int>();
    for(int i = 0; i < classCount; i++){
        if(i == label){
            this->class_vector->push_back(1);
        }
        else{
            this->class_vector->push_back(0);
        }
    }
}

std::vector<int>* data::get_class_vector(){
    return this->class_vector;
}


