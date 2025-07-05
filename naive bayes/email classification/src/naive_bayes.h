#ifndef NAIVE_BAYES_H
#define NAIVE_BAYES_H
#include "Readinput.h"

void display_train_data();
extern std::vector<int> predict();
void compare(std::vector<int> predictions);


#endif