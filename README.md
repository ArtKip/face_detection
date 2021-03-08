# face_detection
c++ app for detecting and bluring faces.

face_detector_tool is command line executable, 
it consumes path to directory,
finds all .jpg and .png images in all inner subdirectories,
detects faces on them,
blurs faces and saves processed image,
also prepares report in json format.

In order to build project:
1. Install and add to PATH boost and opecv.
2. build project with cmake.

It can be used on Windows and Linux. 
