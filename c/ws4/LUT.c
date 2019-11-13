/***********WS4 - FUNCTIONS**************
*										*
*		functions implementation		*
*										*
*****************************************/

#include <stdio.h>
#include <stdlib.h>
#include "LUT.h"

/*** If / Else implimentatoin ***/
int IfPrint()
{
	char c = '\0';
	printf("\n\n***If/Else implimentatoin*** \n\n");
	printf("Insert T/A to print or Esc to exit: \n");
	
	system("stty -icanon -echo");
	
	while(1)
	{
		c = getchar();
		
		if (c == 'A' || c == 'T')
		{
			printf("%c pressed\n", c);
		}
		else if ((int)c == 27)
		{
			printf("exiting\n");
			system("stty icanon echo");
			return 1;
		}
		else
		{
			printf("Wrong key!\n");
		}
	}
	
	system("stty icanon echo");
	
	return 0;
}

/*** Switch case implimentatoin ***/
int SwitchPrint()
{
	char c;
	
	printf("\n\n***Switch case implimentatoin*** \n\n");		
	printf("Insert T/A to print or Esc to exit: \n");
	
	system("stty -icanon -echo");
			
	while(1)
	{
		c = getchar();
		
		switch(c)
		{
		case 'T':
			printf("%c pressed\n", c);
			break;
		case 'A':
			printf("%c pressed\n", c);
			break;
		case 27:
			printf("exiting\n");
			system("stty icanon echo");
			return 1;
		default:
			printf("Wrong key!\n");
		}
	}
	system("stty icanon echo");
	
	return 0;
}

/****************************************
*										*
*		LUT implementation				*
*										*
*****************************************/
int PrintPressed(char);
int Esc(char);
int fun(char);

int LUTPrint(int (*pf[])(char))
{
	int i = 0, in = 0, ret = 1;
	
	while (i < 256)
	{
		pf[i] = fun;
		++i;
	}
	
	pf[27] = &Esc;
	pf[65] = &PrintPressed;
	pf[84] = &PrintPressed;

	printf("***\n\nLUT implimentatoin*** \n\n");
	printf("Insert T/A to print or Esc to exit:\n\n");
	system("stty -icanon -echo");	
	while (ret)
	{
		in = getchar();
		ret = (*pf[in])(in);
	}
	system("stty icanon echo");
	
	return 0;
}

/*** LUT Print ***/
int PrintPressed(char c)
{
	printf("%c pressed\n", c);
	return 1;
}

/*** Termination function***/
int Esc(char c)
{ 
	return 0;
}

/*** empty function ***/
int fun(char c){return 1;}

