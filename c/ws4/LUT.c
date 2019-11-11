#include<stdio.h>
#include <ctype.h> /*toupper*/

/*** If / Else implimentatoin ***/
int IfPrint(void)
{
	char c = '\0';
	printf("\n\n***If/Else implimentatoin*** \n\n");
	printf("Insert T/A to print or Esc to exit: \n");
	
	system("stty -icanon -echo");
	
	while(1)
	{
		c = getchar();
		
		if (c == 'a' || c == 't' || c == 'A' || c == 'T')
		{
			printf("%c pressed\n", toupper(c));
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
	while(1)
	{
		system("stty -icanon -echo");
		
		c = getchar();
		
		switch(c)
		{
		case 't':
			printf("%c pressed\n", toupper(c));
			break;
		case 'a':
			printf("%c pressed\n", toupper(c));
			break;
		case 27:
			printf("exiting\n");
			system("stty icanon echo");
			return 1;
		default:
			printf("Wrong key!\n");
		}
		system("stty icanon echo");
	}
	
	return 0;
}

/*** LUT implimentatoin ***/
int PrintPressed(char c)
{
	printf("%c pressed\n", toupper(c));
	return 1;
}

int Esc(char c)
{
	return 0;
}

int fun(char c){}

int LUTPrint()
{
	int i = 0, in = 0, ret = 1;
	int (*pf[256])(char);
	
	while (i < 256)
	{
		pf[i] = fun;
		++i;
	}
	
	pf[27] = &Esc;
	pf[65] = &PrintPressed;
	pf[84] = &PrintPressed;
	pf[97] = &PrintPressed;
	pf[116] = &PrintPressed;

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

int main()
{	
	IfPrint();
	SwitchPrint();
	LUTPrint();
	
	
	return 0;	
}
