#include <opencv2/opencv.hpp>
#include <stdio.h>

#include "face_detector.h"
#include "image_processor.h"
#include "json_results_saver.h"
#include "path_manager.h"

int main(int argc, char** argv)
{
    std::cout << "Enter path of folder with images having .jpg extension: " << std::endl;

    std::string input_dir_path;
    std::getline(std::cin, input_dir_path);

    const auto files = PathManager::get_all(input_dir_path, ".jpg");

    PathManager path_manager("output");

    JsonResultsSaver json_writer(path_manager.get_filename_in_output_directory("results.json"));

    FaceDetector face_detector;

    for (const auto& file : files)
    {
        try
        {
            ImageProcessor image_processor(file.string(), face_detector);

            image_processor.process_image();

            image_processor.save_processed_image(path_manager.get_filename_in_output_directory(file.filename().string()));

            json_writer.append_image_with_rectangles(file.filename().string(), image_processor.get_face_rectangles());

        }
        catch (...)
        {
            std::cout << "failed to process " << file.filename().string() << std::endl;
        }
    }
        
    json_writer.write_to_file();
    

    return 0;
}
