/************************************************
*
* File: queue_test.c
* Ex: Queue data structure
* writer: Israel Drayfus
* Description: Run and test functions of Queue library.
*
*************************************************/

#include <stdlib.h> /*malloc()*/
#include <assert.h> /*assert()*/
#include <string.h> /*mamcpy*/
#include <stdio.h> /*printf()*/
#include "circularbuffer.h" /*typedef CBuffer*/

#define RED "\033[31m"
#define GREEN "\033[32m"
#define WHITE "\033[0m"

#define TEST(test, errMsg) if (test)\
						   {\
						      printf(GREEN);\
						      printf("%s\n", "SUCCESS");\
						   }\
						   else\
						   {\
						      printf(RED);\
						      printf("%s, %s\n", "FAILURE", errMsg);\
						   }\
						   printf(WHITE);

#define SIZE 10

typedef char BYTE;
typedef size_t WORD;

struct CBuffer
{
	size_t read_index;
	size_t size;
	size_t capacity;
	BYTE cbuffer[1];
};

int value = 1;
int int_test[] = {1,2,3};
char char_test[] = {'1','2','3','4','5','6','7','8','9'};
float float_test[] = {1.0,2.0,3.0};

int main()
{
	char char_buffer[10];
	
	cbuffer_t *cbuffer = CBufferCreate(SIZE);
	TEST(1 == CBufferIsEmpty(cbuffer), "CBufferIsEmpty(), empty buffer");
	TEST(SIZE == CBufferCapacity(cbuffer), "CBufferCapacity()");
	TEST(SIZE == CBufferFreeSpace(cbuffer), "CBufferFreeSpacey(), enpty buffer");
	
	CBufferWrite(cbuffer, char_test, 3); /* [1,2,3,-,-,-,-,-,-,-] */
	TEST(char_test[0] == cbuffer->cbuffer[0], "Write(), empty buffer 3 items");
	CBufferWrite(cbuffer, char_test, 3); /* [1,2,3,1,2,3,-,-,-,-] */
	TEST(char_test[0] == cbuffer->cbuffer[3], "Write(), items in buffer");
	CBufferWrite(cbuffer, char_test, 4); /* [1,2,3,1,2,3,1,2,3,4] */
	CBufferRead(cbuffer, char_buffer, 3); /* [-,-,-,1,2,3,1,2,3,4] */
	TEST(3 == cbuffer->read_index, "Read()");
	CBufferWrite(cbuffer, char_test, 3); /* [1,2,3,1,2,3,1,2,3,4] */
	TEST(char_test[0] == cbuffer->cbuffer[0], "Write(), write index + count > capacity");
	CBufferRead(cbuffer, char_buffer, 9);/* [-,-,3,-,-,-,-,-,-,-] */
	TEST(char_test[2] == cbuffer->cbuffer[2], "Read(), read index + count > capacity");
	TEST(char_test[0] == char_buffer[0], "Read(), char_buffer initialized");
	CBufferWrite(cbuffer, char_test, 9); /* [8,9,3,1,2,3,4,5,6,7] */
	CBufferRead(cbuffer, char_buffer, 8); /* [8,9,-,-,-,-,-,-,-,-] */
	TEST(10 == cbuffer->read_index, "Read(), exactly to capacity");
	CBufferRead(cbuffer, char_buffer, 2); /* [-,-,-,-,-,-,-,-,-,-] */
	TEST(char_test[8] == char_buffer[1], "Read(), read after exactly capacity");

	CBufferDestroy(cbuffer);
	
	return 0;
}
