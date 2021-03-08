#pragma once

#include <boost/filesystem.hpp>

class PathManager {
public:
    explicit PathManager(const std::string& output_directory);
    std::string get_filename_in_output_directory(const std::string& filename);
    std::vector<boost::filesystem::path> get_all(const std::vector<std::string>& exts);
    bool is_correct() const;
    std::string get_processed_image_path(const std::string& filename);

private:
    static std::string modify_filename(const std::string& filename);

private:
    boost::filesystem::path _output_dir;
};