#pragma once

#include <stddef.h>

void uz_timestamp(char* stamp, size_t stamp_size);
const char* uz_filename(const char* filename);

#define UZ_FILENAME   uz_filename(__FILE__)
#define UZ_LOG_FORMAT "[%-s|%-s] [%-16s:%5u] (%s) "

#define uz_log(lvl, file, line, func, fmt, ...)                                \
  do {                                                                         \
    char timestamp[16];                                                        \
    uz_timestamp(timestamp, sizeof(timestamp));                                \
    (void)fprintf(stdout, UZ_LOG_FORMAT fmt "\n", lvl, timestamp, file, line,  \
                  func, ##__VA_ARGS__);                                        \
  } while (0)

#define uz_log_err(_fmt, ...)                                                  \
  uz_log("ERR", UZ_FILENAME, __LINE__, __FUNCTION__, _fmt, ##__VA_ARGS__)

#ifdef UZ_DEBUG_BUILD
#define uz_log_wrn(_fmt, ...)                                                  \
  uz_log("WRN", UZ_FILENAME, __LINE__, __FUNCTION__, _fmt, ##__VA_ARGS__)
#else
#define uz_log_wrn(...)                                                        \
  do {                                                                         \
  } while (0)
#endif

#ifdef UZ_DEBUG_BUILD
#define uz_log_dbg(_fmt, ...)                                                  \
  uz_log("DBG", UZ_FILENAME, __LINE__, __FUNCTION__, _fmt, ##__VA_ARGS__)
#else
#define uz_log_dbg(...)                                                        \
  do {                                                                         \
  } while (0)
#endif
