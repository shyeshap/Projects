/****************************************
*		User Calculator Function		*		
*				Shye Shapira			*
*			reviewer: Ben Zaad			*
*				14/01/2020				*
*****************************************/

#include <stdio.h>
#include <assert.h> /*assert */

#include "calculator.h" /* calculator API */
#include "arithmetic.h" /* internal implementation of calculartor functions */
#include "stack.h" /* stack API */
/*
static calc_status_t ParenthesisCheck(const char *expression)
{
	size_t left_parenthesis = 0, right_parenthesis = 0;
	char *runner = NULL;
	
	assert(NULL != expression);
	
	runner = (char *)expression;
	
	while ('\0' != *runner && left_parenthesis >= right_parenthesis)
	{
		if ('(' == *runner)
		{
			++left_parenthesis;
		}
		
		else if (')' == *runner)
		{
			++right_parenthesis;
		}
		++runner;
	}
	
	return !(('\0' == *runner) && (left_parenthesis >= right_parenthesis));
}
*/
calc_status_t Calculator(const char *expression, double *result)
{
	calc_t *calc = NULL;
	calc_status_t status = 0;
	
	assert(NULL != expression);
	assert(NULL != result);
	
	/*status = ParenthesisCheck(expression);
	*/
	if (status == 0)
	{	
		calc = CalcInit(expression, result);
		if (NULL == calc)
		{
			return MEMORY_FAIL;
		}
		
		status = (CalcRun(expression, calc) != 1);
		
		CalcDestroy(calc);
	}
	
	return status;	
}
