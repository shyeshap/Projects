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

#include "arithmetic.h" 
#include "stack.h" /* stack API */

#define FREE(ptr) free(ptr); ptr = NULL;
#define ASCII_SIZE 256
#define STATES_NUM 2
#define UNUSED(x) (void)(x)

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

static void CalcAdd(double x, double y, calc_t *calc)
{
	*calc->result = x + y;
}

static void CalcSub(double x, double y, calc_t *calc)
{
	*calc->result = x - y;
}

static void CalcMult(double x, double y, calc_t *calc)
{
	*calc->result = x * y;
}

static void CalcDiff(double x, double y, calc_t *calc)
{
	*calc->result = x / y;
}

static void CalcPow(double x, double y, calc_t *calc)
{
	*calc->result = pow(x, y);
}

static void NotOp(double x, double y, calc_t *calc)
{
	UNUSED(x);
	UNUSED(y);
	UNUSED(calc);
}

static char *DoNothing(const char *expression, calc_t* calc)
{
	UNUSED(calc);
	
	return (char *)expression;
}

static int CalcFold(calc_t *calc)
{
	double x = 0, y = 0;
	
	x = *(double *)StackPeek(calc->num);
	StackPop(calc->num);
	y = *(double *)StackPeek(calc->num);
	StackPop(calc->num);
	calc->op_lut[(int)*(char *)StackPeek(calc->ops)].op_func(y, x, calc);
	
	StackPop(calc->ops);
	
	return StackPush(calc->num, calc->result);
}

static char *HandleSpace(const char *expression, calc_t* calc)
{	
	char *runner = (char *)expression;

	UNUSED(calc);
	
	return ++runner;
}

static char *CalcHandleNum(const char *expression, calc_t *calc)
{
	double num = 0;
	char *ret = (char *)expression;
	int push_status = 0;
	
	num = strtod(expression, &ret);
	
	push_status = StackPush(calc->num, &num);
	if (0 == push_status)
	{
		calc->calc_lut->next_state = ERROR;
	}
	
	return ret;
}

static char *CalcHandleCloseParenthesis(const char *expression, calc_t *calc)
{
	char *runner = NULL;
	int folder_status = 0;
	
	runner = (char *)expression;

	while (!(StackIsEmpty(calc->ops)) && '(' != (int)*(char *)StackPeek(calc->ops))
	{
		folder_status = CalcFold(calc);
		if (0 == folder_status)
		{
			calc->calc_lut->next_state = ERROR;
		}
	}
	
	StackPop(calc->ops);
	
	return ++runner;
}

static char *CalcHandleOpeneParenthesis(const char *expression, calc_t *calc)
{
	char *runner = NULL;
	int push_status = 0;
	
	runner = (char *)expression;
	
	push_status = StackPush(calc->ops, expression);
	if (0 == push_status)
	{
		calc->calc_lut->next_state = ERROR;
	}
	
	return ++runner;
}

static char *CalcHandlePow(const char *expression, calc_t *calc)
{
	int push_status = 0;
	char *runner = (char *)expression;
	
	push_status = StackPush(calc->ops, expression);
	if (0 == push_status)
	{
		calc->calc_lut->next_state = ERROR;
	}
	
	return ++runner;
}

static char *CalcHandleOp(const char *expression, calc_t *calc)
{
	int push_status = 0;
	char *runner = (char *)expression;
	
	while (!(StackIsEmpty(calc->ops)) && (calc->op_lut[(int)*runner].presedence <= 
					calc->op_lut[(int)*(char *)StackPeek(calc->ops)].presedence))
	{
		push_status = CalcFold(calc);
	}
	
	push_status = StackPush(calc->ops, expression);
	
	if (0 == push_status)
	{
		calc->calc_lut->next_state = ERROR;
	}
	
	return ++runner;
}

static void CalcLutInit(calc_state_t *calc_lut)
{
	unsigned int i = 0;
	calc_state_t *runner = NULL;

	assert(NULL != calc_lut);	

	runner = calc_lut;
		
	while (i < (ASCII_SIZE * STATES_NUM))
	{
		runner->next_state = ERROR;
		runner->handle_func = &DoNothing;
		++runner;
		++i;
	}
	
	runner = calc_lut;
	
	for (i = '0'; i <= '9'; ++i)
	{
		runner[i + (ASCII_SIZE * WAIT_FOR_NUM)].next_state = WAIT_FOR_OP;
		runner[i + (ASCII_SIZE * WAIT_FOR_NUM)].handle_func = &CalcHandleNum;
	}
	
	/* WAIT_FOR_NUM init */
	runner['.' + (ASCII_SIZE * WAIT_FOR_NUM)].next_state = WAIT_FOR_OP;
	runner['.' + (ASCII_SIZE * WAIT_FOR_NUM)].handle_func = &CalcHandleNum;
	
	runner['+' + (ASCII_SIZE * WAIT_FOR_NUM)].next_state = WAIT_FOR_OP;
	runner['+' + (ASCII_SIZE * WAIT_FOR_NUM)].handle_func = &CalcHandleNum;
	
	runner['-' + (ASCII_SIZE * WAIT_FOR_NUM)].next_state = WAIT_FOR_OP;
	runner['-' + (ASCII_SIZE * WAIT_FOR_NUM)].handle_func = &CalcHandleNum;
	
	runner['(' + (ASCII_SIZE * WAIT_FOR_NUM)].next_state = WAIT_FOR_NUM;
	runner['(' + (ASCII_SIZE * WAIT_FOR_NUM)].handle_func = &CalcHandleOpeneParenthesis;
	
	runner[' ' + (ASCII_SIZE * WAIT_FOR_NUM)].next_state = WAIT_FOR_NUM;
	runner[' ' + (ASCII_SIZE * WAIT_FOR_NUM)].handle_func = &HandleSpace;
	
	/* WAIT_FOR_OP init */
	runner['+' + (ASCII_SIZE * WAIT_FOR_OP)].next_state = WAIT_FOR_NUM;
	runner['+' + (ASCII_SIZE * WAIT_FOR_OP)].handle_func = &CalcHandleOp;
	
	runner['-' + (ASCII_SIZE * WAIT_FOR_OP)].next_state = WAIT_FOR_NUM;
	runner['-' + (ASCII_SIZE * WAIT_FOR_OP)].handle_func = &CalcHandleOp;
		
	runner['/' + (ASCII_SIZE * WAIT_FOR_OP)].next_state = WAIT_FOR_NUM;
	runner['/' + (ASCII_SIZE * WAIT_FOR_OP)].handle_func = &CalcHandleOp;
		
	runner['*' + (ASCII_SIZE * WAIT_FOR_OP)].next_state = WAIT_FOR_NUM;
	runner['*' + (ASCII_SIZE * WAIT_FOR_OP)].handle_func = &CalcHandleOp;
		
	runner['^' + (ASCII_SIZE * WAIT_FOR_OP)].next_state = WAIT_FOR_NUM;
	runner['^' + (ASCII_SIZE * WAIT_FOR_OP)].handle_func = &CalcHandlePow;
	
	runner[')' + (ASCII_SIZE * WAIT_FOR_OP)].next_state = WAIT_FOR_OP;
	runner[')' + (ASCII_SIZE * WAIT_FOR_OP)].handle_func = &CalcHandleCloseParenthesis;
	
	runner[' ' + (ASCII_SIZE * WAIT_FOR_OP)].next_state = WAIT_FOR_OP;
	runner[' ' + (ASCII_SIZE * WAIT_FOR_OP)].handle_func = &HandleSpace;
	
	runner['\0' + (ASCII_SIZE * WAIT_FOR_OP)].next_state = END;
	runner['\0' + (ASCII_SIZE * WAIT_FOR_OP)].handle_func = &CalcHandleOp;
}

static void OpLutInit(calc_op_t *op_lut)
{
	calc_op_t *runner = NULL;
	unsigned int i = 0;
	
	assert(NULL != op_lut);
	
	runner = op_lut;
	
	while (i < ASCII_SIZE)
	{
		runner->op_func = &NotOp;
		runner->presedence = 0;
		++runner;
		++i;
	}
	
	runner = op_lut;
	
	runner['+'].op_func = &CalcAdd;
	runner['+'].presedence = ADD_AND_SUB;
	
	runner['-'].op_func = &CalcSub;
	runner['-'].presedence = ADD_AND_SUB;
	
	runner['*'].op_func = &CalcMult;
	runner['*'].presedence = MULT_AND_DIFF;
	
	runner['/'].op_func = &CalcDiff;
	runner['/'].presedence = MULT_AND_DIFF;
	
	runner['^'].op_func = &CalcPow;
	runner['^'].presedence = POWER;
	
	runner['\0'].presedence = END;
}

calc_t *CalcInit(const char *expression, double *result)
{
	calc_t *new_calc = (calc_t *)malloc(sizeof(calc_t));
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
	
	CalcLutInit(new_calc->calc_lut);
	
	new_calc->op_lut = (calc_op_t *)malloc(sizeof(calc_op_t) * ASCII_SIZE);
	if (NULL == new_calc->calc_lut)
	{
		FREE(new_calc->num);
		FREE(new_calc->ops);
		FREE(new_calc->calc_lut);
		FREE(new_calc);
		return NULL;
	}
	
	OpLutInit(new_calc->op_lut);
	
	new_calc->result = result;
	
	return new_calc;
}

void CalcDestroy(calc_t *calc)
{
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
