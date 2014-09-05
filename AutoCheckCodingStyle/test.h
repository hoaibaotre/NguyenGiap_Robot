
#ifndef __TEST_H__
#define __TEST_H__

/*
 * @brief Testing for NguyenGiap robot
 */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "global.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define MAX_ELEMENT (1000U)
typedef enum _ng_test_status_code
{
    kNgTestStatusNotImplement,
    kNgTestStatusFailure,
    kNgTestStatusSuccess,
    kNgTestStatusInvalid
} ng_test_status_code_t, *ng_test_status_code_ptr;

typedef struct _ng_test_result
{
    uint32_t ngTestCountNotImplement;
    char ngTestResultNotImplement[MAX_ELEMENT];
    uint32_t ngTestCountFailure;
    char ngTestResultFailure[MAX_ELEMENT];
    uint32_t ngTestCountSuccess;
    char ngTestResultSuccess[MAX_ELEMENT];
    uint32_t ngTestCountInvalid;
    char ngTestResultInvalid[MAX_ELEMENT];
} ng_test_result_t, *ng_test_result_ptr;

ng_test_result_t g_ngTestTotalResult;

/*******************************************************************************
 * API
 ******************************************************************************/

ng_global_status_code_t NG_TEST_Result_Init(ng_test_result_t *out);

ng_global_status_code_t NG_TEST_All(uint32_t argc, char **argv, ng_test_result_t *result);











#endif      /* __TEST_H__ */

/* END OF FILE */
