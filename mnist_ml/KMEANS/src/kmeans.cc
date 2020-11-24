#include<kmeans.hpp>

kmeans::kmeans(int val){
    num_clusters = val;
    cluster_list = new std::vector<cluster_t *>;
}
kmeans::kmeans(){
    cluster_list = new std::vector<cluster_t *>;
}

kmeans::~kmeans(){
    free(cluster_list);
}

void kmeans::init_clusters(){
    std::unordered_set<int> used_index;
    for(size_t i = 0; i < num_clusters; i++){
        int index = rand() % training_data->size();
        while(used_index.find(index) == used_index.end()){
            index = rand() % training_data->size();
        }
        used_index.insert(index);
        cluster_t *c = new cluster(training_data->at(index));
        index_map.insert(std::pair<int,int>(index,cluster_list->size()));
        cluster_list->push_back(c);
    }
    printf("Initialize clusters");
}

void kmeans::init_clusters_for_each_class(){
    std::unordered_set<int> used_class;
    for(size_t i = 0; i < training_data->size(); i++){
        int label = training_data->at(i)->get_label();
        if(used_class.find(label) == used_class.end()){
            used_class.insert(label);
            index_map.insert(std::pair<int,int>(i,cluster_list->size()));
            cluster_list->push_back(new cluster(training_data->at(i)));
        }
    }
    printf("Initialize clusters for each class");
}

void kmeans::train(int epoches){
    for(size_t epoch = 0; epoch < epoches; epoch++){
        for(size_t index = 0; index < training_data->size(); index++){
            int best_cluster_index = 0;
            double min_distance = std::numeric_limits<double>::max();
            
            for(size_t i = 0; i < cluster_list->size(); i++){
                double distance = euclidean_distance(cluster_list->at(i)->centroid, training_data->at(index));
                if(distance < min_distance){
                    best_cluster_index = i;
                    min_distance = distance;
                }
            }

            if(index_map.find(index) == index_map.end()){
                index_map[index] = best_cluster_index;
            }
            else if(index_map[index] != best_cluster_index){
                cluster_list->at(index_map[index])->erase_from_cluster(training_data->at(index));
                cluster_list->at(best_cluster_index)->erase_from_cluster(training_data->at(index));
            }
            
        }
    }
}
/* 
    calculate the euclidean distance between centroid and query_point

 */
double kmeans::euclidean_distance(std::vector<double>* centroid, data * point){
    double distance = 0.0;
    for(size_t i = 0; i < centroid->size(); i++){
        distance += pow(centroid->at(i) - point->get_feature_vector()->at(i),2);
    }
    return sqrt(distance);
}

int kmeans::predict(data* query_point){
    int best_cluster = 0;
    double  min_distance = std::numeric_limits<double>::max();   
    for(size_t i = 0; i < num_clusters; i++){
       double distance = euclidean_distance(cluster_list->at(i)->centroid,query_point);
       if(distance < min_distance){
           best_cluster = i;
           min_distance = distance;
       }
    }
    return cluster_list->at(best_cluster)->most_frequent_label;
}

double kmeans::validation(){
    double current_performance = 0.0;
    int count = 0;
    int index = 0;
    for(auto query_point : *validation_data){
        int pred_label = predict(query_point);
        if(pred_label == query_point->get_label()){
            count++;
        }
        index++;
        current_performance = (double)count/(double)index * 100;
        printf("Validation:%d:%lu Current Performance:%.3f%%\n|",index,validation_data->size(),current_performance);
    }
    printf("Validation Final Performance Accuracy %.3f%%",current_performance);
    return current_performance;
}

double kmeans::test(){
    double current_performance = 0.0;
    int count = 0;
    int index = 0;
    for(auto query_point : *test_data){
        int pred_label = predict(query_point);
        if(pred_label == query_point->get_label()){
            count++;
        }
        index++;
        current_performance = (double)count/(double)index * 100;
        printf("Test:%d:%lu Current Performance:%.3f%%\n|",index,test_data->size(),current_performance);
    }
    printf("Test Final Performance Accuracy %.3f%%",current_performance);
    return current_performance;
}

int main(){
    data_handler *dh = new data_handler();
    dh->read_feature_vector("../mnist_data/t10k-images-idx3-ubyte");
    dh->read_feature_labels("../mnist_data/t10k-labels-idx1-ubyte");
    dh->split_data();
    dh->count_classes(); 
    kmeans * model = new kmeans(10);
    model->set_test_data(dh->get_test_data());
    model->set_training_data(dh->get_training_data());
    model->set_validation_data(dh->get_validation_data());

    model->init_clusters_for_each_class();
    model->train();
    model->validation();
    model->test();

}