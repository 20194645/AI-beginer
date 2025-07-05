#include "naive_bayes.h"
#include <cmath>
using namespace std;

void display_train_data() {
    for (int i = N; i <= S; i++) {
        std::cout << "Class " << i << ":\n";
        for (size_t j = 1; j < train_data[i].size(); j++)
        {
            std::cout << "Word " << j << ": " << train_data[i][j] << "\n";
        }
        
    }
}

vector<int> predict() {
    vector<int> predictions;
    predictions.resize(test_labels.size()+1, 0);
    
    for (size_t i = 1; i <= test_labels.size(); i++)
    {
        float S_prob = 0.0f + log(P_S);
        float N_prob = 0.0f + log(P_N);
        for (size_t j = 1; j <= 2500; j++)
        {
            if (test_data[i][j] > 0) 
            {
                S_prob += log(train_data[S][j]) * test_data[i][j];
                N_prob += log(train_data[N][j]) * test_data[i][j];
            }
            
        }
        //cout<<"S_prob: " << S_prob << ", N_prob: " << N_prob << endl;
        if (S_prob > N_prob) {
            predictions[i] = S;
        } else {
            predictions[i] = N;
        }
    }
    return predictions;
}

void compare(vector<int> predictions) {
    int correct = 0;
    for (size_t i = 1; i < predictions.size(); i++) {
        if (predictions[i] == test_labels[i]) {
            correct++;
        }
    }
    float accuracy = static_cast<float>(correct) / (test_labels.size()) * 100.0f;
    std::cout << "Accuracy: " << accuracy << "%\n";
    
}