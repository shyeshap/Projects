/****************************************
*		Calculator Implementation		*		
*				Shye Shapira			*
*			reviewer: Ben Zaad			*
*				14/01/2020				*
*****************************************/

#include <assert.h> /* assert() */
#include <stdlib.h> /* malloc(), free() */
#include <string.h> /* strlen() */
#include <math.h> /* pow() */

#include "arithmetic.h" /* calculator implementation API */
#include "stack.h" /* stack API */

#define ASCII_SIZE 256
#define STATES_NUM 2

#define UNUSED(x) (void)(x)
#define FREE(ptr) free(ptr); ptr = NULL;

typedef char *(*func_state_t)(const char *expression, calc_t* calc);
typedef void (*func_op_t)(double x, double y, calc_t *calc);

typedef enum
{
	WAIT_FOR_NUM,
	WAIT_FOR_OP,
	ERROR
} state_t;

typedef enum
{
	OPEN_PARENTHESIS,
	END,
	ADD_AND_SUB,
	MULT_AND_DIFF,
	POWER
} presedence_t;

typedef struct State
{
	state_t next_state;
	func_state_t handle_func;
} calc_state_t;

typedef struct Operator
{
	func_op_t op_func;
	presedence_t presedence;
} calc_op_t;

struct Calc
{
	stack_t *num;
	stack_t *ops;
	double *result;
	calc_state_t *calc_lut;
	calc_op_t *op_lut;
};

static void CalcAdd(double num1, double num2, calc_t *calc)
{
	assert(NULL != calc);
	
	*calc->result = num1 + num2;
}

static void CalcSub(double num1, double num2, calc_t *calc)
{
	assert(NULL != calc);
	
	*calc->result = num1 - num2;
}

static void CalcMult(double num1, double num2, calc_t *calc)
{
	assert(NULL != calc);
	
	*calc->result = num1 * num2;
}

static void CalcDiff(double num1, double num2, calc_t *calc)
{
	assert(NULL != calc);
	
	*calc->result = num1 / num2;
}

static void CalcPow(double num1, double num2, calc_t *calc)
{
	assert(NULL != calc);
	
	*calc->result = pow(num1, num2);
}

static void Dummy(double num1, double num2, calc_t *calc)
{
	assert(NULL != calc);
	
	UNUSED(num1);
	UNUSED(num2);
	UNUSED(calc);
}

static char *DoNothing(const char *expression, calc_t* calc)
{
	UNUSED(calc);
	
	return (char *)expression;
}

static int CalcFold(calc_t *calc)
{
	double num1 = 0, num2 = 0;
	
	assert(NULL != calc);
	
	num1 = *(double *)StackPeek(calc->num);
	StackPop(calc->num);
	num2 = *(double *)StackPeek(calc->num);
	StackPop(calc->num);
	calc->op_lut[(int)*(char *)StackPeek(calc->ops)].op_func(num2, num1, calc);
	
	StackPop(calc->ops);
	
	return StackPush(calc->num, calc->result);
}

static char *HandleSpace(const char *expression, calc_t* calc)
{	
	UNUSED(calc);
	
	return (char *)++expression;
}

static char *CalcHandleNum(const char *expression, calc_t *calc)
{
	double num = 0;
	char *ret = (char *)expression;
	
	assert(NULL != calc);
	assert(NULL != expression);
	
	num = strtod(expression, &ret);
	
	if (!StackPush(calc->num, &num))
	{
		calc->calc_lut[(int)*ret].next_state = ERROR;
	}
	
	return ret;
}

static char *CalcHandleCloseParenthesis(const char *expression, calc_t *calc)
{
	char *runner = NULL;
	
	assert(NULL != calc);
	assert(NULL != expression);
	
	runner = (char *)expression;

	while (!(StackIsEmpty(calc->ops)) && '(' != (int)*(char *)StackPeek(calc->ops))
	{
		
		if (!CalcFold(calc))
		{
			calc->calc_lut[(int)*runner].next_state = ERROR;
		}
	}
	
	StackPop(calc->ops);
	
	return ++runner;
}

static char *CalcHandleOpeneParenthesis(const char *expression, calc_t *calc)
{
	char *runner = NULL;
	
	assert(NULL != calc);
	assert(NULL != expression);
	
	runner = (char *)expression;
	
	if (!StackPush(calc->ops, runner))
	{
		calc->calc_lut[(int)*runner].next_state = ERROR;
	}
	
	return ++runner;
}

static char *CalcHandlePow(const char *expression, calc_t *calc)
{
	char *runner = NULL;
	
	assert(NULL != calc);
	assert(NULL != expression);
	
	runner = (char *)expression;
	
	if (!StackPush(calc->ops, runner))
	{
		calc->calc_lut[(int)*runner].next_state = ERROR;
	}
	
	return ++runner;
}

static char *CalcHandleOp(const char *expression, calc_t *calc)
{
	int push_status = 0;
	char *runner = NULL;
	
	assert(NULL != calc);
	assert(NULL != expression);
	
	runner = (char *)expression;
	
	while (!(StackIsEmpty(calc->ops)) && (calc->op_lut[(int)*runner].presedence <= 
					calc->op_lut[(int)*(char *)StackPeek(calc->ops)].presedence))
	{
		push_status = CalcFold(calc);
	}
	
	if (!StackPush(calc->ops, runner))
	{
		calc->calc_lut[(int)*runner].next_state = ERROR;
	}
	
	return ++runner;
}

static void CalcLutInit(calc_state_t *calc_lut)
{
	unsigned int i = 0;

	assert(NULL != calc_lut);
		
	for (i = 0; i < (ASCII_SIZE * STATES_NUM); ++i)
	{
		calc_lut[i].next_state = ERROR;
		calc_lut[i].handle_func = &DoNothing;
	}
	
	for (i = '0'; i <= '9'; ++i)
	{
		calc_lut[i + (ASCII_SIZE * WAIT_FOR_NUM)].next_state = WAIT_FOR_OP;
		calc_lut[i + (ASCII_SIZE * WAIT_FOR_NUM)].handle_func = &CalcHandleNum;
	}
	
	/* WAIT_FOR_NUM init */
	calc_lut['.' + (ASCII_SIZE * WAIT_FOR_NUM)].next_state = WAIT_FOR_OP;
	calc_lut['.' + (ASCII_SIZE * WAIT_FOR_NUM)].handle_func = &CalcHandleNum;
	
	calc_lut['+' + (ASCII_SIZE * WAIT_FOR_NUM)].next_state = WAIT_FOR_OP;
	calc_lut['+' + (ASCII_SIZE * WAIT_FOR_NUM)].handle_func = &CalcHandleNum;
	
	calc_lut['-' + (ASCII_SIZE * WAIT_FOR_NUM)].next_state = WAIT_FOR_OP;
	calc_lut['-' + (ASCII_SIZE * WAIT_FOR_NUM)].handle_func = &CalcHandleNum;
	
	calc_lut['(' + (ASCII_SIZE * WAIT_FOR_NUM)].next_state = WAIT_FOR_NUM;
	calc_lut['(' + (ASCII_SIZE * WAIT_FOR_NUM)].handle_func = &CalcHandleOpeneParenthesis;
	
	calc_lut[' ' + (ASCII_SIZE * WAIT_FOR_NUM)].next_state = WAIT_FOR_NUM;
	calc_lut[' ' + (ASCII_SIZE * WAIT_FOR_NUM)].handle_func = &HandleSpace;
	
	/* WAIT_FOR_OP init */
	calc_lut['+' + (ASCII_SIZE * WAIT_FOR_OP)].next_state = WAIT_FOR_NUM;
	calc_lut['+' + (ASCII_SIZE * WAIT_FOR_OP)].handle_func = &CalcHandleOp;
	
	calc_lut['-' + (ASCII_SIZE * WAIT_FOR_OP)].next_state = WAIT_FOR_NUM;
	calc_lut['-' + (ASCII_SIZE * WAIT_FOR_OP)].handle_func = &CalcHandleOp;
		
	calc_lut['/' + (ASCII_SIZE * WAIT_FOR_OP)].next_state = WAIT_FOR_NUM;
	calc_lut['/' + (ASCII_SIZE * WAIT_FOR_OP)].handle_func = &CalcHandleOp;
		
	calc_lut['*' + (ASCII_SIZE * WAIT_FOR_OP)].next_state = WAIT_FOR_NUM;
	calc_lut['*' + (ASCII_SIZE * WAIT_FOR_OP)].handle_func = &CalcHandleOp;
		
	calc_lut['^' + (ASCII_SIZE * WAIT_FOR_OP)].next_state = WAIT_FOR_NUM;
	calc_lut['^' + (ASCII_SIZE * WAIT_FOR_OP)].handle_func = &CalcHandlePow;
	
	calc_lut[')' + (ASCII_SIZE * WAIT_FOR_OP)].next_state = WAIT_FOR_OP;
	calc_lut[')' + (ASCII_SIZE * WAIT_FOR_OP)].handle_func = &CalcHandleCloseParenthesis;
	
	calc_lut[' ' + (ASCII_SIZE * WAIT_FOR_OP)].next_state = WAIT_FOR_OP;
	calc_lut[' ' + (ASCII_SIZE * WAIT_FOR_OP)].handle_func = &HandleSpace;
	
	calc_lut['\0' + (ASCII_SIZE * WAIT_FOR_OP)].next_state = END;
	calc_lut['\0' + (ASCII_SIZE * WAIT_FOR_OP)].handle_func = &CalcHandleOp;
}

static void OpLutInit(calc_op_t *op_lut)
{
	unsigned int i = 0;
	
	assert(NULL != op_lut);
	
	for (i = 0; i < ASCII_SIZE; ++i)
	{
		op_lut[i].op_func = &Dummy;
		op_lut[i].presedence = 0;
	}
	
	op_lut['+'].op_func = &CalcAdd;
	op_lut['+'].presedence = ADD_AND_SUB;
	
	op_lut['-'].op_func = &CalcSub;
	op_lut['-'].presedence = ADD_AND_SUB;
	
	op_lut['*'].op_func = &CalcMult;
	op_lut['*'].presedence = MULT_AND_DIFF;
	
	op_lut['/'].op_func = &CalcDiff;
	op_lut['/'].presedence = MULT_AND_DIFF;
	
	op_lut['^'].op_func = &CalcPow;
	op_lut['^'].presedence = POWER;
	
	op_lut['\0'].presedence = END;
	
	op_lut['('].presedence = OPEN_PARENTHESIS;
}

calc_t *CalcInit(const char *expression, double *result)
{
	calc_t *new_calc = NULL;
	
	assert(NULL != result);
	assert(NULL != expression);
	
	new_calc = (calc_t *)malloc(sizeof(calc_t));
	if (NULL == new_calc)
	{
		return NULL;
	}
	
	new_calc->num = StackCreate(sizeof(double), strlen(expression));
	if (NULL == new_calc->num)
	{
		FREE(new_calc);
		return NULL;
	}
	
	new_calc->ops = StackCreate(sizeof(char), strlen(expression));
	if (NULL == new_calc->num)
	{
		FREE(new_calc->num);
		FREE(new_calc);
		return NULL;
	}

	new_calc->calc_lut = (calc_state_t *)malloc(ASCII_SIZE * STATES_NUM * sizeof(calc_state_t));
	if (NULL == new_calc->calc_lut)
	{
		FREE(new_calc->num);
		FREE(new_calc->ops);
		FREE(new_calc);
		return NULL;
	}
	
	new_calc->op_lut = (calc_op_t *)malloc(sizeof(calc_op_t) * ASCII_SIZE);
	if (NULL == new_calc->calc_lut)
	{
		FREE(new_calc->num);
		FREE(new_calc->ops);
		FREE(new_calc->calc_lut);
		FREE(new_calc);
		return NULL;
	}
	
	CalcLutInit(new_calc->calc_lut);
	OpLutInit(new_calc->op_lut);
	
	new_calc->result = result;
	
	return new_calc;
}

void CalcDestroy(calc_t *calc)
{
	assert(NULL != calc);
	
	FREE(calc->op_lut);
	FREE(calc->calc_lut);
	
	StackDestroy(calc->num);
	StackDestroy(calc->ops);
	
	FREE(calc);
}

calc_status_t CalcRun(const char *expression, calc_t *calc)
{
	char *runner = NULL;
	char holder = 0;
	state_t state = WAIT_FOR_NUM;
	
	assert(NULL != expression);
	assert(NULL != calc);
	
	runner = (char *)expression;
	holder = *runner;
	
	while (ERROR != state && '\0' != holder)
	{
		holder = *runner;
		runner = calc->calc_lut[holder + (state * ASCII_SIZE)].handle_func(runner, calc);
		state = calc->calc_lut[holder + (state * ASCII_SIZE)].next_state;
	}
	
	return state;
}
