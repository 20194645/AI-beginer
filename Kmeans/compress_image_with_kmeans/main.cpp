#include "Image_process.h"
#include "Kmeans.h"
#include <string>

int main(){
    std::string filename = "image/image.jpg"; // Replace with your image file
    try {
        std::vector<Pixel> image;
        int width, height;
        readImage(filename, image, width, height);
        std::cout << image.size() << " pixels read from image." << std::endl;
        std::vector<Pixel> centroids;
        std::vector<std::vector<int>> rgb_labels;
        kmeans(image,5,centroids,rgb_labels);
        std::string outputfile = "out.jpg";
        reconstructImage(filename,rgb_labels,centroids,width,height);
        // Further processing can be done here
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}