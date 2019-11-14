#include <stdio.h>

/***Ex1***/

long Pow2(unsigned int x, unsigned int y)
{
	return x << y;
}

/***Ex2 A***/
int LoopIsPow2(unsigned int n)
{
	unsigned int num = 1;
	
	if (n == 0)
	{
		return 0;
	}
	for (num = 1; n >= num; num = num << 1)
	{
	    if (num == n)
	    {
	        return 1;
	    }
	}
	return 0;
}

/***Ex2 B***/
int IsPow2(unsigned int n)
{
	if (n == 0)
	{
		return 0;
	}
	if ((n & (n-1)) == 0)
	{
		return 1;
	}
	return 0;	
}

/***Ex3***/
int PlusOne(int x)
{
	int m = 1;
	
	while ((x & m) != 0)
	{
		x = x ^ m;
		m <<= 1;
	}
	
	x = x ^ m;
	
	return x;
}

/***Ex4***/
int ThreeBitsOn(unsigned int *arr)
{
	for (i = 0; 32 > i; ++i)
	{
		sum += arr[i] % 2
}

int Esc()
{
	return 0;
}
int main()
{
	unsigned int x = 0, y = 0 ,ans = 0;
	int choose = 0, esc = 1, x1;

	printf("\
		1 -	Pow2\n\
		2 -	LoopIsPow2\n\
		3 -	IsPow2\n\
		4 -	PlusOne\n\
		5 -		\n\
		6 -		\n\
		8 -		\n\
		9 -		\n\
		10 -	\n\
		11 -	\n\
		12 - 	\n\
		13 - 	\n\
		14 - 	\n\
		15 - 	\n\
		16 - 	exit\n");
		
	while (esc)
	{
	printf("\nChoose number of program to run: ");
	scanf("%d", &choose);
	
	switch (choose)
	{
		case 1:
		{
			printf("insert x: ");
			scanf("%u", &x);
			printf("Insert y: ");
			scanf("%u", &y);
			ans = Pow2(x, y);
			printf("%u\n", ans);
			break;
		}
		case 2:
		{
			printf("Insert a number to chek if it is a power of 2: "); 
			scanf("%u", &x);
			printf("%d\n", LoopIsPow2(x));
			break;
		}	
		case 3:
		{
			printf("Insert a number to chek if it is a power of 2: ");
			scanf("%u", &x);
			printf("%d\n", IsPow2(x));
			break;
		}
		case 4:
		{
			printf("insert a number to incriment by one: ");
			scanf("%d", &x1);
			printf("%d\n", PlusOne(x1));
			break;
		}
		case 16:
		{
			esc = Esc();
		}
		
	}
	}
	return 0;
}

