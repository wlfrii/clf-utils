#ifndef H_CLF_C34E641A_6748_4294_8D7E_8E17E62CEC98
#define H_CLF_C34E641A_6748_4294_8D7E_8E17E62CEC98
#include <clf/utils/log.h>

namespace clf {
namespace log {

inline char logIdentifier(Level level) noexcept {
    switch (level) {
        case Level::FATAL:   return 'F';
        case Level::ERROR:   return 'E';
        case Level::WARNING: return 'W';
        case Level::DEBUG:   return 'D';
        case Level::TRACE:   return 'T';
    }
    return '?';
}

}} // namespace clf::log

#endif /* H_CLF_C34E641A_6748_4294_8D7E_8E17E62CEC98 */
