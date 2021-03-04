#pragma once

#include <boost/filesystem.hpp>

class PathManager {
public:
    explicit PathManager(const std::string& output_directory);

    std::string get_filename_in_output_directory(const std::string& filename);

    static std::vector<boost::filesystem::path> get_all(const std::string& root_dir_name, const std::string& ext);


private:
    boost::filesystem::path _output_dir;
};