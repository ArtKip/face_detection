#include <stdio.h>
#include <opencv2/opencv.hpp>

#include "face_detector.h"

int main(int argc, char** argv)
{
    try
    {
        FaceDetector face_detector;

        cv::Mat image;
        image = cv::imread("photo_2021-02-01_09-50-37.jpg");

        auto rectangles = face_detector.detect_face_rectangles(image);

        cv::Scalar color(0, 105, 205);

        for (const auto& r : rectangles) {
            cv::rectangle(image, r, color, 4);
        }

        cv::imshow("Image", image);

        cv::waitKey(0);
    }
    catch (std::invalid_argument e)
    {
        std::cout << e.what() << std::endl;
    }


    return 0;
}