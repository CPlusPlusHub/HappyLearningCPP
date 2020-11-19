#include "data_handler.hpp"

data_handler::data_handler(){
    this->data_array = new std::vector<data *>;
    this->training_data = new std::vector<data *>;
    this->validation_data = new std::vector<data *>;
    this->test_data = new std::vector<data *>;
}

data_handler::~data_handler(){
 
}

void data_handler::read_feature_vector(std::string path){
    uint32_t header[4];
    /*
    32 bit integer
    [0] magic number
    [1] number of images
    [2] number of rows
    [3] number of columns 
    */
   unsigned char bytes[4];
   FILE * f = fopen(path.c_str(),"r");
   if(f){
       for(size_t i = 0; i < 4; i++){
           if(fread(bytes,sizeof(bytes),1,f)){
               header[i] = this->convert_to_little_endian(bytes);
            //    printf("%u\n",header[i]);
           }
       }
   printf("Done getting file header\n");
   // start to get pixel
   int  image_size = header[2] * header[3];
//    printf("%d\n",image_size);
   for(size_t i = 0; i < header[1]; i++){
       data *d = new data();
       uint8_t  element[1];
       for(size_t j = 0; j<image_size; j++){
           if(fread(element, sizeof(element),1,f)){
               d->append_to_feature_vector(element[0]);
           }else{
               printf("Error Reading from File. \n");
               exit(1);
           }
       }
       data_array->push_back(d);
    }
    printf("Successfully read and stored %lu feature vectors.\n", data_array->size());
    }else{
        printf("Could not find file. \n");
        exit(1);
    }
    // printf("flagsdadcxasc\n");
    fclose(f);
}

void data_handler::read_feature_labels(std::string path){
    uint32_t header[2];
    /*
    [0] magic number
    [1] number of items
    */
   unsigned char bytes[4]; // 8 * 4 =32
   FILE * f = fopen(path.c_str(),"r");
   if(f){
       for(size_t i = 0; i < 2; i++){
           if(fread(bytes,sizeof(bytes),1,f)){
               header[i] = this->convert_to_little_endian(bytes);
            //    printf("%u\n",header[i]);
           }
       }
       printf("Done getting label file Header. \n");
       int numberofitem = header[1];
    //    printf("%d\n",numberofitem);
       for(size_t i = 0; i < numberofitem; i++){
           uint8_t element[1];
           if(fread(element, sizeof(element), 1, f)){
               data_array->at(i)->set_label(element[0]);
           }else{
               printf("Error Reading from File. \n");
               exit(1);
           }
       }
    //    printf("flag mmmm\n");
       printf("Successfully read and stored %lu labels\n",data_array->size());
       
       printf("flag"); 
   }else{
       printf("Could not find file.\n");
       exit(1);
   }
   fclose(f);
   printf("flag1");
}

void data_handler::split_data(){
    std::unordered_set<int> used_indexes;
    int train_size = this->data_array->size() * TRAINING_SET_PERCENT;
    int test_size = this->data_array->size() * TEST_SET_PERCENT;
    int validation_size = this->data_array->size() * VALIDATION_SET_PERCENT;

    int count = 0;
    while(count < train_size)
    {
        int rand_index =  rand() % data_array->size();
        if(used_indexes.find(rand_index) == used_indexes.end()){
            training_data->push_back(data_array->at(rand_index));
            used_indexes.insert(rand_index);
            count++;
        }
    }

    count = 0;
    while(count < test_size){
        int rand_index = rand() % data_array->size();
        if(used_indexes.find(rand_index) == used_indexes.end()){
            test_data->push_back(data_array->at(rand_index));
            used_indexes.insert(rand_index);
            count++;
        }
    }

    count = 0;
    while(count < test_size){
        int rand_index = rand() % data_array->size();
        if(used_indexes.find(rand_index) == used_indexes.end()){
            validation_data->push_back(data_array->at(rand_index));
            used_indexes.insert(rand_index);
            count++;
        }
    }

    printf("Training Data Size : %lu.\n", this->training_data->size());
    printf("Test Data Size : %lu.\n", this->test_data->size());
    printf("validation Data Size : %lu.\n", this->validation_data->size());
}

void data_handler::count_classes(){
    int count = 0;
    for( size_t i=0; i< data_array->size(); i++){
        if(class_map.find(data_array->at(i)->get_label()) == class_map.end()){
            class_map[data_array->at(i)->get_label()] = count;
            data_array->at(i)->set_enumerated_label(count);
            count++;
        }
    }
    num_classes = count;
    printf("Successfully Extraced %lu Unique class", class_map.size());

}

std::vector<data *> * data_handler::get_training_data(){
    return this->training_data;
}

std::vector<data *> * data_handler::get_test_data(){
    return this->test_data;
}

std::vector<data *> * data_handler::get_validation_data(){
    return this->validation_data;
}

uint32_t data_handler::convert_to_little_endian(const unsigned char * bytes){
    return (uint32_t)(
        (bytes[0] << 24) |
        (bytes[1] << 16) |
        (bytes[2] << 8 ) | 
         bytes[3]
    );
}

int main(){
    data_handler *dh =  new data_handler();
    dh->read_feature_vector("../mnist_data/t10k-images-idx3-ubyte");
    dh->read_feature_labels("../mnist_data/t10k-labels-idx1-ubyte");
    printf("flag\n");
    exit(1);
    dh->split_data();
    dh->count_classes();
}