#include "gtest/gtest.h"
#include <opencv2/opencv.hpp>

#include "face_detector.h"
#include "image_processor.h"
#include "path_manager.h"

TEST(FaceDetectorTest, ComparePreparedFaces)
{
    const auto files = PathManager::get_all("../", ".jpg");

    ASSERT_TRUE(files.size() > 0);

    FaceDetector face_detector;

    for (const auto& file : files)
    {
        ImageProcessor image_processor(file.string(), face_detector);

        ASSERT_NO_THROW(image_processor.process_image());

        const auto faces = image_processor.get_face_rectangles();

        const int abs_error = 5;

        if (file.filename().string() == "bird.jpg")
        {
            ASSERT_EQ(faces.size(), 0);
        }
        if (file.filename().string() == "man.jpg")
        {
            ASSERT_EQ(faces.size(), 1);
            ASSERT_NEAR(faces.at(0).x, 119, abs_error);
            ASSERT_NEAR(faces.at(0).y, 30, abs_error);
            ASSERT_NEAR(faces.at(0).width, 30, abs_error);
            ASSERT_NEAR(faces.at(0).height, 44, abs_error);
        }
        if (file.filename().string() == "foot_team.jpg")
        {
            ASSERT_EQ(faces.size(), 5);
        }
    }
}

