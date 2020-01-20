/****************************************
*		User Calculator Function		*		
*				Shye Shapira			*
*			reviewer: Ben Zaad			*
*				14/01/2020				*
*****************************************/

#include <stdio.h> /* NULL */
#include <assert.h> /*assert */

#include "calculator.h" /* calculator API */
#include "arithmetic.h" /* internal implementation of calculartor functions */

calc_status_t Calculator(const char *expression, double *result)
{
	calc_t *calc = NULL;
	calc_status_t status = 0;
	
	assert(NULL != expression);
	assert(NULL != result);

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
