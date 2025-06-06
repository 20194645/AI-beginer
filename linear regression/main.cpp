#include<iostream>
using namespace std;

int number_of_samples = 13;
float height[20][20] = {{147, 150, 153, 158, 163, 165, 168, 170, 173, 175, 178, 180, 183}};
float weight[20][20] = {{49}, {50}, {51}, {54}, {58}, {59}, {60}, {62}, {63}, {64}, {66}, {67}, {68}};
float w[20][20];


void preprocess_data(){
    for(int i = 0; i < number_of_samples; i++){
        height[1][i] = 1; // Adding a bias term
    }
}   

// Function to transpose a matrix

void transpose_matrix(float a[][20], float tmp[][20], int rows){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < number_of_samples; j++){
           tmp[j][i] = a[i][j];
        }
    }
}

// Matrix multiplication function

void mul_matrix(float a[][20],float b[][20],float c[][20], int a_rows ,int a_cols_b_rows , int b_cols){
    for(int i = 0; i < a_rows; i++){
        for(int j = 0; j < b_cols; j++){
            c[i][j] = 0;
            for(int k = 0; k < a_cols_b_rows; k++){
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

// Function to calculate inverse of matrix using Gaussian elimination
void inverse_matrix(float a[][20], float inv[][20], int n) {
    // Initialize the inverse matrix to the identity matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j)
                inv[i][j] = 1;
            else
                inv[i][j] = 0;
        }
    }

    // Perform Gaussian elimination
    for (int i = 0; i < n; i++) {
        float diag = a[i][i];
        for (int j = 0; j < n; j++) {
            a[i][j] /= diag;
            inv[i][j] /= diag;
        }
        for (int j = 0; j < n; j++) {
            if (j != i) {
                float factor = a[j][i];
                for (int k = 0; k < n; k++) {
                    a[j][k] -= factor * a[i][k];
                    inv[j][k] -= factor * inv[i][k];
                }
            }
        }
    }
}

// Linear regression prediction process

void process_predict(){
    float height_T[20][20];
    float mul_result[20][20];
    float Pseudo_inverse[20][20];
    float tmp[20][20];
    transpose_matrix(height, height_T, 2); 
    mul_matrix(height, height_T, mul_result, 2, number_of_samples, 2);
    inverse_matrix(mul_result, Pseudo_inverse, 2);
    mul_matrix(Pseudo_inverse, height, tmp, 2, 2, number_of_samples);
    mul_matrix(tmp, weight, w, 2, number_of_samples, 1);
}

void display(){
    cout<< "W matrix : " << endl;
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 1    ; j++){
            cout << w[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Predict weught of a persion with height 155 cm is: " << w[0][0]* 155 + w[1][0] << endl;
    cout << "Predict weught of a persion with height 160 cm is: " << w[0][0]* 160 + w[1][0] << endl;
}


int main(){
    preprocess_data();
    process_predict();
    display();
    
    // Linear regression logic would go here, but is not implemented in this example.
    // This is where you would typically calculate the weights based on the height and weight data.

    return 0;
}