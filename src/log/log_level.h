#ifndef H_CLF_C34E641A_6748_4294_8D7E_8E17E62CEC98
#define H_CLF_C34E641A_6748_4294_8D7E_8E17E62CEC98
#include <clf/utils/log.h>
#include <unordered_map>

namespace clf {
namespace log {

inline const char logIdentifier(Level level) {
    static const std::unordered_map<Level, char> map = {
        { Level::FATAL,     'F' },
        { Level::ERROR,     'E' },
        { Level::WARNING ,  'W' },
        { Level::DEBUG ,    'D' },
        { Level::TRACE ,    'T' } 
    };
    auto it = map.find( level );
    if ( it != map.end() ) {
        return it->second;
    }
    return '0';
};

}} // namespace clf::log

#endif /* H_CLF_C34E641A_6748_4294_8D7E_8E17E62CEC98 */
