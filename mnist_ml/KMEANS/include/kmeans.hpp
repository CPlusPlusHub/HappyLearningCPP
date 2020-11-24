#ifndef __KMEANS_HPP
#define __KMEANS_HPP

#include "common.hpp"
#include <unordered_set>
#include <unordered_map>
#include <limits>
#include <cstdlib>
#include <cmath>
#include <map>
#include "data_handler.hpp"

typedef struct cluster{
    std::vector<double> *centroid;
    std::unordered_set<data *> * cluster_points;
    std::map<uint8_t,int> class_counts;
    int most_frequent_label;

    cluster(data *initial_point){
        centroid = new std::vector<double>;
        cluster_points = new std::unordered_set<data *>;
        for(auto value: *(initial_point->get_feature_vector())){
            centroid->push_back(value);
        }
        cluster_points->insert(initial_point);
        class_counts[initial_point->get_label()] = 1;
        most_frequent_label = initial_point->get_label();
    }

    void add_to_cluster(data* point){
        for(size_t i = 0; i < centroid->size(); i++){
            double tmp = centroid->at(i) * cluster_points->size();
            tmp += point->get_feature_vector()->at(i);
            tmp /= (double)(cluster_points->size() + 1);
            centroid->at(i) = tmp;
        }

        if(class_counts.find(point->get_label()) == class_counts.end()){
            class_counts[point->get_label()] = 1;
        }else{
            class_counts[point->get_label()] += 1;
        }
        cluster_points->insert(point);
        set_most_frequent_class();
    }

    void erase_from_cluster(data* point){
        if(cluster_points->find(point) == cluster_points->end()){
            printf("Error the point doesn\'t exit in this cluster\n");
            return;
        }
        for(size_t i = 0; i < centroid->size(); i++){
            double value = centroid->at(i) * cluster_points->size();
            value -= point->get_feature_vector()->at(i);
            value /= (double)(cluster_points->size() - 1);
            centroid->at(i) = value;
        }
        class_counts[point->get_label()] -= 1;
        cluster_points->erase(point);
        set_most_frequent_class();
    }

    void set_most_frequent_class(){
        int best_class;
        int freq = 0;
        for(auto kv : class_counts){
            if(kv.second > freq){
                freq = kv.second;
                best_class = kv.first;
            }
        }
        most_frequent_label = best_class;
    }
} cluster_t;


class kmeans : public common_data
{
private:
    /* data */
    int num_clusters;
    std::vector<cluster_t *> *cluster_list;
    std::unordered_map<int, int> index_map;
public:
    kmeans(/* args */int);
    kmeans();
    void init_clusters();
    void init_clusters_for_each_class();
    void train(int epoches = 10);
    double euclidean_distance(std::vector<double> *, data *);
    double validation();
    double test();
    int predict(data *);
    ~kmeans();
};


#endif