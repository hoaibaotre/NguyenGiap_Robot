
/*
 * @brief
 */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "draw.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define NG_DRAW_LINE_LENGTH (100U)
#define EOS                 '\0'
#define EOL                 '\n'

const char NG_DRAW_SYMBOL[] = { '-', ';', ',', '.', '-', '/', '\\', '_', '*' };
/*******************************************************************************
 * API
 ******************************************************************************/

ng_global_status_code_t NG_DRAW_Line(ng_draw_character_extension_t mode, char **out)
{
    char template[NG_DRAW_LINE_LENGTH + 2];
    memset(template, NG_DRAW_SYMBOL[mode], NG_DRAW_LINE_LENGTH);
    template[NG_DRAW_LINE_LENGTH] = EOL;
    template[NG_DRAW_LINE_LENGTH + 1] = EOS;

    *out = template;

    return kNgGlobalStatusSuccess;
}

ng_global_status_code_t NG_DRAW_String(char *source, ng_draw_character_extension_t mode, char **out)
{
    uint32_t length = strlen(source);
    if (length >= NG_DRAW_LINE_LENGTH
        || strchr(source, EOL) != NULL)
        return kNgGlobalStatusSuccess;
    else
    {
        char template[NG_DRAW_LINE_LENGTH + 2];
        length = (NG_DRAW_LINE_LENGTH - length) / 2;
        memset(&template, NG_DRAW_SYMBOL[mode], length);
        memcpy(&template[length], source, strlen(source));
        length = NG_DRAW_LINE_LENGTH - length - strlen(source);
        memset(&template[NG_DRAW_LINE_LENGTH - length], NG_DRAW_SYMBOL[mode], length);
        template[NG_DRAW_LINE_LENGTH] = EOL;
        template[NG_DRAW_LINE_LENGTH + 1] = EOS;

        *out = template;
    }

    return kNgGlobalStatusSuccess;
}

ng_global_status_code_t NG_DRAW_Block(char *sourceString, ng_draw_character_extension_t mode, char **out)
{

    return kNgGlobalStatusError;
}

ng_global_status_code_t NG_DRAW_DetailInfo(char *sourceString, char **out)
{
    return kNgGlobalStatusError;
}








/* END OF FILE */
