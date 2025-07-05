#ifndef READINPUT_H
#define READINPUT_H
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#define S 1
#define N 0
#define total_words 2500

extern std::string train_data_fn ;
extern std::string test_data_fn ;
extern std::string train_label_fn ;
extern std::string test_label_fn ;
extern float P_S, P_N; // Probabilities of classes S and N


extern std::vector<int> labels; // 1 to cover indices 0, 1
extern std::vector<int> test_labels; // 2 to cover indices 0, 1
extern void make_P_S_N();
extern std::vector<std::vector<float>> train_data; // 2 to cover indices 0, 1
extern std::vector<std::vector<int>> test_data; // 2 to cover indices 0, 1
void make_labels_vector(std::string filename, std::vector<int>& labels);
void make_train_data_vector(std::string filename);
void make_test_data_vector(std::string filename);

#endif