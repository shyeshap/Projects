#include <stdio.h>

/********declare functions*********/
float DecPow(int n);
long int Flip(long int num);
void Swap(int **x, int **y);

 							
int main()
{

	printf("\nHexadecimal value of Hello world\n\n");
	printf("the ascii of hello world is %x, %x, %x, %x, %x, %x, %x, %x, %x, %x, %x, %x. %x\n", 		'\"', 'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\"');
	printf("which returns: %c%c%c%c%c%c%c%c%c%c%c%c%c\n\n", 
		0x22, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0x77, 0x6f, 0x72, 0x6c, 0x64, 0x22);


	int n = 0;
	printf("10^number:\n");
	printf("Insert the number: ");
	scanf("%d", &n);
	printf("10^%d = %f\n\n", n, DecPow(n));


	printf("\nFlip\n\n");

	long int num = 0;
	printf("Insert an intiger to be flipped: ");
	scanf("%ld", &num);
	printf("The flipped number is: %ld\n\n", Flip(num));




	printf("swap the location of two variabls:\n\n");
	int *px, *py, x = 0, y = 0;
	printf("Insert first value of a variablre to be swapped: ");
	scanf("%d", &x);
	printf("Insert second value of a variable to be swapped: ");
	scanf("%d", &y);
	px = &x;
	py = &y;
	Swap(&px, &py); 


	return 0;
}


/*******Ex4- return 10^n decleration********/

float DecPow(int n)
{
	int i = 0;
	float d_pow = 1.0, tmp = 10;
	
	if(n < 0)
	{
		tmp = 1.0/tmp;
		n = -n;
	}
	for(i = 0; i < n; i++)
	{
		d_pow *= tmp;
	}	

	return d_pow;
}


/******Ex5- flip intiger decleration********/

long int Flip(long int num)
{

	int temp = 0;
	long int final = 0;
	
	while(num > 10)
	{
		temp = (num % 10);
		final = (final + temp) * 10;
		num = num / 10;
	}
	final += num;

	return final;
}

/******** Ex6- swap decleration ************/




void Swap(int **x, int **y)
{
	printf	("\nx initial address: %p\ny inital address: %p\n", *x, *y);
		
	int **tmp;
	tmp = x;
	x = y;
	y = tmp;
	printf("\nx address after swap: %p\ny address after swap: %p\n\n", *x, *y);
}
