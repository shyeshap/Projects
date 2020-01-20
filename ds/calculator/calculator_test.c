/************************************************
*
* File: calculator_test.c
* Ex: calculator
* writer: Israel Drayfus
* Description: Run and test calculator.
*
*************************************************/

#include <stdio.h> /*printf()*/

#include "calculator.h"

#define RED "\033[31m"
#define GREEN "\033[32m"
#define WHITE "\033[0m"

#define TEST(test, errMsg) if (test)\
						   {\
						      printf(GREEN);\
						      printf("%s\n", "SUCCESS");\
						   }\
						   else\
						   {\
						      printf(RED);\
						      printf("%s, %s\n", "FAILURE", errMsg);\
						   }\
						   printf(WHITE);

void Test1()
{
	double result = 0.0;
	
	Calculator("1+1", &result);
	TEST(result == 2, "plus");
	Calculator(" 1 + 1 ", &result);
	TEST(result == 2, "plus with whitespaces");
	Calculator(" 1 - 1 ", &result);
	TEST(result == 0, "minus");
	Calculator(" 1 / 2 ", &result);
	TEST(result == 0.5, "devision");
	Calculator(" 2 * 3 ", &result);
	TEST(result == 6, "multification");
	Calculator(" 2 ^ 3 ", &result);
	TEST(result == 8, "power");
	Calculator(" 0 + 1 ", &result);
	TEST(result == 1, "plus with zero");
	printf("\n");
	
	Calculator("2+2+4", &result);
	TEST(result == 8, "plus twise");
	Calculator("2*2+4", &result);
	TEST(result == 8, "different operators");
	Calculator("2*2+4", &result);
	TEST(result == 8, "different operators");
	Calculator("2+-4", &result);
	TEST(result == -2, "different operators");
	Calculator("2++4", &result);
	TEST(result == 6, "different operators");
	printf("\n");
}

void Test2()
{
	double result = 0.0;
	
	Calculator("2+2*4", &result);
	TEST(result == 10, "presedence");
	Calculator("3-2-3", &result);
	TEST(result == -2, "presedence");
	Calculator("3^2^3", &result);
	TEST(result == 6561, "presedence");
	Calculator("1+2*3^3*2+1", &result);
	TEST(result == 110, "presedence");
	printf("\n");
}

void Test3()
{
	double result = 0.0;
	
	Calculator("3^2^3/123-81*0+21/89", &result);
	printf("result = %f (Success = 53.577418)\n", result);
	Calculator(".35 + 1", &result);
	printf("result = %f (Success = 1.35)\n", result);
	Calculator("-.35 + +1", &result);
	printf("result = %f (Success = 0.65)\n", result);
	printf("\n");
}

void Test4()
{
	double result = 0.0;
	
	Calculator("(1+2)", &result);
	TEST(result == 3, "parentheses");
	Calculator("(1+2+3)", &result);
	TEST(result == 6, "parentheses");
	Calculator("1+(1+2)", &result);
	TEST(result == 4, "parentheses");
	printf("\n");

	Calculator("(2*(2+2))", &result);
	TEST(result == 8, "parentheses");
	Calculator("((2+1)*2)", &result);
	TEST(result == 6, "parentheses");
	Calculator("1+(1+2*(3+4))", &result);
	TEST(result == 16, "parentheses");
	Calculator("256/(2^2^3)+2", &result);
	TEST(result == 3, "parentheses");
	Calculator("2^(1+1)^2", &result);
	TEST(result == 16, "parentheses");
	printf("\n");

}

void Test5()
{
	double result = 0.0;
	calc_status_t status;
	
	status = Calculator("1+2)", &result);
	TEST(status == SYNTAX_ERROR, "syntax error");
	status = Calculator("((1+2)", &result);
	TEST(status == SUCCESS, "syntax error");
	status = Calculator("1+2+", &result);
	TEST(status == SYNTAX_ERROR, "syntax error");
	status = Calculator("1+2+-", &result);
	TEST(status == SYNTAX_ERROR, "syntax error");
	status = Calculator("((1+2 2)", &result);
	TEST(status == SYNTAX_ERROR, "syntax error");
	status = Calculator("+1+2 /", &result);
	TEST(status == SYNTAX_ERROR, "syntax error");
	status = Calculator("1+2 .", &result);
	TEST(status == SYNTAX_ERROR, "syntax error");
}

int main()
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();

	return 0;
}























