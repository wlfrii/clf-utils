#include <clf/utils/fs.h>
#include <filesystem>

namespace clf {
namespace fs {

bool createPathIfNotExists(const std::string& path) {
    if (std::filesystem::exists(path)) {
        return true;
    }
    return std::filesystem::create_directories(path);
}

std::string getFilename(const std::string& filepath) {
    return std::filesystem::path(filepath).filename();
}

}} // namespace clf::fs