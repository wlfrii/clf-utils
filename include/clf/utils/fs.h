#ifndef H_CLF_BAAF537F_193E_4100_9CDA_6F5809C3ED33
#define H_CLF_BAAF537F_193E_4100_9CDA_6F5809C3ED33
#include <string>

namespace clf {
namespace fs {

/**
 * @brief Create a path if not exists.
 * 
 * @param path The specified path.
 */
bool createPathIfNotExists(const std::string& path);

/**
 * @brief Get the filename from a given file path.
 * 
 * @param path The specified file path.
 */
std::string getFilename(const std::string& filepath);

}} // namespace clf::fs
#endif /* H_CLF_BAAF537F_193E_4100_9CDA_6F5809C3ED33 */
