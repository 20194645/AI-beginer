#include "process.h"
#include <cmath>
#include <chrono>
using namespace std::chrono;
float x[1001][101];
float z[101];
void dist_ps_naive(float result[])
{
    for (int i = 0; i < 1000; i++)
    {
        result[i] = 0.0f;
        for (int j = 0; j < 100; j++)
        {
            float diff = x[i][j] - z[j];
            result[i] += diff * diff; // Using squared difference directly
        }
    }
}

void dist_ps_optimized(float result[])
{

    // Calculate z_2
    float z_2 = 0.0f;
    for (int i = 0; i < 100; i++)
    {
        z_2 += z[i] * z[i]; // Using squared value of z
    }

    for (int i = 0; i < 1000; i++)
    {
        float x_2 = 0.0f;
        float tmp = 0.0f;
        for (int j = 0; j < 100; j++)
        {
            x_2 += x[i][j] * x[i][j];  // Using squared value of x
            tmp += 2 * x[i][j] * z[j]; // Using dot product for x and z
        }

        result[i] = x_2 + z_2 - tmp;
    }
}

bool Check(float res1[], float res2[])
{
    for (int i = 0; i < 1000; i++)
    {
        if (std::abs(res1[i] - res2[i]) > 1e-3)
        { // Using a small epsilon for floating point comparison
            std::cout << "Mismatch at index " << i << ": " << res1[i] << " vs " << res2[i] << std::endl;
            return false;
        }
    }
    return true;
}

int main()
{
    readData("../Create_Dataset/X.txt", "../Create_Dataset/z.txt");
    float result[1000];
    float result_optimized[1000];
    auto start_naive = high_resolution_clock::now();
    dist_ps_naive(result);
    auto end_naive = high_resolution_clock::now();
    auto duration_naive = duration_cast<microseconds>(end_naive - start_naive).count();
    std::cout << "Naive time: " << duration_naive << " microseconds\n";
    auto start_opt = high_resolution_clock::now();
    dist_ps_optimized(result_optimized);
    auto end_opt = high_resolution_clock::now();
    auto duration_opt = duration_cast<microseconds>(end_opt - start_opt).count();
    std::cout << "Optimized time: " << duration_opt << " microseconds\n";
    if (Check(result, result_optimized))
    {
        std::cout << "The results are equal." << std::endl;
    }
    else
    {
        std::cout << "The results are not equal." << std::endl;
    }
}