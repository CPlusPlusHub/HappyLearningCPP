#include<kmeans.hpp>

kmeans::kmeans(int val){
    num_clusters = val;
    cluster_list = new std::vector<cluster_t *>;
}

kmeans::~kmeans(){

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
            cluster_list->push_back(new cluster(training_data->at(i)));
        }
    }
    printf("Initialize clusters for each class");
}

void kmeans::train(int epoches = 10){
    for(size_t epoch = 0; epoch < epoches; epoch++){
        for(auto point : *training_data){
            int best_cluster_index = 0;
            double min_distance = std::numeric_limits<double>::max();
            for(size_t i = 0; i < cluster_list->size(); i++){
                double distance = euclidean_distance(cluster_list->at(i)->centroid, point);
                if(distance < min_distance){
                    best_cluster_index = i;
                    min_distance = distance
                }
            }
        }
    }
}

double kmeans::euclidean_distance(std::vector<double>* centroid, data * point){
    double distance = 0.0;
    for(size_t i = 0; i < centroid->size(); i++){
        distance += pow(centroid->at(i) - point->get_feature_vector()->at(i),2);
    }
    return sqrt(distance);
}

double kmeans::validation(){

}

double kmeans::test(){

}
