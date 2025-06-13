#include "Matirx_input.h"

void readData(const std::string& X_Data, const std::string& Z_data) {
    std::ifstream xFile(X_Data);
    std::ifstream zFile(Z_data);
    
    if (!xFile.is_open() || !zFile.is_open()) {
        std::cerr << "Error opening file(s)." << std::endl;
        return;
    }

    int i = 0, j = 0;
    while (xFile >> x[i][j]) {
        j++;
        if (j == 100) {
            j = 0;
            i++;
        }
    }

    i = 0;
    while (zFile >> z[i]) {
        i++;
    }

    xFile.close();
    zFile.close();
}