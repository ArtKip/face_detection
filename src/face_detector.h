#pragma once

#include <opencv2/dnn.hpp>

class FaceDetector {
public:
    FaceDetector();

    std::vector<cv::Rect> detect_face_rectangles(const cv::Mat& frame);

private:
    /// Face detection network
    cv::dnn::Net _network;
    /// Input image width
    const int _input_image_width;
    /// Input image height
    const int _input_image_height;
    /// Scale factor when creating image blob
    const double _scale_factor;
    /// Mean normalization values network was trained with
    const cv::Scalar _mean_values;
    /// Face detection confidence threshold
    const float _confidence_threshold;

};