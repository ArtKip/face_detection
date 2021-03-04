#include "json_results_saver.h"

#include <fstream>

JsonResultsSaver::JsonResultsSaver(const std::string& path)
    : _path(path)
{   
}

void JsonResultsSaver::append_image_with_rectangles(const std::string& imagename, const std::vector<cv::Rect>& rectangles)
{
    Json::Value data;

    for (int i = 0; i < rectangles.size(); ++i) 
    {
        data["Rect_" + std::to_string(i) + ".X"] = rectangles[i].x;
        data["Rect_" + std::to_string(i) + ".Y"] = rectangles[i].y;
        data["Rect_" + std::to_string(i) + ".Width"] = rectangles[i].width;
        data["Rect_" + std::to_string(i) + ".Height"] = rectangles[i].height;
    }

    if (data.isNull())
    {
        data = "No faces found";
    }
    _root[imagename] = data;
}

void JsonResultsSaver::write_to_file() const
{
    std::ofstream file(_path);

    Json::StreamWriterBuilder builder;

    file << Json::writeString(builder, _root);

    file.close();
}
