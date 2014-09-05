
/*
 * @brief Scan functionality
 */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "scan.h"


/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define NG_SCAN_BUFFER_MAX_LENGTH (256)

uint32_t currentLine;
uint32_t currentLinePosition;
uint32_t currentLineSize;
char bufferRead[NG_SCAN_BUFFER_MAX_LENGTH] = {'\0'};

/*******************************************************************************
 * API
 ******************************************************************************/

ng_global_status_code_t NG_SCAN_Get_Next_Char(char *c)
{
    if (currentFile == NULL)
        return kNgGlobalStatusError;
    else
    {
        currentLineSize = strlen(bufferRead);
        if (currentLinePosition == (currentLineSize - 1))
        {
            if (fgets(bufferRead, NG_SCAN_BUFFER_MAX_LENGTH, currentFile) == NULL)
            {
                currentLine = 0;
                *c = EOF;
                memset(bufferRead, 0x00, NG_SCAN_BUFFER_MAX_LENGTH);
            }
            else
            {
                currentLine++;
                *c = bufferRead[currentLinePosition];
            }
            currentLinePosition = 0;
        }
        else
        {
            *c = bufferRead[currentLinePosition++];
        }
        return kNgGlobalStatusSuccess;
    }
}










/* END OF FILE */
