
#ifndef __UTILITY_H__
#define __UTILITY_H__

/*
 * @brief Utility functionality
 */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "global.h"


/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define STRING_CONCAT(str1,str2)        memcpy((str2) + strlen((str2)), (str1), strlen((str1)))

/*******************************************************************************
 * API
 ******************************************************************************/

//ng_global_status_code_t NG_UTILITY_String_Concatenate(const char *src, char *dest, )










#endif      /* __UTILITY_H__ */

/* END OF FILE */
