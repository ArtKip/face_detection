#include "image_processor.h"


ImageProcessor::ImageProcessor(const std::string& path, const FaceDetector& face_detector)
    : _face_detector(face_detector),
    _path(path)
{
    _image = cv::imread(path);
}

void ImageProcessor::process_image()
{
    _face_rectangles = _face_detector.detect_face_rectangles(_image);

    blur_faces(_face_rectangles);

    cv::resize(_image, _image, cv::Size(), 0.5, 0.5);

    _image_processed = true;
}

void ImageProcessor::save_processed_image(const std::string& path) const
{
    if (!_image_processed)
    {
        log_warning();
    }
    cv::imwrite(path, _image);
}

void ImageProcessor::blur_faces(const std::vector<cv::Rect>& rectangles)
{
    const auto kernel_size = cv::Size(101, 101);

    for (const auto& r : rectangles)
    {
        cv::GaussianBlur(_image(r), _image(r), kernel_size, 0);
    }
}

void ImageProcessor::log_warning() const noexcept
{
    std::cout << "Saving of unprocessed image " << _path << std::endl;
}

std::vector<cv::Rect> ImageProcessor::get_face_rectangles() const noexcept
{
    if (!_image_processed)
    {
        log_warning();
    }
    return _face_rectangles;
}
