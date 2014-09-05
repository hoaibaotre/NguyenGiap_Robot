
#ifndef __PARSER_H__
#define __PARSER_H__

/*
 * @brief parsing functionality
 */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "global.h"
#include "debug.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

typedef struct _ng_parser_arg_cmd
{
    bool isRecursive;
    char *fileNameInput;
    char *pathFolderInput;
    char *fileNameOutput;
    char *pathFolderOutput;
    ng_debug_mode_t debugMode;
} ng_parser_arg_cmd_t, *ng_parser_arg_cmd_ptr;

typedef union _ng_parser_token_type
{
    char TODO;
} ng_parser_token_type_t, *ng_parser_token_type_ptr;

typedef enum _ng_parser_node_kind
{
    kNgParserDeclarement,
    kNgParserStatement,
    kNgParserExpression,
    kNgParserComment
} ng_parser_node_kind_t, *ng_parser_node_kind_ptr;

typedef enum _ng_parser_declarement_kind
{
    kNgParserDecKindPreprocessor,
    kNgParserDecKindFunction,
    kNgParserDecKindVariable
} ng_parser_declarement_kind_t, *ng_parser_declarement_kind_ptr;

typedef struct _ng_parser_expression_type
{
    char TODO;
} ng_parser_expression_type_t, *ng_parser_expression_type_ptr;

typedef enum _ng_parser_statement_kind
{
    kNgParserStateKindDecision,
    kNgParserStateKindLoop,
    kNgParserStateKindBranch,
    kNgParserStateKindCall,
    kNgParserStateKindCompound,
    kNgParserStateKindReturn
} ng_parser_statement_kind_t, *ng_parser_statement_kind_ptr;

typedef enum _ng_parser_expression_kind
{
    kNgParserExpKind0
} ng_parser_expression_kind_t, *ng_parser_expression_kind_ptr;

typedef enum _ng_parser_comment_kind
{
    kNgParserCommentKindSingle,
    kNgParserCommentKindMultipleStart,
    kNgParserCommentKindMultipleEnd
} ng_parser_comment_kind_t, *ng_parser_comment_kind_ptr;

typedef union _ng_parser_node_kind_detail
{
    ng_parser_declarement_kind_t dec;
    ng_parser_statement_kind_t stmt;
    ng_parser_expression_kind_t exp;
    ng_parser_comment_kind_t cmt;
} ng_parser_node_kind_detail_t, *ng_parser_node_kind_detail_ptr;

typedef enum _ng_parser_declare_preprocessor
{
    kNgParserDecPrepDefine,
    kNgParserDecPrepInclude,
    kNgParserDecPrepUndef,
    kNgParserDecPrepIfdef,
    kNgParserDecPrepIfndef,
    kNgParserDecPrepIf,
    kNgParserDecPrepElse,
    kNgParserDecPrepElif,
    kNgParserDecPrepEndif,
    kNgParserDecPrepError,
    kNgParserDecPrepPragma,
    kNgParserDecPrepDate,
    kNgParserDecPrepTime,
    kNgParserDecPrepFile,
    kNgParserDecPrepLine,
    kNgParserDecPrepStdc,
    kNgParserDecPrepContinuant,
    kNgParserDecPrepStringize,
    kNgParserDecPrepTokenPasting,
    kNgParserDecPrepDefinedOperator
} ng_parser_declare_preprocessor_t, *ng_parser_declare_preprocessor_ptr;

typedef enum _ng_parser_data_type_primitive
{
    kNgParserDataTypeVoid,
    kNgParserDataTypeBool,
    kNgParserDataTypeChar,
    kNgParserDataTypeSignedChar,
    kNgParserDataTypeUnsignedChar,
    kNgParserDataTypeShort,
    kNgParserDataTypeSignedShort,
    kNgParserDataTypeUnsignedShort,
    kNgParserDataTypeInt,
    kNgParserDataTypeSignedInt,
    kNgParserDataTypeUnsignedInt,
    kNgParserDataTypeLong,
    kNgParserDataTypeSignedLong,
    kNgParserDataTypeUnsignedLong,
    kNgParserDataTypeInt8,
    kNgParserDataTypeUint8,
    kNgParserDataTypeInt16,
    kNgParserDataTypeUint16,
    kNgParserDataTypeInt32,
    kNgParserDataTypeUInt32,
    kNgParserDataTypeInt64,
    kNgParserDataTypeUInt64,
    kNgParserDataTypeFloat,
    kNgParserDataTypeDouble,
    kNgParserDataTypeLongDouble,
} ng_parser_data_type_primitive_t, *ng_parser_data_type_primitive_ptr;

typedef enum _ng_parser_keyword
{
    kNgParserKeywordAuto,
    kNgParserKeywordBreak,
    kNgParserKeywordCase,
    kNgParserKeywordChar,
    kNgParserKeywordConst,
    kNgParserKeywordContinue,
    kNgParserKeywordDefault,
    kNgParserKeywordDo,
    kNgParserKeywordDouble,
    kNgParserKeywordElse,
    kNgParserKeywordEnum,
    kNgParserKeywordExtern,
    kNgParserKeywordFloat,
    kNgParserKeywordFor,
    kNgParserKeywordGoto,
    kNgParserKeywordIf,
    kNgParserKeywordInt,
    kNgParserKeywordLong,
    kNgParserKeywordRegister,
    kNgParserKeywordReturn,
    kNgParserKeywordShort,
    kNgParserKeywordSigned,
    kNgParserKeywordSizeof,
    kNgParserKeywordStatic,
    kNgParserKeywordStruct,
    kNgParserKeywordSwitch,
    kNgParserKeywordTypedef,
    kNgParserKeywordUnion,
    kNgParserKeywordUnsigned,
    kNgParserKeywordVoid,
    kNgParserKeywordVolatile,
    kNgParserKeywordWhile,
    kNgParserKeywordPacked
} ng_parser_keyword_t, *ng_parser_keyword_ptr;

typedef enum _ng_parser_symbol_type
{
    kNgParserSymbolTypeArithmetic,
    kNgParserSymbolTypeRelational,
    kNgParserSymbolTypeLogical,
    kNgParserSymbolTypeBitwise,
    kNgParserSymbolTypeAssignment,
    kNgParserSymbolTypeMisc
} ng_parser_symbol_type_t, *ng_parser_symbol_type_ptr;

typedef enum _ng_parser_symbol_arithmetic
{
    kNgParserSymbolArithmeticPlus,
    kNgParserSymbolArithmeticMinus,
    kNgParserSymbolArithmeticMul,
    kNgParserSymbolArithmeticDiv,
    kNgParserSymbolArithmeticMod,
    kNgParserSymbolArithmeticInc,
    kNgParserSymbolArithmeticDec,
} ng_parser_symbol_arithmetic_t, *ng_parser_symbol_arithmetic_ptr;

typedef enum _ng_parser_symbol_relational
{
    kNgParserSymbolRelationalLT,
    kNgParserSymbolRelationalGT,
    kNgParserSymbolRelationalNE,
    kNgParserSymbolRelationalLTE,
    kNgParserSymbolRelationalGTE,
    kNgParserSymbolRelationalEQ
} ng_parser_symbol_relational_t, *ng_parser_symbol_relational_ptr;

typedef enum _ng_parser_symbol_logical
{
    kNgParserSymbolLogicalAnd,
    kNgParserSymbolLogicalOr,
    kNgParserSymbolLogicalNot
} ng_parser_symbol_logical_t, *ng_parser_symbol_logical_ptr;

typedef enum _ng_parser_symbol_bitwise
{
    kNgParserSymbolBitwiseAnd,
    kNgParserSymbolBitwiseOr,
    kNgParserSymbolBitwiseXor,
    kNgParserSymbolBitwiseFlip,
    kNgParserSymbolBitwiseLShift,
    kNgParserSymbolBitwiseRShift
} ng_parser_symbol_bitwise_t, *ng_parser_symbol_bitwise_ptr;

typedef enum _ng_parser_symbol_assignment
{
    kNgParserSymbolAssignmentEQ,
    kNgParserSymbolAssignmentPlus,
    kNgParserSymbolAssignmentMinus,
    kNgParserSymbolAssignmentMul,
    kNgParserSymbolAssignmentDiv,
    kNgParserSymbolAssignmentMod,
    kNgParserSymbolAssignmentAnd,
    kNgParserSymbolAssignmentOr,
    kNgParserSymbolAssignmentXor,
    kNgParserSymbolAssignmentFlip,
    kNgParserSymbolAssignmentLShift,
    kNgParserSymbolAssignmentRShift
} ng_parser_symbol_assignment_t, *ng_parser_symbol_assignment_ptr;

typedef enum _ng_parser_symbol_misc
{
    kNgParserSymbolMiscCondition
} ng_parser_symbol_misc_t, *ng_parser_symbol_misc_ptr;

typedef enum _ng_parser_symbol_punctuation
{
    kNgParserSymbolPunctuationLParen,
    kNgParserSymbolPunctuationRParen,
    kNgParserSymbolPunctuationLSquare,
    kNgParserSymbolPunctuationRSquare,
    kNgParserSymbolPunctuationLBrace,
    kNgParserSymbolPunctuationRBrace,
    kNgParserSymbolPunctuationLChevron,
    kNgParserSymbolPunctuationRChevron,
    kNgParserSymbolPunctuationSemi,
    kNgParserSymbolPunctuationComma,
    kNgParserSymbolPunctuationDot
} ng_parser_symbol_punctuation_t, *ng_parser_symbol_punctuation_ptr;

typedef struct _ng_parser_variable_type
{
    bool isGlobal;
    bool isStatic;
    bool isFormal;
    bool isConst;
    bool isArray;
    bool isPointer;
    bool isPrimitive;
    uint32_t elementNo;
    ng_parser_data_type_primitive_t primitiveType;
} ng_parser_variable_type_t, *ng_parser_variable_type_ptr;

typedef struct _ng_parser_function_type
{
    bool isGlobal;
    bool isStatic;
    bool isInline;
    bool isPointer;
    /* parameter */
} ng_parser_function_type_t, *ng_parser_function_type_ptr;

typedef enum _ng_parser_tree_scope_type
{
    kParserScopeGlobal,
    kParserScopeLocal,
    kParserScopeFormal
} ng_parser_tree_scope_type_t, *ng_parser_tree_scope_type_ptr;

typedef struct _ng_parser_tree_scope_node
{
    ng_parser_tree_scope_type_t scopeType;
    struct _ng_parser_tree_scope_node *parenScope;
    struct _ng_parser_tree_scope_node **childScopeLv1;
} ng_parser_tree_scope_node_t, *ng_parser_tree_scope_node_ptr;

typedef struct _ng_parser_tree_token_node
{
    struct _ng_parser_tree_token_node *parentToken;
    struct _ng_parser_tree_token_node **childTokenLv1;
    struct _ng_parser_tree_token_node *prevToken;
    struct _ng_parser_tree_token_node *nextToken;
    struct _ng_parser_tree_token_node *declareToken;
    uint32_t rowStartNumber;
    uint32_t colStartNumber;
    uint32_t rowEndNumber;
    uint32_t colEndNumber;
    uint32_t tokenId;
    char *pathTokenId;   /* This field demonstrate relationship between parent nodes and child nodes base on path like this: /1/2/5/6/ */
    char name[MAX_TOKEN_STRING_LENGTH];
    ng_parser_tree_scope_node_t *scope;
    ng_parser_node_kind_t nodeKind;
    ng_parser_token_type_t tokenType;
    ng_parser_node_kind_detail_t nodeKindDetail;
    ng_parser_variable_type_t *varType;
    ng_parser_function_type_t *funcType;
    ng_parser_expression_type_t *expType;
} ng_parser_tree_token_node_t, *ng_parser_tree_token_node_ptr;

typedef union _ng_parser_token
{
    ng_parser_symbol_arithmetic_t token1;
    ng_parser_symbol_relational_t token2;
    ng_parser_symbol_logical_t token3;
    ng_parser_symbol_bitwise_t token4;
    ng_parser_symbol_assignment_t token5;
    ng_parser_symbol_punctuation_t token6;
    ng_parser_keyword_t token7;
    ng_parser_data_type_primitive_t token8;
    ng_parser_declare_preprocessor_t token9;
} ng_parser_token_t, *ng_parser_token_ptr;


/*******************************************************************************
 * API
 ******************************************************************************/

ng_global_status_code_t NG_PARSER_Analysis_Argument_Cmd(uint32_t argc, const char **argv, ng_parser_arg_cmd_t *paserArgCmd);

ng_global_status_code_t NG_PARSER_Initial_Token_Node(ng_parser_tree_token_node_t *initialNode);

ng_global_status_code_t NG_PARSER_Initial_Scope_Node(ng_parser_tree_scope_node_t *initialScope);






#endif      /* __PARSER_H__ */

/* END OF FILE */
