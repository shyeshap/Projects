/****************************************
*			Calculator API				*		
*			Shye Shapira				*
*			reviewer: Ben Zaad			*
*			14/01/2020					*
*****************************************/

#ifndef __ARITHMETICS_H__
#define __ARITHMETICS_H__

#include "calculator.h" /* user API of calculator */

typedef struct Calc calc_t;

/* Initiates LUT of all ASCII table 
	pointer to calculator struct or NULL for memory fail */
calc_t *CalcInit(const char *expression, double *result);

/* free all resorces in use */ 
void CalcDestroy(calc_t *calc);

/* calculator infrastructure */
calc_status_t CalcRun(const char *expression, calc_t *calc);

#endif
