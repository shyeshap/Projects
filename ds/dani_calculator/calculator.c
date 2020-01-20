#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "stack.h"
#include "calculator.h"
#include "calc.h"

#define ASCII 256
#define TAB   9
#define SPACE 32
#define FREE(x) free(x); x = NULL;
#define UNUSED(x) (void)(x)


calc_status_t Calculator(const char *expression, double *result)
{
	calc_t *new_calc = NULL;
	int state        = 0;
	
	new_calc = CalcInit(expression, result);

    InitOparationLut(new_calc);

    InitCalcLut(new_calc);

    state = CalcRun(expression, new_calc);

	CalcDestroy(new_calc);

	return state;
}