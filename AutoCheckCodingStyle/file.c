
/*
 * @brief file functionality
 */
#include <stdio.h>
#include <malloc.h>
#include <stdint.h>
#include <stdbool.h>
#include "file.h"


/*******************************************************************************
 * Definitions
 ******************************************************************************/

const char *FILE_TEXT_MODE[] = { "r", "w", "a", "r+", "w+", "a+" };
const char *FILE_BINARY_MODE[] = { "rb", "wb", "ab", "rb+", "r+b", "wb+", "w+b", "ab+", "a+b" };


/*******************************************************************************
 * API
 ******************************************************************************/

ng_global_status_code_t NG_FILE_Open(char *fileName, ng_file_text_mode_t mode, FILE *out)
{
    const char *file_mode = FILE_TEXT_MODE[mode];
    FILE *file = fopen(fileName, file_mode);

    if (!file)
        return kNgGlobalStatusError;
    else
    {
        out = file;
        return kNgGlobalStatusSuccess;
    }
}

ng_global_status_code_t NG_FILE_Read(char *fileName, FILE *out)
{
    FILE *file = (FILE *)malloc(sizeof(FILE *));
    if (kNgGlobalStatusError == NG_FILE_Open(fileName, kNgFileReadFromBeginning, file))
    {
        return kNgGlobalStatusError;
    }
    else
    {
        out = file;
        return kNgGlobalStatusSuccess;
    }
}

ng_global_status_code_t NG_FILE_Create(char *fileName, FILE *out)
{
    FILE *file = (FILE *) malloc(sizeof(FILE*));
    if (kNgGlobalStatusError == NG_FILE_Open(fileName, kNgFileWriteFromBeginning, file))
    {
        return kNgGlobalStatusError;
    }
    else
    {
        out = file;
        return kNgGlobalStatusSuccess;
    }
}

ng_global_status_code_t NG_FILE_Close(FILE *input)
{
    if (!input)
    {
        fclose(input);
        return kNgGlobalStatusSuccess;
    }
    else
        return kNgGlobalStatusError;
}



/* END OF FILE */
