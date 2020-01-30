/******************************************************************************
			Ws06 - Bitwise Operations
			Shye Shapira
			17.11.19
			revirewer- Yoav
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "bitwise.h" 

/***Ex1***/
long Pow2(unsigned int x, unsigned int y)
{
	return x << y;
}

/***Ex2 A***/
int LoopIsPow2(unsigned int n)
{
	unsigned int num = 1;
	
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
void Print3BitsInt(unsigned int *arr, int size)
{
	int i = 0, count = 0, n = 0;
	unsigned int cpy_i = 0;
	n = size / sizeof(unsigned int);
	
	for (i = 0; i < n; ++i)
	{
		cpy_i = arr[i];
		while ((cpy_i > 0) && (count <= 3))
		{
			count += (cpy_i & 1);
			cpy_i >>= 1;
		}
		if (count == 3)
		{
			printf("%u, ", arr[i]);
		}
		count = 0;
	}
	printf("\n");
}
	
/***Ex5 A***/
unsigned int ByteMirrorLoop(unsigned int x)
{
	unsigned int mirror = 0, i = 0;
	
	for (i = 0; i < NO_OF_BITS; i++)
	{
		mirror <<= 1;
		mirror |= 1 & x;
		x >>= 1;
	}
	
	return mirror;
}

/***Ex5 B***/
unsigned int ByteMirror(unsigned int x)
{
	x = ((x & m1) >> 16) | ((x & m2) << 16);
	x = ((x & m3) >> 8) | ((x & m4) << 8);
	x = ((x & m5) >> 4) | ((x & m6) << 4);
	x = ((x & m7) >> 2) | ((x & m8) << 2);
	x = ((x & m9) >> 1) | ((x & m10) << 1);
	return x; 	
}

/***Ex6 A***/
int Is2n6On(unsigned char c)
{
	unsigned int two = 1 << 1, six = 1 << 5;
	
	two = (two & c) >> 1;
	six = (six & c) >> 5;
	return two & six;
}

/***Ex6 B***/
int Is2or6On(unsigned char c)
{
	unsigned int two = 1 << 1, six = 1 << 5;
	
	two = (two & c) >> 1;
	six = (six & c) >> 5;
	return two | six;
}

/***Ex6 C***/
int Swap3n5(unsigned char c)
{
	unsigned int three = 0, five = 0, tmp = 0;
	
	five = (c >> 4) & 1;
	three = (c >> 2) & 1;
	tmp = five ^ three;
	five = tmp << 4;
	three = tmp << 2;
	
	return (c ^ (five | three));
}

/***Ex7***/
unsigned int ClosestSmaller(unsigned int x)
{
	return (x >> 4) << 4;
} 

/***Ex8***/
void Swap(unsigned int *px, unsigned int *py)
{
	*px <<= NO_OF_BITS / sizeof(unsigned int);
	*py = *py ^ *px;
	*px = *py % NO_OF_BITS;
	*py >>= NO_OF_BITS / sizeof(unsigned int);
}

/***Ex9 A***/
int LoopCountBitsOn(unsigned int x)
{
	unsigned int one = 1, count = 0;
	while (one <= x)
	{
		count += one & x;
		x >>= 1;
	}
	return count;
}

/***Ex9 B***/
/***Hamming weight***/
int CountBitsOn(unsigned int x)
{
    x = (x & m10 ) + ((x >>  1) & m10 ); /*put count of each  2 bits into those  2 bits*/ 
    x = (x & m8 ) + ((x >>  2) & m8 ); /*put count of each  4 bits into those  4 bits*/ 
    x = (x & m6 ) + ((x >>  4) & m6 ); /*put count of each  8 bits into those  8 bits*/
    x = (x & m4 ) + ((x >>  8) & m4 ); /*put count of each 16 bits into those 16 bits*/ 
    x = (x & m2) + ((x >> 16) & m2); /*put count of each 32 bits into those 32 bits*/ 
    return x;
}

/***Ex10***/
/***print bits***/
int BitPrint(int a, int loc)   
{
    int buf = a & 1<<loc;

    if (buf == 0)
    {
    	 return 0;
    }
    else 
    {
    	return 1; 
    }
}

/***Ex11***/
int *FloatAnalysis(float f)
{
	unsigned int *b = 0;
	int i = NO_OF_BITS - 1;
    b = (unsigned int*) &f;
    
    for (i = NO_OF_BITS - 1; i >= 0; i--)
    {
        printf("%d ", BitPrint(*b, i));
    }

    return 0;
}



