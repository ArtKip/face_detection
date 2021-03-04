#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <filesystem>

#include "face_detector.h"

FaceDetector::FaceDetector() : _confidence_threshold(0.5), _input_image_height(300), _input_image_width(300),
_scale_factor(1.0), _mean_values({ 104., 177.0, 123.0 }) {

    _network = cv::dnn::readNetFromCaffe(FACE_DETECTION_CONFIGURATION, FACE_DETECTION_WEIGHTS);

    // Note: The varibles MODEL_CONFIGURATION_FILE and MODEL_WEIGHTS_FILE are passed(network_.empty()) {
        //std::ostringstream ss;
        //ss << "Failed to load network with the following settings:\n"
        //    << "Configuration: " + std::string(FACE_DETECTION_CONFIGURATION) + "\n"
        //    << "Binary: " + std::string(FACE_DETECTION_WEIGHTS) + "\n";
        //throw std::invalid_argument(ss.str());
    }


std::vector<cv::Rect> FaceDetector::detect_face_rectangles(const cv::Mat& frame) {
    cv::Mat input_blob = cv::dnn::blobFromImage(frame, _scale_factor, cv::Size(_input_image_width, _input_image_height),
        _mean_values, false, false);
    _network.setInput(input_blob, "data");
    cv::Mat detection = _network.forward("detection_out");
    cv::Mat detection_matrix(detection.size[2], detection.size[3], CV_32F, detection.ptr<float>());

    std::vector<cv::Rect> faces;

    for (int i = 0; i < detection_matrix.rows; i++) {
        float confidence = detection_matrix.at<float>(i, 2);

        if (confidence < _confidence_threshold) {
            continue;
        }
        int x_left_bottom = static_cast<int>(detection_matrix.at<float>(i, 3) * frame.cols);
        int y_left_bottom = static_cast<int>(detection_matrix.at<float>(i, 4) * frame.rows);
        int x_right_top = static_cast<int>(detection_matrix.at<float>(i, 5) * frame.cols);
        int y_right_top = static_cast<int>(detection_matrix.at<float>(i, 6) * frame.rows);

        faces.emplace_back(x_left_bottom, y_left_bottom, (x_right_top - x_left_bottom), (y_right_top - y_left_bottom));
    }

    return faces;
}
