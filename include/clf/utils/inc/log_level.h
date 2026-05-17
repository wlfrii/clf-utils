#ifndef H_CLF_BF680D7A_1010_44CA_AA77_0095DDC00D4D
#define H_CLF_BF680D7A_1010_44CA_AA77_0095DDC00D4D
#include <cstdint>

namespace clf {
namespace log {

/**
 * @brief Log level definition.
 */
enum class Level : uint8_t {
    FATAL,      ///< For fatal error level, identified as [F].
    ERROR,      ///< For error level, identified as [E].
    WARNING,    ///< For warning level, identified as [W].
    NOTICE,     ///< For notice level, identified as [N].
    DEBUG,      ///< For debug level, identified as [D].
    TRACE       ///< For trace level, identified as [T].
};

}} // namespace clf::log
#endif /* H_CLF_BF680D7A_1010_44CA_AA77_0095DDC00D4D */
