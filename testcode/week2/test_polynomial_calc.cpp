#include <stdio.h>
#include <string.h>

#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTestExt/MockSupport.h"

#include "polynomial_calc.h"

//#define ENABLE_INPUT

static const char *input_str_1 = "4 3 4 -5 2 6 1 -2 0";
static const char *input_str_2 = "3 5 20 -7 4 3 1";
static const char *result_empty = "0 0";
static const char *result_add = "5 5 20 -4 4 -5 2 9 1 -2 0";
static const char *result_multi = "";

TEST_GROUP( test_polynomial_calc )
{
    void setup()
    {
    }

    void teardown()
    {
    }
};

TEST( test_polynomial_calc, input_exception )
{
    struct PolyMgr *p1;
    const char *str_empty = "0";

    p1 = Polynomial_CreateMgr_FromString( str_empty );

    STRCMP_EQUAL(Polynomial_Print_String(p1), result_empty );

    Polynomial_DecreateMgr( p1 );
};

TEST( test_polynomial_calc, add )
{
    struct PolyMgr *p1;
    struct PolyMgr *p2;
    struct PolyMgr *add;
    struct PolyMgr *add2;

#ifdef ENABLE_INPUT
    p1 = Polynomial_CreateMgr_FromInput();
    p2 = Polynomial_CreateMgr_FromInput();
#else
    p1 = Polynomial_CreateMgr_FromString( input_str_1 );
    p2 = Polynomial_CreateMgr_FromString( input_str_2 );
#endif

    add = Polynomial_Add( p1, p2 );
    Polynomial_Print( add );

    STRCMP_EQUAL(Polynomial_Print_String(add), result_add );

    add2 = Polynomial_Add( p2, p1 );
    Polynomial_Print( add2 );
    STRCMP_EQUAL(Polynomial_Print_String(add2), result_add );

    Polynomial_DecreateMgr( p1 );
    Polynomial_DecreateMgr( p2 );

    Polynomial_DecreateMgr( add );
    Polynomial_DecreateMgr( add2 );
};

TEST( test_polynomial_calc, multi )
{
    struct PolyMgr *p1;
    struct PolyMgr *p2;
    struct PolyMgr *multi_1;
    struct PolyMgr *multi_2;

#ifdef ENABLE_INPUT
    p1 = Polynomial_CreateMgr_FromInput();
    p2 = Polynomial_CreateMgr_FromInput();
#else
    p1 = Polynomial_CreateMgr_FromString( input_str_1 );
    p2 = Polynomial_CreateMgr_FromString( input_str_2 );
#endif

    multi_1 = Polynomial_Multi( p1, p2 );
    Polynomial_Print( multi_1 );

    STRCMP_EQUAL(Polynomial_Print_String(multi_1), result_multi );

    multi_2 = Polynomial_Add( p2, p1 );
    Polynomial_Print( multi_2 );
    STRCMP_EQUAL(Polynomial_Print_String(multi_2), result_multi );

    Polynomial_DecreateMgr( p1 );
    Polynomial_DecreateMgr( p2 );

    Polynomial_DecreateMgr( multi_1 );
    Polynomial_DecreateMgr( multi_2 );
};

