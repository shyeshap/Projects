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


typedef struct State
{
	state_t next_state;
	func_state_t action;
} calc_state_t;

typedef struct Operator
{
	func_op_t op_handler;
	int presedence;
} calc_op_t;

struct Calc
{
	stack_t *stack_num;
	stack_t *stack_ops;
	double *result;
	calc_state_t *calc_lut;
	calc_op_t *op_lut;

};

int Plus(stack_t *num_stack, stack_t *op_stack)
{
	double a  = 0;
	double b  = 0;

	assert(NULL != num_stack);
	assert(NULL != op_stack);

	a = *(double*)StackPeek(num_stack);
	StackPop(num_stack);
	b = *(double*)StackPeek(num_stack);
	StackPop(num_stack);

	b += a;

	return (StackPush(num_stack, &b)); 
}

int Subtracts(stack_t *num_stack, stack_t *op_stack)
{
	double a  = 0;
	double b  = 0;

	assert(NULL != num_stack);
	assert(NULL != op_stack);

	a = *(double*)StackPeek(num_stack);
	StackPop(num_stack);
	b = *(double*)StackPeek(num_stack);
	StackPop(num_stack);

	b -= a;

	return (StackPush(num_stack, &b)); 
}

int Multiplication(stack_t *num_stack, stack_t *op_stack)
{
	double a  = 0;
	double b  = 0;

	assert(NULL != num_stack);
	assert(NULL != op_stack);

	a = *(double*)StackPeek(num_stack);
	StackPop(num_stack);
	b = *(double*)StackPeek(num_stack);
	StackPop(num_stack);

	b *= a;

	return (StackPush(num_stack, &b));  
}

int Division(stack_t *num_stack, stack_t *op_stack)
{
	double a  = 0;
	double b  = 0;

	assert(NULL != num_stack);
	assert(NULL != op_stack);

	a = *(double*)StackPeek(num_stack);
	StackPop(num_stack);
	b = *(double*)StackPeek(num_stack);
	StackPop(num_stack);

	b /= a;

	return (StackPush(num_stack, &b)); 
}

int Power(stack_t *num_stack, stack_t *op_stack)
{
	double a  = 0;
	double b  = 0;

	assert(NULL != num_stack);
	assert(NULL != op_stack);

	a = *(double*)StackPeek(num_stack);
	StackPop(num_stack);
	b = *(double*)StackPeek(num_stack);
	StackPop(num_stack);

	b = pow(b,a);

	return (StackPush(num_stack, &b)); 
}

int DummyFunction(stack_t *num_stack, stack_t *op_stack)
{
	UNUSED(num_stack); UNUSED(op_stack);

	return 1;
}

char *CalcHandleNum(const char *expression, calc_t *calc)
{
	char *runner = NULL;
	double ret = 0;

	ret = strtod(expression, &runner);

	StackPush(calc->stack_num, &ret);

	return runner;
}

char *CalcHandleOp(const char *expression, calc_t *calc)
{
	char op = '0';

	op = *expression;

	while ((!StackIsEmpty(calc->stack_ops)) && 
		     ((calc->op_lut[(int)op].presedence) <= 
			 (calc->op_lut[(int)(*(char*)(StackPeek(calc->stack_ops)))].presedence)) &&
		     (calc->op_lut[(int)op].presedence != 3))
	{
		calc->op_lut[(int)(*(char*)(StackPeek(calc->stack_ops)))].op_handler(calc->stack_num,
                                                                     calc->stack_ops);
		StackPop(calc->stack_ops);
	}

	StackPush(calc->stack_ops, &op);

	return (char*)(++expression);
}

char *CalcHandleOpen(const char *expression, calc_t *calc)
{
	char op = '0';

	op = *expression;

	StackPush(calc->stack_ops, &op);

	return (char*)(++expression);
}

char *CalcHandleClose(const char *expression, calc_t *calc)
{
	char op = '0';

	op = *expression;

	calc->op_lut['('].presedence = -1;

	while ((!StackIsEmpty(calc->stack_ops)) && 
		     ((calc->op_lut[(int)op].presedence) <= 
			   (calc->op_lut[(int)(*(char*)(StackPeek(calc->stack_ops)))].presedence)) &&
		     (calc->op_lut[(int)op].presedence != 3))
	{
		calc->op_lut[(int)(*(char*)(StackPeek(calc->stack_ops)))].op_handler(calc->stack_num,
                                                                     calc->stack_ops);
		StackPop(calc->stack_ops);
	}

	StackPop(calc->stack_ops);

	return (char*)(++expression);
}

char* Error(const char *expression, calc_t *calc)
{
	UNUSED(expression); UNUSED(calc);

	return (char*)(++expression);
}

calc_t *CalcInit(const char *exp, double *result)
{
	calc_t *new_calc       = NULL;
	stack_t *ops           = NULL;
	stack_t *num           = NULL;
	calc_state_t *calc_lut = NULL;
	calc_op_t *op_lut      = NULL;
	size_t exp_size        = strlen(exp);

	new_calc = (calc_t*)malloc(sizeof(calc_t));
	if (NULL == new_calc)
	{
		return NULL;
	}

	calc_lut = (calc_state_t*)malloc(ASCII * 3 * sizeof(calc_state_t));
	if (NULL == calc_lut)
	{
		FREE(new_calc);

		return NULL;
	}

	ops = StackCreate(sizeof(char), exp_size);
	if (NULL == ops)
	{
		FREE(calc_lut);
		FREE(new_calc);

		return NULL;
	}

	num = StackCreate(sizeof(double), exp_size);
	if (NULL == num)
	{
		FREE(calc_lut);
		FREE(ops);
		FREE(new_calc);

		return NULL;
	}

	op_lut = (calc_op_t*)malloc(ASCII * sizeof(calc_op_t));
	if (NULL == num)
	{
		FREE(calc_lut);
		FREE(ops);
		FREE(num);
		FREE(new_calc);

		return NULL;
	}

	new_calc->stack_ops = ops;
	new_calc->stack_num = num;
	new_calc->calc_lut  = calc_lut;
	new_calc->op_lut    = op_lut;
	new_calc->result = result;

	return new_calc;
}

void CalcDestroy(calc_t *calc)
{
	StackDestroy(calc->stack_ops);
	StackDestroy(calc->stack_num);
	FREE(calc->calc_lut);
	FREE(calc->op_lut);
	FREE(calc);
}

void InitOparationLut(calc_t *calc)
{
	int i = 0;

	for (; i < ASCII; ++i)
	{
		calc->op_lut[i].op_handler = DummyFunction;
		calc->op_lut[i].presedence = 0;
	} 

	calc->op_lut['+'].op_handler = Plus;
	calc->op_lut['-'].op_handler= Subtracts;
	calc->op_lut['*'].op_handler = Multiplication;
	calc->op_lut['/'].op_handler= Division;
	calc->op_lut['^'].op_handler= Power;

	calc->op_lut['+'].presedence = 1;
	calc->op_lut['-'].presedence = 1;
	calc->op_lut['*'].presedence = 2;
	calc->op_lut['/'].presedence = 2;
	calc->op_lut['^'].presedence = 3;
}

void InitCalcLut(calc_t *calc)
{
	int i = 0;

	for (; i < ASCII * 3; ++i)
	{
		calc->calc_lut[i].action = Error;
		calc->calc_lut[i].next_state = ERROR;
	} 

	for (i = '0'; i <= '9'; ++i)
	{
		calc->calc_lut[i].action = CalcHandleNum;
		calc->calc_lut[i].next_state = WAIT_FOR_OP;
	}

	calc->calc_lut['+'].action = CalcHandleNum;
	calc->calc_lut['-'].action = CalcHandleNum;
	calc->calc_lut['+'].next_state = WAIT_FOR_OP;
	calc->calc_lut['-'].next_state = WAIT_FOR_OP;

	calc->calc_lut['	'].action = CalcHandleNum;
	calc->calc_lut[' '].action    = CalcHandleNum;
	calc->calc_lut['.'].action    = CalcHandleNum;
	calc->calc_lut['	'].next_state = WAIT_FOR_OP;
	calc->calc_lut[' '].next_state    = WAIT_FOR_OP;
	calc->calc_lut['.'].next_state    = WAIT_FOR_OP;


	calc->calc_lut['('].action = CalcHandleOpen;
	calc->calc_lut['('].next_state = WAIT_FOR_NUM;

	calc->calc_lut[WAIT_FOR_OP * ASCII + ')'].action = CalcHandleClose;
	calc->calc_lut[WAIT_FOR_OP * ASCII + ')'].next_state = WAIT_FOR_OP;

	calc->calc_lut[WAIT_FOR_OP * ASCII + '+'].action = CalcHandleOp;
	calc->calc_lut[WAIT_FOR_OP * ASCII + '-'].action = CalcHandleOp;
	calc->calc_lut[WAIT_FOR_OP * ASCII + '*'].action = CalcHandleOp;
	calc->calc_lut[WAIT_FOR_OP * ASCII + '/'].action = CalcHandleOp;
	calc->calc_lut[WAIT_FOR_OP * ASCII + '^'].action = CalcHandleOp;
	calc->calc_lut[WAIT_FOR_OP * ASCII + '	'].action = CalcHandleOp;
	calc->calc_lut[WAIT_FOR_OP * ASCII + ' '].action = CalcHandleOp;

	calc->calc_lut[WAIT_FOR_OP * ASCII + '+'].next_state = WAIT_FOR_NUM;
	calc->calc_lut[WAIT_FOR_OP * ASCII + '-'].next_state = WAIT_FOR_NUM;
	calc->calc_lut[WAIT_FOR_OP * ASCII + '*'].next_state = WAIT_FOR_NUM;
	calc->calc_lut[WAIT_FOR_OP * ASCII + '/'].next_state = WAIT_FOR_NUM;
	calc->calc_lut[WAIT_FOR_OP * ASCII + '^'].next_state = WAIT_FOR_NUM;
	calc->calc_lut[WAIT_FOR_OP * ASCII + '	'].next_state = WAIT_FOR_OP;
	calc->calc_lut[WAIT_FOR_OP * ASCII + ' '].next_state = WAIT_FOR_OP;
}

state_t CalcRun(const char *expression, calc_t *calc)
{
	char *runner     = (char*)expression;
	int state        = 0;

	while ((ERROR != state) && ('\0' != *expression))
	{
		runner = calc->calc_lut[state * ASCII + *runner].action(expression, calc);
		state = calc->calc_lut[state * ASCII + *expression].next_state;
		expression = runner;
	}

	if (WAIT_FOR_OP != state)
	{
		return 1;
	}

	while (!StackIsEmpty(calc->stack_ops))
	{
		calc->op_lut[(int)(*(char*)(StackPeek(calc->stack_ops)))].
		                   op_handler(calc->stack_num, calc->stack_ops);

		StackPop(calc->stack_ops);
	}

	*calc->result = *(double*)StackPeek(calc->stack_num);

	return 0;
}
