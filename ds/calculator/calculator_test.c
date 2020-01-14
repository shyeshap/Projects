#include <stdlib.h>

#include "utilities.h" /* RUN_TEST */
#include "calculator.h"

static void TestAdd()
{
    char add[] = ".2+3";
    double result = 0;
    
    printf("Add:\n");
    
    TEST(0 == Calculator(add, &result), ".2+3");
    TEST(3.200000 == result, "result");
}

static void TestSub()
{
    char sub[] = "100-30-20";
    double result = 0;
    
    printf("\nSub:\n");
    TEST(0 == Calculator(sub, &result), "100-30-20");
    TEST(50.000000 == result, "result");
}

static void TestMult()
{
    char mult[] = "8*4";
    double result = 0;
    
    printf("\nMult:\n");
    TEST(0 == Calculator(mult, &result), "8*4");
    TEST(32.000000 == result, "result");
}

static void TestDiv()
{
    char div[] = "1/4/2";
    double result = 0;
    
    printf("\nDiv:\n");
    TEST(0 == Calculator(div, &result), "1/4/2");
    TEST(0.125000 == result, "result");
}

static void TestPower()
{
    char pow[] = "2^3^2+2+3";
    double result = 0;
    
    printf("\nPow:\n");
    TEST(0 == Calculator(pow, &result), "2^3^2+2+3");
    TEST(517.000000 == result, "result");
}

static void TestComplex()
{
    char complex1[] = "(2+7)*6+5", complex2[] = "(((((((((2^3)))+3)";
    double result = 0;
    
    printf("\nComplex:\n");
    TEST(0 == Calculator(complex1, &result), "(2+7)*6+5");
    TEST(59.000000 == result, "result");
    TEST(0 == Calculator(complex2, &result), "invalid: (((((((((2^3)))+3)");
}

static void TestSpaces()
{
    char spaces[] = "  2+5";
    double result = 0;
    
    printf("\nSpaces:\n");
    TEST(0 == Calculator(spaces, &result), "  2+5");
    TEST(7.000000 == result, "result");
}

static void TestSyntaxError()
{
    char invalid1[] = "24*/8", invalid2[] = "5-", invalid3[] = "4+5)(+3";
    double result = 0;
    
    printf("\nSyntaxError:\n");
    TEST(1 == Calculator(invalid1, &result), "invalid: 24*/8");
    TEST(1 == Calculator(invalid2, &result), "invalid: 5-");
    TEST(1 == Calculator(invalid3, &result), "invalid: 4+5)(+3");
}

int main()
{    
    TestAdd();
    TestSub();
    TestMult();
    TestDiv();
    TestPower();
    TestComplex();
    TestSpaces();
    TestSyntaxError();    
     
    return 0;
}
