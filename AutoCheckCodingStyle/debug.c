
/*
 * @brief debug functionality
 */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "debug.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

uint32_t g_ng_debug_mode = kInfo;



/*******************************************************************************
 * API
 ******************************************************************************/

ng_global_status_code_t NG_DEBUG_Dump(char *string)
{
    return kNgGlobalStatusError;
}

 //ng_global_status_code_t NG_DEBUG_Print(ng_parser_arg_cmd_t parserArgCmd/*, ng_debug_echo_mode_t mode*/)
 //{
 //    return kNgGlobalStatusError;
 //}








/* END OF FILE */
