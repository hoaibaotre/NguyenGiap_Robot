#include <stdio.h>
#include <stdint.h>
#include "global.h"
#include "utility.h"
#include "draw.h"
#include "parser.h"
#include "file.h"
#include "folder.h"
#include "property_menu_context.h"
#include "test.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define NG_DEBUG_MODE                   (1U)
#define NG_TEST_MODE                    (1U)
#define NG_PARSER_TOKEN_STRING_MAX_SIZE (256)

ng_parser_arg_cmd_t g_parserArgCmd = {
    .isRecursive      = false,
    .fileNameInput    = "",
    .pathFolderInput  = "",
    .fileNameOutput   = "",
    .pathFolderOutput = "",
    .debugMode        = kDebug
};

char g_tokenString[NG_PARSER_TOKEN_STRING_MAX_SIZE];
ng_parser_tree_token_node_t *g_rootTokenNode, *g_currentTokenNode;
ng_parser_tree_scope_node_t *g_rootScopeNode, *g_currentScopeNode;
/*******************************************************************************
 * API
 ******************************************************************************/

/**
 * @brief NguyenGiap robot will auto explorer all file *.c, *.h (recursive in specify folder) and
 *  take note all point that didn't follow yet by Freescale coding style. This tool will save our
 *  time and your money, so that we focus completely into the innovation on JOB.
 *  It's pretty tool for lazy man.
 *
 * @details [long description]
 * @return int - exit code when program executes
 */
uint32_t main(uint32_t argc, char **argv)
{
#if NG_TEST_MODE

    ng_test_result_t result;
    NG_TEST_Result_Init(&result);
    NG_TEST_All(argc, argv, &result);

    return EXIT_OK;
#else
    /* Parser input argument to get variables & startup mode */
    NG_PARSER_Analysis_Argument_Cmd(argc, argv);

    /* Display start message */

    while (true)
    {
        /* 1. Explorer each file & folder */

        /* 2. Build syntax tree & dictionary */
        /* Initial root node */
        NG_PARSER_Initial_Token_Node(g_rootTokenNode);
        NG_PARSER_Initial_Scope_Node(g_rootScopeNode);


        /* 3. Get list of coding style for Freescale */

        /* 4. Explorer tree & dump incompatible coding style with Freescale */
    }

    /* Display end message */

    return  EXIT_OK;
#endif
}

/* END OF FILE */
