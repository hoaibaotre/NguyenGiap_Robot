
#ifndef __SCAN_H__
#define __SCAN_H__

/*
 * @brief Scan functionality
 */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "global.h"


/*******************************************************************************
 * Definitions
 ******************************************************************************/

uint32_t currentLine;
uint32_t currentLinePosition;
uint32_t currentLineSize;

/*******************************************************************************
 * API
 ******************************************************************************/

ng_global_status_code_t NG_SCAN_Get_Next_Char(char *c);






#endif      /* __SCAN_H__ */

/* END OF FILE */
