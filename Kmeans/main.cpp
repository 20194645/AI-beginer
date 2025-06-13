#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <limits>
using namespace std;

struct Point{
    float x,y;
};

vector<Point> Points;

void readPointsFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }
    Point p;
    int label;
    while (file >> p.x >> p.y >> label) {
        Points.push_back(p);
    }
    file.close();
}

vector<Point> kmeans_init_centroids(int k){
    vector<Point> centroids;
    if (Points.size() < k) {
        cerr << "Not enough points to initialize " << k << " centroids." << endl;
        return centroids;
    }
    set<int> check;
    while (centroids.size() < k) {
        int index = rand() % Points.size();
        if (check.find(index) == check.end()) {
            centroids.push_back(Points[index]);
            check.insert(index);
        }
    }
    return centroids;
}

vector<vector<int>> labels(vector<Point>centroids , vector<Point> points){
    vector<vector<int>> result(centroids.size());
    for (size_t j = 0; j < points.size(); ++j) {
        Point point = points[j];
        int closest_index = -1;
        float min_distance = numeric_limits<float>::max();
        for (int i = 0; i < centroids.size(); ++i) {
            float distance = (point.x - centroids[i].x) * (point.x - centroids[i].x) +
                             (point.y - centroids[i].y) * (point.y - centroids[i].y);
            if (distance < min_distance) {
                min_distance = distance;
                closest_index = i;
            }
        }
        result[closest_index].push_back(j);
    }
    return result;
}

vector<Point> kmeans_update_centroids(const vector<vector<int>>& labels, const vector<Point>& points) {
    vector<Point> new_centroids(labels.size());
    for (int i = 0; i < labels.size(); ++i) {
        if (labels[i].empty()) continue;
        float sum_x = 0, sum_y = 0;
        for (int idx : labels[i]) {
            sum_x += points[idx].x;
            sum_y += points[idx].y;
        }
        new_centroids[i].x = sum_x / labels[i].size();
        new_centroids[i].y = sum_y / labels[i].size();
    }
    return new_centroids;
}

bool kmeans_converged(vector<Point>& old_c, vector<Point>& new_c, float tol = 1e-4) {
    for (int i = 0; i < old_c.size(); ++i) {
        float dx = old_c[i].x - new_c[i].x;
        float dy = old_c[i].y - new_c[i].y;
        if ((dx * dx + dy * dy) > tol * tol)
            return false;
    }
    return true;
}


void kmeans(){
    int k = 3;
    vector<Point> centroids = kmeans_init_centroids(k);
    for (size_t i = 0; i < centroids.size(); i++)
    {
        cout<< "Initial Centroid " << i << ": (" << centroids[i].x << ", " << centroids[i].y << ")" << endl;
    }
    
    while (1)
    {
        vector<vector<int>> point_labels = labels(centroids, Points);
        vector<Point> new_centroids = kmeans_update_centroids(point_labels, Points);
        if (kmeans_converged(centroids, new_centroids)) {
            cout << "Centroids have converged." << endl;
            break;
        }
        centroids = new_centroids;
    }
    for (const auto& centroid : centroids) {
        cout << "Centroid: (" << centroid.x << ", " << centroid.y << ")"<< endl;
    }
}


int main(){
    readPointsFromFile("data_with_labels.txt");
    kmeans();
}