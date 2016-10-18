#include <iostream>
#include "oai/image_view.h"

int main(int argc, char *argv[]) {

    if (argc < 2) {
        std::cerr << "Enter the image path as argument." << std::endl;
    }
    cv::Mat_<cv::Vec3b> image = cv::imread(argv[1]);
    oai::ImageView view(image);
    view.display();

    return 0;
}