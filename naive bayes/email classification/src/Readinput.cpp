#include "Readinput.h"
using namespace std;

std::string train_data_fn = "data/train-features.txt";
std::string test_data_fn = "data/test-features.txt";
std::string train_label_fn = "data/train-labels.txt";
std::string test_label_fn = "data/test-labels.txt";
float P_S = 0.0f, P_N = 0.0f; // Probabilities of classes S and N
std::vector<int> labels; // 1 to cover indices 0, 1
std::vector<int> test_labels;
std::vector<std::vector<float>> train_data(2); // 2 to cover indices 0, 1
std::vector<std::vector<int>> test_data; // 2 to cover indices 0, 1


void make_labels_vector(string filename,vector<int>& labels) {
    fstream file(filename);
    string line;
    if (!file.is_open()) 
    {
        cerr << "Error opening file: " << filename << endl;
        return;
    }
    while (getline(file, line)) 
    {
        stringstream ss(line);
        string word;
        ss >> word;
        int label = stoi(word);
        labels.push_back(label);
    }
    file.close();
}

void make_P_S_N() {
    int count_S = 0, count_N = 0;
    for (const auto& label : labels) {
        if (label == S) {
            count_S++;
        } else if (label == N) {
            count_N++;
        }
    }
    P_S = static_cast<float>(count_S) / (float)(labels.size());
    P_N = static_cast<float>(count_N) / (float)(labels.size());  
}

void make_train_data_vector(string filename) {
    train_data[N].resize(2501);
    train_data[S].resize(2501);
    int word_S = 0, word_N = 0;
    fstream file(filename);
    string line;
    if (!file.is_open())
    {
        cerr << "Error opening file: " << filename << endl;
        return;
    }
    while (getline(file, line))
    {
        stringstream ss(line);
        string word;
        ss >> word;
        int Label_index = stoi(word);
        ss >> word; 
        int word_index = stoi(word);
        ss >> word;
        float freq = stof(word);
        if (labels[Label_index] == S)
        {
            train_data[S][word_index] += freq;
        }
        else if (labels[Label_index] == N)
        {
            train_data[N][word_index] += freq;
        }
    }
    for(size_t i = 0; i < train_data[N].size(); i++){
        word_N += (int)(train_data[N][i]);
    }
    for (size_t i = 0; i < train_data[S].size(); i++)
    {
        word_S += (int)(train_data[S][i]);
    }
    for(int i = N ; i <= S; i++){
        for(size_t j = 0; j < train_data[i].size(); j++){
            if(i == N){
                train_data[i][j] = (train_data[i][j] + 1) / (float)(word_N + total_words);
            }
            else if(i == S){
                train_data[i][j] = (train_data[i][j] + 1) / (float)(word_S + total_words);
            }
        }
    }
    
}

void make_test_data_vector(string filename) {
    test_data.resize(test_labels.size()+1);
    fstream file(filename);
    string line;
    if (!file.is_open()) 
    {
        cerr << "Error opening file: " << filename << endl;
        return;
    }
    for (size_t i = 0; i < test_labels.size()+1; i++) 
    {
        test_data[i].resize(2501); // Initialize with 0s
    }
    cout<< "test_labels size: " << test_labels.size() << endl;
    while (getline(file, line)) 
    {
        stringstream ss(line);
        string word;
        ss >> word;
        int Label_index = stoi(word);
        ss >> word; 
        int word_index = stoi(word);
        ss >> word;
        int freq = stoi(word);
        test_data[Label_index][word_index] = freq;
    }

}