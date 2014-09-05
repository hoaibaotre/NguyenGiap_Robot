
#ifndef __DRAW_H__
#define __DRAW_H__

/*
 * @brief draw functionality ex draw string, draw line, draw block, draw detail info
 */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "global.h"


/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define NG_DRAW_LINE_SIZE_LIMIT (100U)

const char NG_DRAW_SYMBOL[];

typedef enum _ng_draw_character_extension
{
    kNgDrawDash       = 0,          /* -- */
    kNgDrawSemicolons = 1,          /* ; */
    kNgDrawComma      = 2,          /* , */
    kNgDrawDot        = 3,          /* . */
    kNgDrawHyphen     = 4,          /* - */
    kNgDrawSlash      = 5,          /* / */
    kNgDrawBackSlash  = 6,          /* \ */
    kNgDrawUnderScore = 7,          /* _ __*/
    kNgDrawStar       = 8,          /* * */
} ng_draw_character_extension_t, *ng_draw_character_extension_ptr;

/*******************************************************************************
 * API
 ******************************************************************************/

/**
 * @brief draw one line with prefix, subfix of string by identity character
 * @details [long description]
 *
 * @param sourceString string will be display or title
 * @param mode identity character
 *
 * @return string after concatenate
 */
ng_global_status_code_t NG_DRAW_String(char *source, ng_draw_character_extension_t mode, char **out);
/**
 * @brief draw one line with identity character
 * @details [long description]
 *
 * @param mode identity character
 *
 * @return string after concatenate
 */
ng_global_status_code_t NG_DRAW_Line(ng_draw_character_extension_t mode, char **out);
/**
 * @brief draw one block of string that has source string in center and border will be decorate
 *  by identity character
 * @details [long description]
 *
 * @param sourceString string will be display or title
 * @param mode identity character
 *
 * @return string after concatenate
 */
ng_global_status_code_t NG_DRAW_Block(char *sourceString, ng_draw_character_extension_t mode, char **out);
/**
 * @brief draw one line of string that include detail system information such as dd-MM-yyyy hh:mm:ss + source string
 * @details [long description]
 *
 * @param sourceString string will be display
 * @return string after concatenate
 */
ng_global_status_code_t NG_DRAW_DetailInfo(char *sourceString, char **out);









#endif      /* __DRAW_H__ */

/* END OF FILE */
