/*********************************/
/*                               */
/*    Work Sheet 9               */       
/*    Author: 	Shye Shapira	 */
/*    Reviewer: 		         */
/*    Date:   	23/11/2019       */
/*                               */
/*********************************/

#ifndef _mem_h
#define _mem_h

#define GRN  "\x1B[32m"
#define RED  "\x1B[31m"
#define RESET "\x1B[0m"

#define IS_LITTLE_ENDIAN(x) ((*(char *)(&x)) == (x & 0xFF))

typedef struct ascii
{
	char c;
	int status;
} ascii_t;

void *MyMemset(void *ptr, int x, size_t n);
void *MyMemcpy(void *dst, const void *src, size_t n);
void *MyMemmove(void *dst, const void *src, size_t num);

char *ItoAby10(int num, char *str);
char *ItoAAnyBase(int num, char *str, int base);
int AtoIby10(const char *nptr);
int AtoIAnyBase(const char *nptr, int base);

void CmpThreeArr(char *arr1, int len1, char *arr2, int len2, char *arr3, int len3);
int IsLittleEndian();

#endif
