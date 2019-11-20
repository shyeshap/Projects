#include <stdio.h>

#define MAX2(a, b) ((a > b) ? a : b)
#define MAX3(a, b, c) MAX2(MAX2(a, b), c) 
						
int main()
{
	int a, b, c, max2, max3;
	a = 1;
	b = 2;
	
	max2 = MAX2(a, b);
	printf("Maximum number: %d\n", max2);
	
	c = 3;
	max3 = MAX3(a, b, c);
	printf("Maximum number: %d\n", max3);
	
	return 0;
}
