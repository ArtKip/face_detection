#pragma once

#include "json/json.h"
#include <opencv2/opencv.hpp>

class JsonResultsSaver {
public:
    JsonResultsSaver(const std::string& path);
    void append_image_with_rectangles(const std::string& imagename, const std::vector<cv::Rect>& rectangles);
    void write_to_file() const;

private:
    Json::Value _root;
    std::string _path;
};