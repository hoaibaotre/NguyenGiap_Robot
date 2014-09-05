
/*
 * @brief Testing for NguyenGiap robot
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "global.h"
#include "utility.h"
#include "test.h"
#include "debug.h"
#include "draw.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define TEST_RESULT_INIT    {\
                                .ngTestCountNotImplement  = 0,\
                                .ngTestCountFailure       = 0,\
                                .ngTestCountSuccess       = 0,\
                                .ngTestCountInvalid       = 0,\
                            }
ng_test_result_t g_ngTestTotalResult = TEST_RESULT_INIT;

/*******************************************************************************
 * API
 ******************************************************************************/

ng_global_status_code_t NG_TEST_Result_Init(ng_test_result_t *out)
{
    ng_test_result_t ngTestResutlInit = TEST_RESULT_INIT;
    *out = ngTestResutlInit;

    return kNgGlobalStatusSuccess;
}

ng_global_status_code_t NG_TEST_Total_Result_Update(ng_test_result_t *addResult)
{
    g_ngTestTotalResult.ngTestCountNotImplement += addResult->ngTestCountNotImplement;
    STRING_CONCAT(addResult->ngTestResultNotImplement, g_ngTestTotalResult.ngTestResultNotImplement);
    g_ngTestTotalResult.ngTestCountFailure += addResult->ngTestCountFailure;
    STRING_CONCAT(addResult->ngTestResultFailure, g_ngTestTotalResult.ngTestResultFailure);
    g_ngTestTotalResult.ngTestCountSuccess += addResult->ngTestCountSuccess;
    STRING_CONCAT(addResult->ngTestResultSuccess, g_ngTestTotalResult.ngTestResultSuccess);
    g_ngTestTotalResult.ngTestCountInvalid += addResult->ngTestCountInvalid;
    STRING_CONCAT(addResult->ngTestResultInvalid, g_ngTestTotalResult.ngTestResultInvalid);

    return kNgGlobalStatusSuccess;
}

ng_global_status_code_t NG_TEST_Result_Add(ng_test_result_t *srcResult, ng_test_result_t *destResult)
{
    destResult->ngTestCountNotImplement += srcResult->ngTestCountNotImplement;
    STRING_CONCAT(srcResult->ngTestResultNotImplement, destResult->ngTestResultNotImplement);
    destResult->ngTestCountFailure += srcResult->ngTestCountFailure;
    STRING_CONCAT(srcResult->ngTestResultFailure, destResult->ngTestResultFailure);
    destResult->ngTestCountSuccess += srcResult->ngTestCountSuccess;
    STRING_CONCAT(srcResult->ngTestResultSuccess, destResult->ngTestResultSuccess);
    destResult->ngTestCountInvalid += srcResult->ngTestCountInvalid;
    STRING_CONCAT(srcResult->ngTestResultInvalid, destResult->ngTestResultInvalid);

    return kNgGlobalStatusSuccess;
}

ng_global_status_code_t NG_TEST_Total_Result_Show()
{
    char *displayString[] = {""};
    NG_DRAW_Line(kNgDrawStar, displayString);
    NG_DEBUG_INFO(" %s abc \n", &(displayString[0]));

    NG_DEBUG_INFO("Total Result: \n");

    NG_DEBUG_INFO("Test count not implement: %d \n Test name not implement: %s \n",
        g_ngTestTotalResult.ngTestCountNotImplement, g_ngTestTotalResult.ngTestResultNotImplement);
    NG_DEBUG_INFO("Test count failure: %d \n Test name failure: %s \n",
        g_ngTestTotalResult.ngTestCountFailure, g_ngTestTotalResult.ngTestResultFailure);
    NG_DEBUG_INFO("Test count success: %d \n Test name success: %s \n",
        g_ngTestTotalResult.ngTestCountSuccess, g_ngTestTotalResult.ngTestResultSuccess);
    NG_DEBUG_INFO("Test count invalid: %d \n Test name invalid: %s \n",
        g_ngTestTotalResult.ngTestCountInvalid, g_ngTestTotalResult.ngTestResultInvalid);

	NG_DEBUG_INFO("%s\n", displayString[0]);

	return kNgGlobalStatusSuccess;
}

ng_global_status_code_t NG_TEST_Result_Show(ng_test_result_t *ngTestResult)
{
    char *displayString[] = {""};
    NG_DRAW_Line(kNgDrawStar, displayString);
	NG_DEBUG_INFO("%s\n", *displayString);

    NG_DEBUG_INFO("Detail Result: \n");

    NG_DEBUG_INFO("Test count not implement: %d \n Test name not implement: %s \n",
        ngTestResult->ngTestCountNotImplement, ngTestResult->ngTestResultNotImplement);
    NG_DEBUG_INFO("Test count failure: %d \n Test name failure: %s \n",
        ngTestResult->ngTestCountFailure, ngTestResult->ngTestResultFailure);
    NG_DEBUG_INFO("Test count success: %d \n Test name success: %s \n",
        ngTestResult->ngTestCountSuccess, ngTestResult->ngTestResultSuccess);
    NG_DEBUG_INFO("Test count invalid: %d \n Test name invalid: %s \n",
        ngTestResult->ngTestCountInvalid, ngTestResult->ngTestResultInvalid);

	NG_DEBUG_INFO("%s\n", *displayString);

	return kNgGlobalStatusSuccess;
}


void NG_TEST_Debug_Debug()
{
    // notice you don't need the \n
    NG_DEBUG_Debug_Info("I have Brown Hair.");

    // passing in arguments like printf
    NG_DEBUG_Debug_Info("I am %d years old.", 37);
}

void NG_TEST_Debug_Log_Err()
{
    NG_DEBUG_Log_Err("I believe everything is broken.");
    NG_DEBUG_Log_Err("There are %d problems in %s.", 0, "space");
}

void NG_TEST_Debug_Log_Warn()
{
    NG_DEBUG_Log_Warn("You can safely ignore this.");
    NG_DEBUG_Log_Warn("Maybe consider looking at: %s.", "/etc/passwd");
}

void NG_TEST_Debug_Log_Info()
{
    NG_DEBUG_Log_Info("Well I did something mundane.");
    NG_DEBUG_Log_Info("It happened %f times today.", 1.3f);
}

int NG_TEST_Debug_Check(char *file_name)
{
    FILE *input = NULL;
    char *block = NULL;

    block = malloc(100);
    NG_DEBUG_Check_Mem(block); // should work

    input = fopen(file_name, "r");
    NG_DEBUG_Check(input, "Failed to open %s.", file_name);

    free(block);
    fclose(input);
    return 0;

error:
    if (block) free(block);
    if (input) fclose(input);
    return -1;
}

int NG_TEST_Debug_Check_Mem()
{
    char *test = NULL;
    NG_DEBUG_Check_Mem(test);

    free(test);
    return 1;

error:
    return -1;
}

int NG_TEST_Debug_Check_Sentinel(int code)
{
    char *temp = malloc(100);
    NG_TEST_Debug_Check_Mem(temp);

    switch (code) {
    case 1:
        NG_DEBUG_Log_Info("It worked.");
        break;
    default:
        NG_DEBUG_Sentinel("I shouldn't run.");
    }

    free(temp);
    return 0;

error:
    if (temp) free(temp);
    return -1;
}

int NG_TEST_Debug_Check_Debug()
{
    int i = 0;
    NG_DEBUG_Check_Debug(i != 0, "Oops, I was 0.");

    return 0;
error:
    return -1;
}

ng_global_status_code_t NG_TEST_Global(ng_test_result_t *result)
{
    NG_DEBUG_Debug_Info("===Start Draw Testing===\n");

    NG_TEST_Result_Init(result);

    return kNgGlobalStatusError;
}

ng_global_status_code_t NG_TEST_File(ng_test_result_t *result)
{
    NG_TEST_Result_Init(result);

    return kNgGlobalStatusError;
}

ng_global_status_code_t NG_TEST_Folder(ng_test_result_t *result)
{
    NG_TEST_Result_Init(result);

    return kNgGlobalStatusError;
}

ng_global_status_code_t NG_TEST_Parser(ng_test_result_t *result)
{
    NG_TEST_Result_Init(result);

    return kNgGlobalStatusError;
}

ng_global_status_code_t NG_TEST_Debug(uint32_t argc, char **argv, ng_test_result_t *result)
{
    NG_TEST_Result_Init(result);
    NG_DEBUG_Check(argc == 2, "Need an argument.");

    NG_TEST_Debug_Debug();
    NG_TEST_Debug_Log_Err();
    NG_TEST_Debug_Log_Warn();
    NG_TEST_Debug_Log_Info();

    NG_DEBUG_Check(NG_TEST_Debug_Check("ex20.c") == 0, "failed with ex20.c");
    NG_DEBUG_Check(NG_TEST_Debug_Check(argv[1]) == -1, "failed with argv");
    NG_DEBUG_Check(NG_TEST_Debug_Check_Sentinel(1) == 0, "test_sentinel failed.");
    NG_DEBUG_Check(NG_TEST_Debug_Check_Sentinel(100) == -1, "test_sentinel failed.");
    NG_DEBUG_Check(NG_TEST_Debug_Check_Mem() == -1, "test_check_mem failed.");
    NG_DEBUG_Check(NG_TEST_Debug_Check_Debug() == -1, "test_check_debug failed.");

    return kNgGlobalStatusSuccess;

error:
    return kNgGlobalStatusError;
}

ng_global_status_code_t NG_TEST_Draw(ng_test_result_t *result)
{
    bool flag = false;
    NG_DEBUG_Debug_Info("===Start Draw Testing===\n");

    if (kNgGlobalStatusSuccess == NG_TEST_Result_Init(result))
    {
        NG_DEBUG_Debug_Info("Test Initial OK!\n");

        //ng_global_status_code_t NG_DRAW_Line(ng_draw_character_extension_t mode, char* out);
        char *expectedLine = "****************************************************************************************************\n";
        char *input[] = {""};
        if (kNgGlobalStatusSuccess == NG_DRAW_Line(kNgDrawStar, input))
        {
            if (0 != strcmp(expectedLine, *input))
            {
                NG_DEBUG_Debug_Info("Result value is not same expected value.\n");
                result->ngTestCountFailure++;
                STRING_CONCAT("NG_DRAW_Line,", result->ngTestResultFailure);
                flag = false;
            }
            else
            {
                NG_DEBUG_Debug_Info("Result value is same expected value.\n");
                result->ngTestCountSuccess++;
                STRING_CONCAT("NG_DRAW_Line,", result->ngTestResultSuccess);
                flag = true;
            }
        }
        else
        {
            NG_DEBUG_Debug_Info("Result Failure.\n");
            result->ngTestCountFailure++;
            STRING_CONCAT("NG_DRAW_Line,", result->ngTestResultFailure);
            flag = false;
        }

        expectedLine = "**********12345678901234567890123456789012345678901234567890123456789012345678901234567890**********\n";
        if (kNgGlobalStatusSuccess ==
            NG_DRAW_String("12345678901234567890123456789012345678901234567890123456789012345678901234567890", kNgDrawStar, input))
        {
            if (0 != strcmp(expectedLine, *input))
            {
                NG_DEBUG_Debug_Info("Result value is not same expected value.\n");
                result->ngTestCountFailure++;
                STRING_CONCAT("NG_DRAW_String,", result->ngTestResultFailure);
                flag = false;
            }
            else
            {
                NG_DEBUG_Debug_Info("Result value is same expected value.\n");
                result->ngTestCountSuccess++;
                STRING_CONCAT("NG_DRAW_String,", result->ngTestResultSuccess);
                flag = true;
            }
        }
        else
        {
            NG_DEBUG_Debug_Info("Result Failure.\n");
            result->ngTestCountFailure++;
            STRING_CONCAT("NG_DRAW_String,", result->ngTestResultFailure);
            flag = false;
        }
    }
    else
    {
        NG_DEBUG_Debug_Info("Test Initial Failure!\n");
        result->ngTestCountInvalid++;
        STRING_CONCAT("NG_DRAW,", result->ngTestResultInvalid);
        flag = false;
    }
    NG_DEBUG_Debug_Info("===End Draw Testing===\n");

    /* Update total result */
    NG_TEST_Total_Result_Update(result);
    return flag ? kNgGlobalStatusSuccess : kNgGlobalStatusError;
}

ng_global_status_code_t NG_TEST_Property_Menu_Context(ng_test_result_t *result)
{
    NG_TEST_Result_Init(result);

    return kNgGlobalStatusError;
}

ng_global_status_code_t NG_TEST_Tree(ng_test_result_t *result)
{
    NG_TEST_Result_Init(result);

    return kNgGlobalStatusError;
}

ng_global_status_code_t NG_TEST_Utility(ng_test_result_t *result)
{
    NG_TEST_Result_Init(result);

    return kNgGlobalStatusError;
}

ng_global_status_code_t NG_TEST_Scan(ng_test_result_t *result)
{
    NG_TEST_Result_Init(result);

    return kNgGlobalStatusError;
}

ng_global_status_code_t NG_TEST_All(uint32_t argc, char **argv, ng_test_result_t *result)
{
    NG_TEST_Result_Init(result);

    NG_TEST_Global(result);
    NG_TEST_File(result);
    NG_TEST_Folder(result);
    NG_TEST_Parser(result);
    NG_TEST_Debug(argc, argv, result);
    NG_TEST_Draw(result);
    NG_TEST_Property_Menu_Context(result);
    NG_TEST_Tree(result);
    NG_TEST_Utility(result);
    NG_TEST_Scan(result);

    NG_TEST_Total_Result_Show();

    return kNgGlobalStatusSuccess;
}


/*******************************************************************************
 * DEBUG: Zed's Awesome Debug Macros
 ******************************************************************************/

/*******************************************************************************
 * ANOTHER
 ******************************************************************************/


/* END OF FILE */
