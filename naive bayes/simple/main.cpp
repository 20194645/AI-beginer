    #include <iostream>
    #include <vector>
    #include <string>
    #include <sstream>
    #include <unordered_map>
    #define B 1
    #define N 2
    using namespace std;

    typedef struct value
    {
        int frequency;
        int label; // 1 for B, 2 for N
        float B_probability;
        float N_probability;    
    };

    vector<vector<string>> train_data(3); // 3 to cover indices 0, 1, 2
    unordered_map<string, value> word_map;


    void init_train_data()
    {
        train_data[B] = {
            "hanoi pho chaolong hanoi",
            "hanoi buncha pho omai",
            "pho banhgio omai",
        };

        train_data[N] = {
            "saigon hutiu banhbo pho"};
    }

    void preprocess_train_data(){
        int word_B = 0, word_N = 0;
        for(int i = B; i <= N; i++) {
            for(auto sentence : train_data[i]) {
                stringstream ss(sentence);
                string word;
                while(ss >> word) {
                    int label;
                    if (i == B)
                    {
                        label = B;
                        word_B++;
                    }
                    if ( i == N)
                    {
                        label = N;
                        word_N++;
                    }
                    
                    if(word_map.find(word) == word_map.end()) {
                        word_map[word] = {0,label,0.0f, 0.0f};
                    }
                    word_map[word].frequency++;
                }
            }
        }
        for(auto& entry : word_map) {
            if (entry.second.label == B) {
                entry.second.B_probability = static_cast<float>(entry.second.frequency + 1) / (word_B+word_map.size());
                entry.second.N_probability = static_cast<float>(1) / (word_N+word_map.size());
            }
            else if (entry.second.label == N) {
                entry.second.B_probability = static_cast<float>(1) / (word_B+word_map.size());
                entry.second.N_probability = static_cast<float>(entry.second.frequency + 1) / (word_N+word_map.size());
            }
            
        }
    }

    void print_word_map() {
        for (const auto& entry : word_map) {
            cout << "Word: " << entry.first << ", Frequency: " << entry.second.frequency
                << ", Label: " << (entry.second.label == B ? "B" : "N")
                << ", B Probability: " << entry.second.B_probability
                << ", N Probability: " << entry.second.N_probability << endl;
        }
    }

    void naive_bayes_classifier(const string& sentence) {
        stringstream ss(sentence);
        string word;
        float b_probability = 1.0f;
        float n_probability = 1.0f;
        while ( ss >> word)
        {
            b_probability *= word_map[word].B_probability;
            n_probability *= word_map[word].N_probability;
        }
        float P_b = (float)(train_data[B].size()) / (float)(train_data[B].size() + train_data[N].size());
        float P_n = (float)(train_data[N].size()) / (float)(train_data[B].size() + train_data[N].size());
        b_probability *= P_b;
        n_probability *= P_n;
        cout << "Probability of B: " << b_probability << endl;
        cout << "Probability of N: " << n_probability << endl;  
        if (b_probability > n_probability) {
            cout << "The sentence is classified as B." << endl;
        }
        else if (n_probability < b_probability) {
            cout << "The sentence is classified as N." << endl;
        }

    }

    int main()
    {
        init_train_data();
        preprocess_train_data();
        //print_word_map();
        naive_bayes_classifier(" hanoi hanoi buncha hutiu");
        return 0;
    }
