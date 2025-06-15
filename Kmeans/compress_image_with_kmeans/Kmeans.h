#ifndef KMEANS_H
#define KMEANS_H

#include "common.h"
#include <iostream>
#include <vector>
#include <set>
#include <limits>
#include <cstdlib>

std::vector<Pixel>kmeans_init_centroids(std::vector<Pixel> src, int k);
std::vector<std::vector<int>> labels(const std::vector<Pixel>& centroids, const std::vector<Pixel>& src);
std::vector<Pixel> kmeans_update_centroids(const std::vector<std::vector<int>>& labels, const std::vector<Pixel>& src);
bool kmeans_converged(const std::vector<Pixel>& old_c, const std::vector<Pixel>& new_c);
void kmeans(const std::vector<Pixel> &src,int k, std::vector<Pixel> &centroids, std::vector<std::vector<int>> &rgb_labels);

#endif