/*********************************/
/*    Data Structures            */
/*    Bits Arrays                */       
/*    Author :   Shye Shapira    */
/*    Reviewed By:               */
/*    Date:     /11/2019         */
/*                               */
/*********************************/

#include <string.h> /* strcmp(), strcpy() */
#include <stdlib.h> /*malloc */

#include "bitsarray.h"

#define GRN  "\x1B[32m"
#define RED  "\x1B[31m"
#define RESET "\x1B[0m"

#define M1   0x5555555555555555UL
#define M8   0x00FF00FF00FF00FFUL

#define BITS_IN_WORD 64

#define RUN_TEST(test, msg)	if(test)					 	\
							{								\
								printf(GRN "[OK]\n" RESET);	\
							}								\
							else							\
							{								\
								printf(RED "%s\n", msg);	\
							}

char *cmp = NULL;

static void  TestSetAll()
{
	RUN_TEST(BArrSetAllBits(3698) == ~(size_t)0, "set all");
}

static void TestResetAll()
{
	RUN_TEST(BArrResetAllBits(58786) == 0, "rest all");
}

static void TestIsOn()
{
	RUN_TEST(BArrIsOn(73246, 10) == 1, "is on 1");
	RUN_TEST(BArrIsOn(874356438, 10), "is on 2");
}

static void TestIsOff()
{
	RUN_TEST(BArrIsOff(16, 12) == 1, "is off 1");
	RUN_TEST(BArrIsOff(1, 1) == 0, "is off 2");	
}

static void TestSetOn()
{
	RUN_TEST(BArrSetOn(8567, 8) == 8695, "set on");
}

static void TestSetOff()
{
	RUN_TEST(BArrIsOff(1, 1) == 0, "set off");
}

static void TestSetBit()
{
	RUN_TEST(BArrSetBit(123456789, 9, 0) == 123456533, "set bit - turn off");
	RUN_TEST(BArrSetBit(54, 10, 1) == 566, "set bit - turn on");
}

static void TestFlip()
{
	RUN_TEST(BArrFlipBit(12345, 6) == 12313, "flip 1");
	RUN_TEST(BArrFlipBit(12345, 10) == 12857, "flip 2");
}

static void TestToStr()
{
	char *arr = (char *) malloc (BITS_IN_WORD * sizeof(char));
	
	cmp = "0000000000000000000000000000000000111010110111100110100010110001";
	RUN_TEST(!(strcmp(BArrToString(987654321, arr), cmp)), "to str 1");
	
	cmp = "0000000000000000000000000000000000000000000000000000000000000001";
	RUN_TEST(!(strcmp(BArrToString(1UL, arr), cmp)) , "to str 2");
	
	cmp = "0000000000000000000000000000000000000000000000000000000000001001";
	RUN_TEST(!(strcmp(BArrToString(9, arr), cmp)) , "to str 3");
	
	free(arr); arr = NULL;
}

static void TestMirror()
{
	RUN_TEST(BArrMirror(M1) == ~M1, "mirror 1");
	RUN_TEST(BArrMirror(M8) == ~M8, "mirror 2");
	RUN_TEST(BArrMirror(1UL) == 1UL << 63, "mirror 3");
	RUN_TEST(BArrMirror(~0UL) == ~0UL, "mirror 4");
}

static void TestCountOn()
{
	RUN_TEST(BArrCountOn(16) == 1, "count on 1");
	RUN_TEST(BArrCountOn(37632451) == 14, "count on 2");
}

static void TestCountOff()
{
	RUN_TEST(BArrCountOff(37632451) == 50, "count off 1");
	RUN_TEST(BArrCountOff(1) == 63, "count off 2");
} 

static void TestRotateRight()
{
	RUN_TEST(BArrRotateRight(1, 1) ==  (size_t)1 << 63, "rotate right 1");
	RUN_TEST(BArrRotateRight(0, 12) == 0, "rotate right 2")								
}

static void TestRotateLeft()
{
	RUN_TEST(BArrRotateLeft(1, 3) == 8, "rotate Left 1");
	RUN_TEST(BArrRotateLeft(1, 65) == 2, "rotate left 2")	
}

int main()
{
	TestSetAll();
	TestResetAll();
	TestIsOn();
	TestIsOff();
	TestSetOn();
	TestSetOff();
	TestSetBit();
	TestFlip();
	TestToStr();
	TestMirror();
	TestCountOn();
	TestCountOff();
	TestRotateRight();
	TestRotateLeft();
	
	return 0;
}












