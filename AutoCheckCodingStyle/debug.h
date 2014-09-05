
#ifndef __DEBUG_H__
#define __DEBUG_H__

/*
 * @brief debug functionality
 */

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "global.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

uint32_t g_ng_debug_mode;

typedef enum _ng_debug_mode
{
    kInfo    = 0,
    kWarning = 1,
    kDebug   = 2,
    kError   = 3,
    kFatal   = 4
} ng_debug_mode_t, *ng_debug_mode_ptr;

typedef enum _ng_debug_echo_mode
{
    kConsoleMode = 0,
    kFileMode    = 1
} ng_debug_echo_mode_t, *ng_debug_echo_mode_ptr;

#if g_ng_debug_mode == kInfo
    #define NG_DEBUG_INFO(stmt,...)         fprintf(stderr, "INFO: " stmt "\n", ##__VA_ARGS__)
    #define NG_DEBUG_WARNING(stmt,...)      fprintf(stderr, "WARNING: " stmt "\n", ##__VA_ARGS__)
    #define NG_DEBUG_DEBUG(stmt,...)        fprintf(stderr, "DEBUG: " stmt "\n", ##__VA_ARGS__)
    #define NG_DEBUG_ERROR(stmt,...)        fprintf(stderr, "ERROR: " stmt "\n", ##__VA_ARGS__)
    #define NG_DEBUG_FATAL(stmt,...)        fprintf(stderr, "FATAL: " stmt "\n", ##__VA_ARGS__)
#elif g_ng_debug_mode == kWarning
    #define NG_DEBUG_INFO(stmt,...)
    #define NG_DEBUG_WARNING(stmt,...)      fprintf(stderr, "WARNING: " stmt "\n", ##__VA_ARGS__)
    #define NG_DEBUG_DEBUG(stmt,...)        fprintf(stderr, "DEBUG: " stmt "\n", ##__VA_ARGS__)
    #define NG_DEBUG_ERROR(stmt,...)        fprintf(stderr, "ERROR: " stmt "\n", ##__VA_ARGS__)
    #define NG_DEBUG_FATAL(stmt,...)        fprintf(stderr, "FATAL: " stmt "\n", ##__VA_ARGS__)
#elif g_ng_debug_mode == kDebug
    #define NG_DEBUG_INFO(stmt,...)
    #define NG_DEBUG_WARNING(stmt,...)
    #define NG_DEBUG_DEBUG(stmt,...)        fprintf(stderr, "DEBUG: " stmt "\n", ##__VA_ARGS__)
    #define NG_DEBUG_ERROR(stmt,...)        fprintf(stderr, "ERROR: " stmt "\n", ##__VA_ARGS__)
    #define NG_DEBUG_FATAL(stmt,...)        fprintf(stderr, "FATAL: " stmt "\n", ##__VA_ARGS__)
#elif g_ng_debug_mode == kError
    #define NG_DEBUG_INFO(stmt,...)
    #define NG_DEBUG_WARNING(stmt,...)
    #define NG_DEBUG_DEBUG(stmt,...)
    #define NG_DEBUG_ERROR(stmt,...)        fprintf(stderr, "ERROR: " stmt "\n", ##__VA_ARGS__)
    #define NG_DEBUG_FATAL(stmt,...)        fprintf(stderr, "FATAL: " stmt "\n", ##__VA_ARGS__)
#elif g_ng_debug_mode = kFatal
    #define NG_DEBUG_INFO(stmt,...)
    #define NG_DEBUG_WARNING(stmt,...)
    #define NG_DEBUG_DEBUG(stmt,...)
    #define NG_DEBUG_ERROR(stmt,...)
    #define NG_DEBUG_FATAL(stmt,...)        fprintf(stderr, "FATAL: " stmt "\n", ##__VA_ARGS__)
#else
    #define NG_DEBUG_INFO(stmt,...)
    #define NG_DEBUG_WARNING(stmt,...)
    #define NG_DEBUG_DEBUG(stmt,...)
    #define NG_DEBUG_ERROR(stmt,...)
    #define NG_DEBUG_FATAL(stmt,...)
#endif

/*******************************************************************************
 * API
 ******************************************************************************/
#ifdef NDEBUG
    #define NG_DEBUG_Debug_Info(M, ...)
#else
    #define NG_DEBUG_Debug_Info(M, ...)     fprintf(stderr, "DEBUG %s:%d: " M "\n",    \
        __FILE__, __LINE__, ##__VA_ARGS__)
#endif

#define NG_DEBUG_Clean_Errno()               (errno == 0 ? "None" : strerror(errno))

#define NG_DEBUG_Log_Err(M, ...)             fprintf(stderr, "[ERROR] (%s:%d: errno: %s) " M "\n",    \
    __FILE__, __LINE__, NG_DEBUG_Clean_Errno(), ##__VA_ARGS__)

#define NG_DEBUG_Log_Warn(M, ...)            fprintf(stderr, "[WARN] (%s:%d: errno: %s) " M "\n",    \
    __FILE__, __LINE__, NG_DEBUG_Clean_Errno(), ##__VA_ARGS__)

#define NG_DEBUG_Log_Info(M, ...)            fprintf(stderr, "[INFO] (%s:%d) " M "\n",    \
    __FILE__, __LINE__, ##__VA_ARGS__)

#define NG_DEBUG_Check(A, M, ...)            if(!(A)) { NG_DEBUG_Log_Err(M, ##__VA_ARGS__); errno=0; goto error; }

#define NG_DEBUG_Sentinel(M, ...)            { NG_DEBUG_Log_Err(M, ##__VA_ARGS__); errno=0; goto error; }

#define NG_DEBUG_Check_Mem(A)                NG_DEBUG_Check((A), "Out of memory.")

#define NG_DEBUG_Check_Debug(A, M, ...)      if(!(A)) { NG_DEBUG_Debug_Info(M, ##__VA_ARGS__); errno=0; goto error; }

/**
 * @brief dump information into log file or terminal
 * @details [long description]
 *
 * @param string information will be logged
 * @return execution status
 */
ng_global_status_code_t NG_DEBUG_Dump(char *string);

//ng_global_status_code_t NG_DEBUG_Print(ng_parser_arg_cmd_t parserArgCmd/*, ng_debug_echo_mode_t mode*/);

#endif      /* __DEBUG_H__ */

/* END OF FILE */
