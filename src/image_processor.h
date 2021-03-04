#pragma once

#include <opencv2/opencv.hpp>

#include "face_detector.h"

class ImageProcessor {
public:
    ImageProcessor(const std::string& path, const FaceDetector& face_detector);
    void process_image();
    void save_processed_image(const std::string& path) const;
    std::vector<cv::Rect> get_face_rectangles() const noexcept;

private:
    void blur_faces(const std::vector<cv::Rect>& rectangles);
    void log_warning() const noexcept;

private:
    FaceDetector _face_detector;
    cv::Mat _image;
    bool _image_processed{false};
    std::vector<cv::Rect> _face_rectangles{};
    std::string _path;
};
