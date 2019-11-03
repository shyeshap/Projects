#include <stdio.h>

/********define functions*********/
float DecPow(int n);
int Flip(int num);
void Swap(int **x, int **y);

 							
int main()
{
/****************************************************************************************
 *					Ex3              				*
 *			   hexadecimal value of char call				* 
 ****************************************************************************************/
	printf("\nThis function prints out the hexadecimal value of Hello world\n\n");
	printf("the ascii of hello world is %x, %x, %x, %x, %x, %x, %x, %x, %x, %x, %x, %x. %x\n", 		'\"', 'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\"');
	printf("which returns: %c%c%c%c%c%c%c%c%c%c%c%c%c\n\n", 0x22, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 		0x20, 0x77, 0x6f, 0x72, 0x6c, 0x64, 0x22);


/****************************************************************************************
 *					Ex4						*
 *				  return 10^n call					*
 ****************************************************************************************/

	int n;
	printf("\nThis function will return 10^number\n");
	printf("Insert the number: ");
	scanf("%d", &n);
	printf("%f\n\n", DecPow(n));

/****************************************************************************************
 *					Ex5						*
 *				   flip intiger call					*
 ****************************************************************************************/
	printf("\nThis funtion will flip your number\n\n");
	
	int num;
	printf("Insert an intiger to be flipped: ");
	scanf("%d", &num);
	printf("The flipped number is: %d\n\n", Flip(num));


/****************************************************************************************
 *					Ex6						*
 *				     swap call  					*
 ****************************************************************************************/

	printf("This function will swap the location of two variabls\n\n");
	int *px, *py, x, y;
	printf("Insert first value of a variablre to be swapped: ");
	scanf("%d", &x);
	printf("Insert second value of a variable to be swapped: ");
	scanf("%d", &y);
	px = &x;
	py = &y;
	Swap(&px, &py); 


	return 0;
}


/****************************************************************************************
*											*
*					Ex4						*
*			       return 10^n decleration 					*
*											*
*****************************************************************************************/

float DecPow(int n)
{
	int i;
	float d_pow = 1.0;
	
	if(n < 0)
	{
		d_pow = 1.0/n;
	}
	for(i = 0; i < n; i++)
	{
		d_pow *= 10.0;
	}	

	return d_pow;
}


/****************************************************************************************
*											*
*					Ex5						*
*			      flip intiger decleration					*
*											*
*****************************************************************************************/

int Flip(int num)
{

	int temp, fin = 0;
	
	while(num > 10)
	{
		temp = (num % 10);
		fin = (fin + temp) * 10;
		num = num / 10;
	}
	fin += num;

	return fin;
}

/****************************************************************************************
*											*
*					Ex6						*
*				  swap decleration  					*
*											*
*****************************************************************************************/




void Swap(int **x, int **y)
{
	printf	("\nx initial address: %p\ny inital address: %p\n", *x, *y);
		
	int **tmp;
	tmp = x;
	x = y;
	y = tmp;
	printf("\nx address after swap: %p\ny address after swap: %p\n\n", *x, *y);
}
