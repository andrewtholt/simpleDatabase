#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"
#include "db.h"

static FILE* temp_file = NULL;
int init_suite1(void);
/* The suite initialization function.
 * Opens the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */

int init_suite1(void) {
    if (NULL == (temp_file = fopen("temp.txt", "w+"))) {
        return -1;
    }
    else {
        return 0;
    }
}
/* The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite1(void)
{
    if (0 != fclose(temp_file)) {
        return -1;
    }
    else {
        temp_file = NULL;
        return 0;
    }
}

void testFRED() {
/*
    if (NULL != temp_file) {
        CU_ASSERT(0 == fred(0));
        CU_ASSERT(2 == fred(1));
        CU_ASSERT(8 == fred(4));
        CU_ASSERT(22 == fred(11));
    }
    */
}

void testSQUARE() {
}

static struct database *table;
void testCREATE() {
    table=db_create(101);
    CU_ASSERT( (struct database *)NULL != table);
}

void testSETATTRIB() {
    db_setattr(table,NEVER_SHRINK,0,10,10);
}

void testDBLOAD() {
    int status;

    status=db_load("tst.db", table);
    CU_ASSERT( 0 != status);
}


void testFINDFIRST_FAIL() {
    struct nlist *np;
    np=find_first("FRED",table);

    CU_ASSERT( (struct nlist *)NULL  == np);
}

void testINSTALL_1() {
    struct nlist *np;
    np= db_install("FRED", "Just testing", table);
    CU_ASSERT( (struct nlist *)NULL  != np);
}
void testFINDFIRST() {
    struct nlist *np;
    np=find_first("FRED",table);

    CU_ASSERT( (struct nlist *)NULL  != np);
}

int main() {
    CU_pSuite pSuite = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* add a suite to the registry */
    pSuite = CU_add_suite("Suite_1", init_suite1, clean_suite1);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(pSuite, "db_create()", testCREATE))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(pSuite, "db_setattr()", testSETATTRIB))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(pSuite, "db_load()", testDBLOAD))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(pSuite, "db_find_first() no entry", testFINDFIRST_FAIL))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(pSuite, "db_install() - add missing data", testINSTALL_1))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(pSuite, "db_find_first() - try find again.", testFINDFIRST))) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}

