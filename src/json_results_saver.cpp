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
        Json::Value rect;

        rect["x"] = rectangles[i].x;
        rect["y"] = rectangles[i].y;
        rect["width"] = rectangles[i].width;
        rect["height"] = rectangles[i].height;

        data["rect_" + std::to_string(i)] = rect;
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
