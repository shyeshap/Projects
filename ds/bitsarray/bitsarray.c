/*********************************/
/*    Data Structures            */
/*    Bits Arrays                */       
/*    Author :    Shye Shapira   */
/*    Reviewed By:               */
/*    Date:     /11/2019         */
/*                               */
/*********************************/

#include <stdio.h> /* size_t */
#include <assert.h> /* assert */

#include "bitsarray.h" /* bits array functions */

#define BINARY 2
#define BITS_IN_WORD 64

#define M1   0x5555555555555555UL /*binary: 0101...				*/
#define M2   0x3333333333333333UL /*binary: 00110011..			*/
#define M4   0x0F0F0F0F0F0F0F0FUL /*binary: 4 zeros,  4 ones ...	*/
#define M8   0x00FF00FF00FF00FFUL /*binary: 8 zeros,  8 ones ...	*/
#define M16  0x0000FFFF0000FFFFUL /*binary: 16 zeros, 16 ones ...	*/
#define M32  0x00000000FFFFFFFFUL /*binary: 32 zeros, 32 ones		*/
#define M11	 0xFFFFFFFFFFFFFFFFUL /*binary: 11111....				*/

bitsarr_t BArrSetAllBits(bitsarr_t bits)
{
	return bits |= M11;
}

bitsarr_t BArrResetAllBits(bitsarr_t bits)
{
	return (bits & 0);
}

int BArrIsOn(bitsarr_t bits, int position)
{	
	return (1 & (bits >> (position - 1)));
}

int BArrIsOff(bitsarr_t bits, int position)
{
	return !(1 & (bits >> (position - 1)));
}

bitsarr_t BArrSetOn(bitsarr_t bits, int position)
{
	return (bits | (1 << (position - 1)));
}

bitsarr_t BArrSetOff(bitsarr_t bits, int position)
{	
	return (bits & ~((1 << (position - 1))));
}

bitsarr_t BArrSetBit(bitsarr_t bits, int position, int status)
{
	if (0 == status)
	{
		return (bits & ~((1 << (position - 1))));
	}
	else 
	{
		return (bits | (1 << (position - 1)));
	}	
}

bitsarr_t BArrFlipBit(bitsarr_t bits, int position)
{
	return bits ^ (1 << (position - 1));
}

char *BArrToString(bitsarr_t bits, char *buffer)
{	
	int i = 0;
	char *head = NULL;
	
	assert(NULL != buffer);
	
	head = buffer;
	bits = BArrMirror(bits);
	
	while(i < BITS_IN_WORD)
	{
		*buffer = bits % BINARY + '0';
		++buffer;
		bits /= BINARY;
		++i;
	}
	
	*buffer = '\0';
	
	return head;
}

bitsarr_t BArrMirror(bitsarr_t bits)
{
	bits = (((bits & ~M32) >> 32) | ((bits & M32) << 32));
	bits = (((bits & ~M16) >> 16) | ((bits & M16) << 16));
	bits = (((bits & ~M8)  >>  8) | ((bits & M8)  <<  8));
	bits = (((bits & ~M4)  >>  4) | ((bits & M4)  <<  4));
	bits = (((bits & ~M2)  >>  2) | ((bits & M2)  <<  2));
	bits = (((bits & ~M1)  >>  1) | ((bits & M1)  <<  1));
	
	return bits;
}

bitsarr_t BArrCountOn(bitsarr_t bits)
{
    bits = (bits & M1 ) + ((bits >>  1) & M1 ); /*put count of each  2 bits into those  2 bits */
    bits = (bits & M2 ) + ((bits >>  2) & M2 ); /*put count of each  4 bits into those  4 bits */
    bits = (bits & M4 ) + ((bits >>  4) & M4 ); /*put count of each  8 bits into those  8 bits */
    bits = (bits & M8 ) + ((bits >>  8) & M8 ); /*put count of each 16 bits into those 16 bits */
    bits = (bits & M16) + ((bits >> 16) & M16); /*put count of each 32 bits into those 32 bits */
    bits = (bits & M32) + ((bits >> 32) & M32); /*put count of each 64 bits into those 64 bits */ 
    
    return bits;
}

bitsarr_t BArrCountOff(bitsarr_t bits)
{
	return BITS_IN_WORD - BArrCountOn(bits);
}

bitsarr_t BArrRotateRight(bitsarr_t bits, int num_of_rotations)
{
	return ((bits >> num_of_rotations % BITS_IN_WORD) ^ 
	(bits << (BITS_IN_WORD - num_of_rotations % BITS_IN_WORD)));
}

bitsarr_t BArrRotateLeft(bitsarr_t bits, int num_of_rotations)
{
	return ((bits << num_of_rotations % BITS_IN_WORD) ^ 
	(bits >> (BITS_IN_WORD - num_of_rotations % BITS_IN_WORD)));
}

