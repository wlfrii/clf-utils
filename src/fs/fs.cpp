#include <clf/utils/fs.h>
#include <filesystem>

namespace clf {
namespace fs {

bool createPathIfNotExists(const std::string& path) {
    std::error_code error;
    if (std::filesystem::exists(path, error)) {
        return !error && std::filesystem::is_directory(path, error) && !error;
    }
    return !error && std::filesystem::create_directories(path, error) && !error;
}

std::string getFilename(const std::string& filepath) {
    return std::filesystem::path(filepath).filename().string();
}

}} // namespace clf::fs
