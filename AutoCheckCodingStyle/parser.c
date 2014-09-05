
/*
 * @brief Parser functionality
 */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "parser.h"
#include "scan.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define MAX_TOKEN_STRING_LENGTH 100
#define NG_PARSER_TOKEN_STRING_RESET memset(ng_parser_token_string, 0x00, MAX_TOKEN_STRING_LENGTH)

#define NG_PARSER_TOKEN_DEFAULT_1(node)     \
    node->childTokenLv1  = NULL; \
    node->declareToken   = node;  \
    node->colStartNumber = currentLinePosition + token_pos_col_start;   \
    node->colEndNumber   = currentLinePosition + token_pos_col_start + length(token_current); \
    node->rowStartNumber = currentLine; \
    node->rowEndNumber   = currentLine;   \
    // node->name           = token_current; \
    node->scope          = NULL; \
    node->varType        = NULL;   \
    node->funcType       = NULL;  \
    node->expType        = NULL;   \
    currentNode          = node;    \
    memcpy(node->name, &token_current, length(token_current));

const char EOS = '\0';
const char EOL_UNIX = '\n';
const char *EOL_WINDOW = {'\n', '\r'};

const char *TOKEN_COMMENT = {"//", "/*", "*/"};
const char *TOKEN_PREPROCESSOR[] = {
    "#define", "#include", "#undef", "#ifdef", "#ifndef",
    "#if", "#else", "#elif", "#endif",
    "#error", "#pragma",
    "__DATE__", "__TIME__", "__FILE__", "__LINE__",
    "stdc()", "continuant()", "stringize()", "tokenpasting()", "define()"
};
const char *TOKEN_PRIMITIVE[] = {
    "void", "bool", "char", "signed char", "unsigned char",
    "short", "signed short", "unsigned short",
    "int", "signed int", "unsigned int",
    "long", "signed long", "unsigned long",
    "int8_t", "uint8_t", "int16_t", "uint16_t", "int32_t", "uint32_t", "int64_t", "uint64_t",
    "float", "double", "long double"
};
const char *TOKEN_KEYWORD[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do", "double",
    "else", "enum", "extern", "float", "for", "goto", "if", "int", "long",
    "register", "return", "short", "signed", "sizeof", "static", "struct", "switch",
    "typedef", "union", "unsigned", "void", "volatile", "while", "packed"
};
const char *TOKEN_ARITHMETIC[] = {
    "+", "-", "*", "/", "%", "++", "--"
};
const char *TOKEN_RELATIONAL[] = {
    "<", ">", "!=", "<=", ">=", "=="
};
const char *TOKEN_LOGICAL[] = {
    "&&", "||", "XOR", "~", "<<", ">>"
};
const char *TOKEN_BITWISE[] = {
    "=", "+=", "-=", "*=", "/=", "%=", "&=", "|=", "^=", "~=", "<<=", ">>="
};
const char *TOKEN_PUNCTUATION[] = {
    "(", ")", "[", "]", "{", "}", "<", ">", ";", ",", "."
};


char ng_parser_token_string[MAX_TOKEN_STRING_LENGTH];
static char token_temporary[MAX_TOKEN_STRING_LENGTH + 1];
char *token_current;
uint8_t token_index, token_pos_row_start, token_pos_row_end, token_pos_col_start, token_pos_col_end;
uint32_t next_token_id;

ng_parser_tree_token_node_t parentNode, siblingNode, currentNode;
/*******************************************************************************
 * API
 ******************************************************************************/

static ng_global_status_code_t NG_PARSER_Copy_Token_Temporay()
{
    uint8_t index;
    while (index < token_index)
    {
        *token_temporary[index] = ng_parser_token_string[index];
    }
    *token_temporary[index] = EOS;
}

static ng_global_status_code_t NG_PARSER_Is_Token_Comment(ng_parser_tree_token_node_t *out)
{
    uint8_t t;

    NG_PARSER_Copy_Token_Temporay();

    if ((t = strstr(token_temporary, TOKEN_COMMENT[kNgParserCommentKindMultipleStart])) >= 0)
    {   /* /* TOKEN */
        token_pos_col_start = t;
        token_current = TOKEN_COMMENT[kNgParserCommentKindMultipleStart]);
    }
    else if ((t = strstr(token_temporary, TOKEN_COMMENT[kNgParserCommentKindMultipleEnd])) >= 0)
    {   /* \*\/ TOKEN */
        token_pos_col_start = t;
        token_current = TOKEN_COMMENT[kNgParserCommentKindMultipleEnd]);
    }
    else if ((t = strstr(token_temporary, TOKEN_COMMENT[kNgParserCommentKindSingle])) >= 0)
    {   /* // TOKEN */
        token_pos_col_start = t;
        token_current = TOKEN_COMMENT[kNgParserCommentKindSingle]);
    }
    else
        return kNgGlobalStatusError;

    ng_parser_tree_token_node_t *node;
    NG_PARSER_Initial_Token_Node(node);

    // node->parentToken =
    // node->prevToken =
    // node->siblingToken =
    NG_PARSER_TOKEN_DEFAULT_1(node);

    out = node;

    return kNgGlobalStatusSuccess;
}

static ng_global_status_code_t NG_PARSER_Is_Token_Preprocessor(ng_parser_tree_token_node_t *out)
{
    uint8_t t;

    NG_PARSER_Copy_Token_Temporay();

    if ((t = strstr(token_temporary, TOKEN_COMMENT[kNgParserCommentKindMultipleStart])) >= 0)
    {   /* /* TOKEN */
        token_pos_col_start = t;
        token_current = TOKEN_COMMENT[kNgParserCommentKindMultipleStart]);
    }
    else if ((t = strstr(token_temporary, TOKEN_COMMENT[kNgParserCommentKindMultipleEnd])) >= 0)
    {   /* \*\/ TOKEN */
        token_pos_col_start = t;
        token_current = TOKEN_COMMENT[kNgParserCommentKindMultipleEnd]);
    }else if ((t = strstr(token_temporary, TOKEN_COMMENT[kNgParserCommentKindSingle])) >= 0)
    {   /* // TOKEN */
        token_pos_col_start = t;
        token_current = TOKEN_COMMENT[kNgParserCommentKindSingle]);
    }
    else
        return kNgGlobalStatusError;

    ng_parser_tree_token_node_t *node;
    NG_PARSER_Initial_Token_Node(node);

    NG_PARSER_TOKEN_DEFAULT_1(node);

    out = node;

    return kNgGlobalStatusSuccess;
}

static ng_global_status_code_t NG_PARSER_Initial_Token_Node(ng_parser_tree_token_node_t *initialNode)
{
    ng_parser_tree_token_node_t blankNode;
    memset(&blankNode, 0x00, sizeof(ng_parser_tree_token_node_t));

    blankNode.tokenId = next_token_id++;
    initialNode = &blankNode;

    return kNgGlobalStatusSuccess;
}

ng_global_status_code_t NG_PARSER_Initial_Scope_Node(ng_parser_tree_scope_node_t *initialScope)
{
    ng_parser_tree_scope_node_t emptyScope;
    memset(&emptyScope, 0x00, sizeof(ng_parser_tree_scope_node_t));
    initialScope = &emptyScope;

    return kNgGlobalStatusSuccess;
}

ng_global_status_code_t NG_PARSER_Get_Next_Token(ng_parser_tree_token_node_t *out)
{
    char tok;
    NG_SCAN_Get_Next_Char(&tok);
    ng_parser_token_string[token_index++] = tok;
    if (tok == EOF)
        return kNgGlobalStatusSuccess;
    else
    {
        if (kNgGlobalStatusSuccess == NG_PARSER_Is_Token_Comment(out))
        {}
        else if (kNgGlobalStatusSuccess == NG_PARSER_Is_Token_Preprocessor(out))
        {}
        else
            return NG_PARSER_Get_Next_Token(out);
    }
}

/**
 * @brief Analysis input argument & fill out argument structure
 * @details [long description]
 *
 * @param argc number of argument
 * @param argv list of argument
 *
 * @return argument structure or otherwise return NULL
 */
ng_global_status_code_t NG_PARSER_Analysis_Argument_Cmd(uint32_t argc, const char **argv, ng_parser_arg_cmd_t *paserArgCmd)
{


    return kNgGlobalStatusError;
}

/* END OF FILE */
