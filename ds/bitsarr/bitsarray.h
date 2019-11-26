/*********************************/
/*    Data Structures            */
/*    Bits Arrays                */       
/*    Author :                   */
/*    Reviewed By:               */
/*    Date:     /11/2019         */
/*                               */
/*********************************/

#ifndef __BITS_ARRAY_H__ 
#define __BITS_ARRAY_H__

#include <stdio.h>

typedef size_t bitsarr_t;

/* sets all bits to 1 */
bitsarr_t BArrSetAllBits(bitsarr_t bits); 
/* sets all bits to 0 */
bitsarr_t BArrResetAllBits(bitsarr_t bits); 
/* returnes 1 if bit in given position set on */
int BArrIsOn(bitsarr_t bits, int position); 
/* returnes 1 if bit in given position set off */
int BArrIsOff(bitsarr_t bits, int position); 
/* return the number of all set on bits */
bitsarr_t BArrCountOn(bitsarr_t bits); 
/* return the number of the off bits */
bitsarr_t BArrCountOff(bitsarr_t bits); 
/*sets specific bit to the given status*/
bitsarr_t BArrSetBit(bitsarr_t bits, int position, int status); 
/* sets specific bit to 1 */
bitsarr_t BArrSetOn(bitsarr_t bits, int position);
/* sets specific bit to 0 */
bitsarr_t BArrSetOff(bitsarr_t bits, int position); 
/* rotate the array to left num_of_rotations times */
bitsarr_t BArrRotateLeft(bitsarr_t bits, int num_of_rotations);
/* rotate the array to right num_of_rotations times */ 
bitsarr_t BArrRotateRight(size_t bits, int num_of_rotations); 
/* return a string representig given bits array */
char* BArrToString(bitsarr_t bits, char* buffer);
/* flips specific bit */
bitsarr_t BArrFlipBit(bitsarr_t bits, int position);
/* mirroring a given bits array */
bitsarr_t BArrMirror(bitsarr_t bits); 

#endif
