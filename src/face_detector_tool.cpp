#include <opencv2/opencv.hpp>
#include <stdio.h>

#include "face_detector.h"
#include "image_processor.h"
#include "json_results_saver.h"
#include "path_manager.h"

using namespace std;

int main(int argc, char** argv)
{
    cout << "Enter path of folder with images having .jpg or .png extension: " << endl;

    string input_dir_path;
    getline(cin, input_dir_path);

    PathManager path_manager(input_dir_path);
    if (!path_manager.is_correct())
    {
        cout << "incorect direcory path " << input_dir_path << endl;
        return 0;
    }

    const auto files = path_manager.get_all(vector<string>{".png", ".jpg"});

    JsonResultsSaver json_writer(path_manager.get_filename_in_output_directory("results.json"));

    FaceDetector face_detector;

    for (const auto& file : files)
    {
        try
        {
            ImageProcessor image_processor(file.string(), face_detector);
            image_processor.process_image();

            const auto processed_image_path = path_manager.get_processed_image_path(file.filename().string());
            image_processor.save_processed_image(processed_image_path);

            json_writer.append_image_with_rectangles(processed_image_path, image_processor.get_face_rectangles());

            cout << image_processor.get_face_rectangles().size() << " faces found on image " << file.string() << endl;
        }
        catch (...)
        {
            cout << "failed to process " << file.filename().string() << endl;
        }
    }
        
    json_writer.write_to_file();   

    return 0;
}
