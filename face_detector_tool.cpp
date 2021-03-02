#include <stdio.h>
#include <opencv2/opencv.hpp>

#include "face_detector.h"
#include <boost/filesystem.hpp>


using namespace std;
namespace fs = boost::filesystem;

std::vector<fs::path> get_all(const fs::path& root, const std::string& ext)
{
    std::vector<fs::path> paths;

    if (fs::exists(root) && fs::is_directory(root))
    {
        for (auto const& entry : fs::recursive_directory_iterator(root))
        {
            if (fs::is_regular_file(entry) && entry.path().extension() == ext)
                paths.emplace_back(entry.path());
        }
    }

    return paths;
}

int main(int argc, char** argv)
{
    try
    {
        std::cout << "Enter path of folder with images" << std::endl;

        std::string str;
        std::getline(std::cin, str);

        fs::path dir(str);
        const auto files = get_all(dir, ".jpg");

        FaceDetector face_detector;

        for (const auto& file : files)
        {
            cv::Mat image;
            image = cv::imread(file.string());

            std::cout << file.string() << std::endl;

            auto rectangles = face_detector.detect_face_rectangles(image);

            cv::Scalar color(0, 105, 205);

            for (const auto& r : rectangles) {
                cv::rectangle(image, r, color, 1);
                std::cout << r << std::endl;
                cv::GaussianBlur(image(r), image(r), cv::Size(101, 101), 0);
            }
            cv::resize(image, image, cv::Size(), 0.5, 0.5);

            cv::imwrite(file.filename().string(), image);
        }
        std::cout << "finish" << std::endl;
        

    }
    catch (std::runtime_error e)
    {
        std::cout << e.what() << std::endl;
    }


    return 0;
}
