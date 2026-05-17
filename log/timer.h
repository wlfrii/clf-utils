#ifndef H_WLF_ADD991E7_F0AD_44A0_91F1_EC4E0F347A61
#define H_WLF_ADD991E7_F0AD_44A0_91F1_EC4E0F347A61
#include <log/sr_log.h>

namespace vision {

constexpr char vision_module_name[]     = "vision";
constexpr char simulation_module_name[] = "simulation";

#define VISION_LOG_FATAL    SR_LOG_FATAL
#define VISION_LOG_ERROR    SR_LOG_ERROR
#define VISION_LOG_WARNING  SR_LOG_WARNING
#define VISION_LOG_NOTICE   SR_LOG_NOTICE
#define VISION_LOG_DEBUG    SR_LOG_DEBUG
#define VISION_LOG_TRACE    SR_LOG_TRACE

/** vision assert */
#define VISION_ASSERT(condition, msg, ...)                              \
    do {                                                                \
        if (!(condition)) {                                             \
            VISION_LOG_FATAL("Assertion failed: " msg,  ##__VA_ARGS__); \
            std::exit(EXIT_FAILURE);                                    \
        }                                                               \
    } while (0)

#define SIMU_LOG(level, _fmt_, ...) \
    do{ \
        spdlog::get(vision::simulation_module_name)->level( "{:08}] {}", \
            LOG_NS::LogUtility::getLogCount(), fmt::sprintf(_fmt_, ##__VA_ARGS__)); \
        LOG_NS::compileCheck(_fmt_, ##__VA_ARGS__); \
    }while(0)

#define SIMU_LOG_FATAL(fmt, ...)   SIMU_LOG(fatal, fmt, ##__VA_ARGS__)
#define SIMU_LOG_ERROR(fmt, ...)   SIMU_LOG(error, fmt, ##__VA_ARGS__)
#define SIMU_LOG_WARNING(fmt, ...) SIMU_LOG(warning, fmt, ##__VA_ARGS__)
#define SIMU_LOG_NOTICE(fmt, ...)  SIMU_LOG(notice, fmt, ##__VA_ARGS__)
#define SIMU_LOG_DEBUG(fmt, ...)   SIMU_LOG(debug, fmt, ##__VA_ARGS__)
#define SIMU_LOG_TRACE(fmt, ...)   SIMU_LOG(trace, fmt, ##__VA_ARGS__)

#define SIMU_ASSERT(condition, msg, ...)                                \
    do {                                                                \
        if (!(condition)) {                                             \
            SIMU_ASSERT("Assertion failed: " msg,  ##__VA_ARGS__);      \
            std::exit(EXIT_FAILURE);                                    \
        }                                                               \
    } while (0)

/**
 * @brief Initiliaze loger for given module.
 *
 * @param module_name The module name.
 */
void initModuleLog(const char* module_name = nullptr);

/**
 * @brief Change output log level
 * 
 * @param log_level The spdlog level.
 */
void changeVisionLogLevel(U8 log_level);

/**
 * @brief Change output log level
 * 
 * @param log_level The spdlog level.
 */
void changeSimulationLogLevel(U8 log_level);

}  // namespace vision
#endif /* H_WLF_ADD991E7_F0AD_44A0_91F1_EC4E0F347A61 */
