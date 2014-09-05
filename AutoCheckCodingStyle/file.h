
#ifndef __FILE_H__
#define __FILE_H__

/*
 * @brief file functionality for create, delete, open, read, write, append, close
 */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "global.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

const char *FILE_TEXT_MODE[];
const char *FILE_BINARY_MODE[];

typedef enum _ng_file_text_mode
{
    kNgFileReadFromBeginning,
    kNgFileWriteFromBeginning,
    kNgFileAppendFromEnding,
    kNgFileReadPlusFromBeginning,
    kNgFileWritePlusFromBeginning,
    kNgFileAppendPlusFromBeginning
} ng_file_text_mode_t, *ng_file_text_mode_ptr;

typedef enum _ng_file_binary_mode
{
    kNgFileReadBinary,
    kNgFileWriteBinary,
    kNgFileAppendBinary
} ng_file_binary_mode_t, *ng_file_binary_mode_ptr;

typedef enum _ng_file_type
{
    CTYPE,
    HTYPE,
    NGTYPE
} ng_file_type_t, *ng_file_type_ptr;

typedef struct _ng_file_info
{
    char* fileName;
    char* pathFile;
    uint32_t sizeInByte;
    uint32_t numberOfLine;
    ng_file_type_t type;
} ng_file_info_t, *ng_file_info_ptr;


/*******************************************************************************
 * API
 ******************************************************************************/
/**
 * @brief Check existing file if any
 * @details [long description]
 *
 * @param file pointer to file for process
 * @return execution status
 */
ng_global_status_code_t NG_FILE_Is_Existing(const char* pathFolder, const char* fileName, const char* mode, FILE *file);

ng_global_status_code_t NG_FILE_Creating(const char* pathFolder, const char* fileName, FILE *file);

ng_global_status_code_t NG_FILE_Deleting(const char* pathFolder, const char* fileName);

ng_global_status_code_t NG_FILE_Renaming(const char* pathFolder, const char* fileName, const char* newFileName);

ng_global_status_code_t NG_FILE_Get_Next_Line(char* output, FILE *file);

ng_global_status_code_t NG_FILE_Get_Next_Character(char* output, FILE *file);

ng_global_status_code_t NG_FILE_Write_To_Begin(const char* input, FILE *file);

ng_global_status_code_t NG_FILE_Write_To_End(const char* input, FILE *file);

ng_global_status_code_t NG_FILE_Find_String(const char* input, char *output[], FILE *file);

ng_global_status_code_t NG_FILE_Get_Info(ng_file_info_t* output, FILE *file);

// fopen – opens a text file.
// fclose – closes a text file.
// feof – detects end-of-file marker in a file.
// fscanf – reads formatted input from a file.
// fprintf – prints formatted output to a file.
// fgets – reads a string from a file.
// fputs – prints a string to a file.
// fgetc – reads a character from a file.
// fputc – prints a character to a file.

#endif      /* __FILE_H__ */

/* END OF FILE */
