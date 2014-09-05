
#ifndef __GLOBAL_H__
#define __GLOBAL_H__

/*
 * @brief Global functionality
 */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>


/*******************************************************************************
 * Definitions
 ******************************************************************************/

FILE *currentFile;

uint32_t g_status_code;

uint32_t g_ng_debug_mode;

typedef enum _execute_code
{
    EXIT_ERROR = -1,
    EXIT_OK,
    EXIT_PENDING
} execute_code_t, *execute_code_ptr;

typedef enum _ng_global_status_code
{
    kNgGlobalStatusError   = 0,
    kNgGlobalStatusPending = 1,
    kNgGlobalStatusSuccess = 2
} ng_global_status_code_t, *ng_global_status_code_ptr;


/*******************************************************************************
 * API
 ******************************************************************************/








#endif      /* __GLOBAL_H__ */

/* END OF FILE */
