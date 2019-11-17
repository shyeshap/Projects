#include <stdio.h>
#include <stdlib.h>

#include "bitwise.h" 

int Esc()
{
	return 0;
}

void test(int cond, const char *msg)
{
	if (cond)
	{
		printf(GRN "SUCCESS\n" RESET);
	}
	else
	{
		printf(RED "FAIL: %s\n" RESET, msg);
	}
}

int main()
{
	unsigned int x = 0, y = 0 ,ans = 0;
	unsigned int *px = &x, *py = &y;
	unsigned char c = 0;
	float f = 0.0;
	int choose = 0, esc = 1, x1 = 0, n = 0;
	
	printf("\
		0 -	exit\n\
		1 -	Pow2\n\
		2 -	LoopIsPow2\n\
		3 -	IsPow2\n\
		4 -	PlusOne\n\
		5 -	Print3BitsInt\n\
		6 -	ByteMirrorLoop\n\
		7 -	ByteMirror\n\
		8 -	Check2n6\n\
		9 -	Check2or6\n\
		10 -	Swap3n5\n\
		11 -	ClosestSmaller\n\
		12 - 	Swap\n\
		13 - 	LoopBitsOnNum\n\
		14 - 	BitsOnNum\n\
		15 - 	FloatAnalysis\n");
		
	while (esc)
	{
		printf("\nChoose number of program to run: ");
		scanf("%d", &choose);
		
		switch (choose)
		{
			case 1:
			{
				test(Pow2(0,1) == 0, "0 * (2^1)");
				test(Pow2(1,0) == 1, "1 * (2^0)");
				test(Pow2(4,10) == 4096, "4 * (2^10)");
				
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
				test(LoopIsPow2(16) == 1, "16");
				test(LoopIsPow2(7) == 0, "7");
				test(LoopIsPow2(0) == 0, "0");
				
				printf("Insert a number to chek if it is a power of 2: "); 
				scanf("%u", &x);
				printf("%d\n", LoopIsPow2(x));
				break;
			}	
			case 3:
			{
				test(IsPow2(16) == 1, "16");
				test(IsPow2(7) == 0, "7");
				test(IsPow2(0) == 0, "0");
				
				printf("Insert a number to chek if it is a power of 2: ");
				scanf("%u", &x);
				printf("%d\n", IsPow2(x));
				break;
			}
			case 4:
			{
				test(PlusOne(999999) == 1000000, "999999");
				test(PlusOne(0) == 1, "0");
				test(PlusOne(3245) == 3246, "3245");
				
				printf("insert a number to incriment by one: ");
				scanf("%d", &x1);
				printf("%d\n", PlusOne(x1));
				break;
			}
			case 5:
			{
				unsigned int arr1[] = {11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
				unsigned int arr2[] = {2134, 235, 765, 87, 4546535, 234};
				unsigned int arr3[] = {'a', 'd', 'h', 'f', 'p'};
				
				Print3BitsInt(arr1);
				Print3BitsInt(arr2);
				Print3BitsInt(arr3);
				break;
			}
			case 6:
			{
				test(ByteMirrorLoop(1) == 2147483648, "1");
				test(ByteMirrorLoop(0) == 0, "0");
				test(ByteMirrorLoop(2147483648) == 1, "2147483648");
				
				printf("Insert a number to flip bitwise: ");
				scanf("%u", &x);
				printf("%u", ByteMirrorLoop(x));
				break;
			}
			case 7:
			{
				test(ByteMirror(1) == 2147483648, "1");
				test(ByteMirror(0) == 0, "0");
				test(ByteMirror(2147483648) == 1, "2147483648")
				;
				printf("Insert a number to flip bitwise: ");
				scanf("%u", &x);
				printf("%u", ByteMirror(x));
				break;
			}
			case 8:
			{
				test(Check2n6(2) == 0, "2");
				test(Check2n6(34) == 1, "34");
				test(Check2n6(0) == 0, "0");
				
				printf("Insert a num to check bits 2 & 6: ");
				scanf("%c", &c);
				printf("%d", Check2n6(c)); 
				break;
			}
			case 9:
			{
				test(Check2or6(2) == 1, "2");
				test(Check2or6(34) == 1, "34");
				test(Check2or6(0) == 0, "0");
				
				printf("Insert a num to check bits 2 | 6: ");
				scanf("%c", &c);
				printf("%d", Check2or6(c));
				break;
			}
			case 10:
			{
				test(Swap3n5(52) == 52, "52");
				test(Swap3n5(48) == 36, "48");
				test(Swap3n5(36) == 48, "36");
				test(Swap3n5(32) == 32, "32");
				
				printf("Insert a num to swap bits 3 & 5: ");
				scanf("%c", &c);
				printf("%d", Swap3n5(c));
				break;
			}
			case 11:
			{
				test(ClosestSmaller(33) == 32, "33");
				test(ClosestSmaller(17) == 16, "17");
				test(ClosestSmaller(22) == 16, "22");
				test(ClosestSmaller(16) == 16, "16");
				
				printf("insert a number to fined the closest divisable by 16: ");
				scanf("%u", &x);
				printf("%u", ClosestSmaller(x));		
				break;
			}
			case 12:
			{
				printf("insert two unsigned ints to swap\n");
				printf("x: ");
				scanf("%u", &x);
				printf("y: ");
				scanf("%u", &y);
				px = &x;
				py = &y;
				Swap(px, py);
				printf("after swap:\n");
				printf("x: %u\n", x);
				printf("y: %u\n", y);
				break;
			}
			case 13:
			{
				test(LoopBitsOnNum(43256) == 8, "43256");
				test(LoopBitsOnNum(9999999) == 14, "9999999");
				test(LoopBitsOnNum(0) == 0, "0");
				test(LoopBitsOnNum(1) == 1, "1");
				
				printf("insert a number to count set bits: ");
				scanf("%d", &n);
				printf("no of bits: %d", LoopBitsOnNum(n));
				break;
			}
			case 14:
			{
				
				break;
			}
			case 15:
			{
				printf("Insert a float to print its bits: ");
				scanf("%f", &f);
				FloatAnalysis(f);
				break;
			}
			case 0:
			{
				esc = Esc();
			}
		}
	}
	return 0;
}

