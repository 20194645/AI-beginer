#ifndef IMAGE_PROCESS_H
#define IMAGE_PROCESS_H

#include <opencv2/opencv.hpp>
#include <vector>
#include <fstream>
#include "common.h"

void readImage(const std::string &filename, std::vector<Pixel> &image, int &width, int &height);
void reconstructImage(
                      const std::string &filename,
                      const std::vector<std::vector<int>> &labels,
                      const std::vector<Pixel> &centroids,
                      int width, int height
                     );
#endif
