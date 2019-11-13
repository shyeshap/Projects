/***********WS4 - FUNCTIONS**************
*										*
*			functions call				*
*										*
*****************************************/

#include<stdio.h>
#include "LUT.h"

int main()
{	
	int (*pf[256])(char);
	
	IfPrint();
	SwitchPrint();
	LUTPrint(pf);
	
	return 0;	
}
