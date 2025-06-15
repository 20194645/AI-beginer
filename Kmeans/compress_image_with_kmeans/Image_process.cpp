#include "Image_process.h"

void readImage(const std::string &filename, std::vector<Pixel> &image, int &width, int &height)
{
    cv::Mat img = cv::imread(filename, cv::IMREAD_COLOR); // đọc ảnh BGR 8-bit 3 kênh
    if (img.empty())
    {
        throw std::runtime_error("Không thể mở ảnh: " + filename);
    }

    width = img.cols;
    height = img.rows;

    image.clear();                 // xoá dữ liệu cũ
    image.reserve(width * height); // cấp phát đủ bộ nhớ trước

    for (int y = 0; y < height; ++y)
    {
        const cv::Vec3b *row = img.ptr<cv::Vec3b>(y); // truy cập dòng ảnh
        for (int x = 0; x < width; ++x)
        {
            const cv::Vec3b &bgr = row[x];
            Pixel p = {bgr[2], bgr[1], bgr[0]}; // chuyển từ BGR sang RGB
            image.push_back(p);
        }
    }
}

void reconstructImage(
    const std::string &input_filename,
    const std::vector<std::vector<int>> &labels,
    const std::vector<Pixel> &centroids,
    int width, int height)
{
    if (width * height == 0) {
        throw std::runtime_error("Kích thước ảnh không hợp lệ");
    }

    if (labels.size() != centroids.size()) {
        throw std::runtime_error("Số label không khớp với số centroid");
    }

    cv::Mat img(height, width, CV_8UC3, cv::Scalar(0, 0, 0)); // ảnh đen mặc định

    for (size_t cluster_idx = 0; cluster_idx < labels.size(); ++cluster_idx) {
        const Pixel& color = centroids[cluster_idx];
        const std::vector<int>& indices = labels[cluster_idx];

        for (int idx : indices) {
            if (idx < 0 || idx >= width * height) continue;

            int y = idx / width;
            int x = idx % width;

            img.at<cv::Vec3b>(y, x) = cv::Vec3b(color.b, color.g, color.r); // RGB → BGR
        }
    }

    std::string output_filename = "output_compressed.jpg";

    if (!cv::imwrite(output_filename, img)) {
        throw std::runtime_error("Không thể ghi ảnh ra file: " + output_filename);
    }

    std::cout << "Đã ghi ảnh nén ra: " << output_filename << std::endl;
}
