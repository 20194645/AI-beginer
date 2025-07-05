#include "naive_bayes.h"

void check_zero_probabilities() {
    bool found = false;
    for (size_t class_idx = 0; class_idx < train_data.size(); ++class_idx) {
        for (size_t word_idx = 0; word_idx < 2501; ++word_idx) {
            if (train_data[class_idx][word_idx] == 0.0f) {
                std::cout << "[ZERO] train_data[" << class_idx 
                          << "][" << word_idx << "] = 0.0\n";
                found = true;
            }
        }
    }
    if (!found) {
        std::cout << "✅ No zero values found in train_data.\n";
    }
}


int main(){
    make_labels_vector(train_label_fn, labels);
    make_labels_vector(test_label_fn, test_labels);
    make_P_S_N();
    std::cout << "P_S: " << P_S << ", P_N: " << P_N << std::endl;
    make_test_data_vector(test_data_fn);
    std::cout<<labels.size()<<" "<<test_labels.size()<<std::endl;
    make_train_data_vector(train_data_fn);
    check_zero_probabilities();
    std::vector<int> result =  predict();
    compare(result);
    //display_train_data();
}