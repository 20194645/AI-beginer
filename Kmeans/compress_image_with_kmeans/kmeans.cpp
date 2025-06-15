#include "Kmeans.h"


using namespace std;

vector<Pixel> kmeans_init_centroids(vector<Pixel> src, int k) {
    vector<Pixel> centroids;
    if (src.size() < k) {
        cerr << "Not enough points to initialize " << k << " centroids." << endl;
        return centroids;
    }
    set<int> check;
    while (centroids.size() < k) {
        int index = rand() % src.size();
        if (check.find(index) == check.end()) {
            centroids.push_back(src[index]);
            check.insert(index);
        }
    }
    return centroids;
}

vector<vector<int>> labels(const vector<Pixel>& centroids, const vector<Pixel>& src) {
    vector<vector<int>> result(centroids.size());

    for (size_t i = 0; i < src.size(); ++i) {
        int closest_index = -1;
        int min_distance = numeric_limits<int>::max();

        for (size_t j = 0; j < centroids.size(); ++j) {
            int dr = (int)src[i].r - centroids[j].r;
            int dg = (int)src[i].g - centroids[j].g;
            int db = (int)src[i].b - centroids[j].b;
            int distance = dr * dr + dg * dg + db * db;

            if (distance < min_distance) {
                closest_index = j;
                min_distance = distance;
            }
        }
        result[closest_index].push_back(i);
    }

    return result;
}

vector<Pixel> kmeans_update_centroids(const vector<vector<int>>& labels, const vector<Pixel>& src) {
    vector<Pixel> new_centroids(labels.size());
    for (size_t i = 0; i < labels.size(); ++i) {
        if (labels[i].empty()) continue;
        int sumr = 0, sumg = 0, sumb = 0;
        for (int idx : labels[i]) {
            sumr += src[idx].r;
            sumg += src[idx].g;
            sumb += src[idx].b;
        }
        new_centroids[i].r = (uint8_t)(sumr / labels[i].size());
        new_centroids[i].g = (uint8_t)(sumg / labels[i].size());
        new_centroids[i].b = (uint8_t)(sumb / labels[i].size());
    }
    return new_centroids;
}

bool kmeans_converged(const std::vector<Pixel>& old_c, const std::vector<Pixel>& new_c) {
    const int tol_squared = 1;
    for (size_t i = 0; i < old_c.size(); ++i) {
        int dr = old_c[i].r - new_c[i].r;
        int dg = old_c[i].g - new_c[i].g;
        int db = old_c[i].b - new_c[i].b;

        int dist2 = dr * dr + dg * dg + db * db;
        if (dist2 > tol_squared)
            return false;
    }
    return true;
}

void kmeans(const vector<Pixel>& src, int k, vector<Pixel> &centroids, vector<vector<int>> &rgb_labels) {
    centroids = kmeans_init_centroids(src, k);
    if (centroids.empty()) return;

    while (true) {
        rgb_labels = labels(centroids, src);
        vector<Pixel> new_centroids = kmeans_update_centroids(rgb_labels, src);

        if (kmeans_converged(centroids, new_centroids)) {
            cout << "Centroids have converged." << endl;
            break;
        }

        centroids = new_centroids;
    }

    for (const auto& c : centroids) {
        cout << "Final Centroid -> R: " << (int)c.r
             << " G: " << (int)c.g
             << " B: " << (int)c.b << endl;
    }
}
