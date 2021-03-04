#include "path_manager.h"

namespace fs = boost::filesystem;

PathManager::PathManager(const std::string& output_directory)
{
    fs::path curr_abs_path = fs::current_path();
    _output_dir = curr_abs_path / fs::path(output_directory);

    fs::create_directory(_output_dir);
}

std::string PathManager::get_filename_in_output_directory(const std::string& filename)
{
    return (_output_dir / fs::path(filename)).string();
}

std::vector<fs::path> PathManager::get_all(const std::string& root_dir_name, const std::string& ext)
{
    std::vector<fs::path> paths;
    fs::path root(root_dir_name);

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