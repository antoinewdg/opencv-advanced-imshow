//
// Created by antoinewdg on 10/18/16.
//

#ifndef OPENCV_ADVANCED_IMSHOW_RGBA_TRANSFORMER_H
#define OPENCV_ADVANCED_IMSHOW_RGBA_TRANSFORMER_H

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace oai {
    using cv::Mat_;
    using cv::Vec4b;
    using cv::Vec3b;

    template<class T>
    struct RGBATransformer {
        static inline Mat_<Vec4b> to_rgba(Mat_<T> src);
    };

    template<>
    Mat_<Vec4b> RGBATransformer<Vec3b>::to_rgba(Mat_<Vec3b> src) {
        Mat_<Vec4b> out;
        cv::cvtColor(src, out, cv::COLOR_BGR2RGBA);
        return out;
    }

    template<>
    Mat_<Vec4b> RGBATransformer<uchar>::to_rgba(Mat_<uchar> src) {
        Mat_<Vec4b> out;
        cv::cvtColor(src, out, cv::COLOR_GRAY2RGBA);
        return out;
    }

    template<>
    Mat_<Vec4b> RGBATransformer<float>::to_rgba(Mat_<float> src) {
//        src = src.clone() * 255.f;
        Mat_<uchar> intermediate;
        src.convertTo(intermediate, CV_8U, 255);
        return RGBATransformer<uchar>::to_rgba(intermediate);
    }




//    template<>
//    int RGBATransformer<Vec3b>::get_cvt_code() {
//        return cv::COLOR_BGR2RGBA;
//    }
//
//    template<>
//    Mat_<Vec3b> RGBATransformer<Vec3b>::scale_before_rgba(Mat_<Vec3b> src) {
//        return src;
//    }
//
//    template<>
//    int RGBATransformer<float>::get_cvt_code() {
//        return cv::COLOR_GRAY2RGBA;
//    }
//
//    template<>
//    Mat_<float> RGBATransformer<float>::scale_before_rgba(Mat_<float> src) {
//        return Mat_<float>(src * 255.f).clone();
//    }
}

#endif //OPENCV_ADVANCED_IMSHOW_RGBA_TRANSFORMER_H
