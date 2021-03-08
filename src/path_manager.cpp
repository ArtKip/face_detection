#include "path_manager.h"

namespace fs = boost::filesystem;

PathManager::PathManager(const std::string& output_directory)
    : _output_dir(fs::path(output_directory))
{
}

bool PathManager::is_correct() const
{
    if (fs::exists(_output_dir) && fs::is_directory(_output_dir))
    {
        return true;
    }
    return false;
}

std::string PathManager::get_filename_in_output_directory(const std::string& filename)
{
    return (_output_dir / fs::path(filename)).string();
}

std::vector<fs::path> PathManager::get_all(const std::vector<std::string>& exts)
{
    std::vector<fs::path> paths;

    if (fs::exists(_output_dir))
    {
        for (auto const& entry : fs::recursive_directory_iterator(_output_dir))
        {
            if (fs::is_regular_file(entry) &&
                std::find(exts.begin(), exts.end(), entry.path().extension()) != exts.end())
            {
                paths.emplace_back(entry.path());
            }
        }
    }

    return paths;
}

std::string PathManager::get_processed_image_path(const std::string& filename)
{
    const auto modified_filename = modify_filename(filename);
    return (_output_dir / fs::path(modified_filename)).string();
}

std::string PathManager::modify_filename(const std::string& filename)
{
    return "processed_" + filename;
}
