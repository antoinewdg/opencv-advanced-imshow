#include <iostream>

#include <opencv2/imgcodecs.hpp>

#include "oai/image_view.h"

int main(int argc, char *argv[]) {

    if (argc < 2) {
        std::cerr << "Enter the image path as argument." << std::endl;
    }
    cv::Mat_<uchar> image = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
    cv::Mat_<float> f;
    image.convertTo(f, CV_32F, 1.f / 255);
    oai::ImageView view(f);
    view.display();

    return 0;
}