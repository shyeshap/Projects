/*********************************/
/*                               */
/*    Work Sheet 9               */       
/*    Author: 	Shye Shapira	 */
/*    Reviewer: 		         */
/*    Date:   	23/11/2019       */
/*                               */
/*********************************/

#include "mem.h"



void Test(int cond, const char *msg)
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
	int x = 4660;
    
    char arr1[4] = {'a', 'g', 'b', 'c'};
    char arr2[6] = {'a', 'c', 'b', 'l', 's', 'h'};
    char arr3[5] = {'b', 'c', 'm', 'r', 'd'};
    
    char *str1, *str2, *str3, *str4, *str5, *str6, *str7, *str8;
    
    str1 = (char*) malloc(31);
    str2 = (char*) malloc(12);
    str3 = (char*) malloc(16);
    str4 = (char*) malloc(11);
    str5 = (char*) malloc(11);
    str7 = (char*) malloc(8);
    str8 = (char*) malloc(13);    
    
    strcpy(str1, "abcdefghijklmnopqrstuvwxyz");
    strcpy(str2, "hello world");
    strcpy(str3, "abcdefghijklmno");
    strcpy(str4, "0123456789");
    strcpy(str5, "0123456789");
    str6 = str3 + 5;
    strcpy(str7, "abcd"); 
    strcpy(str8, "abc");
    
    printf("Check 3 Arrays: ");
    CmpThreeArr(arr1, 4, arr2, 6, arr3, 5);
 
    Test(0 == strcmp((char *)MyMemset(str1, 65, 25) ,(char *)MyMemset(str1, 65, 25)), "memset");
    Test(0 == strcmp((char*)MyMemcpy(str8, str7, 4) ,(char*)memcpy(str8, str7, 4)), "memcpy");
    Test(0 == strcmp((char*)MyMemmove(str6, str3, 8) ,(char*)memmove(str6, str3, 8)), "memmove");
   
    Test(0 == strcmp("-123", ItoAby10(-123 ,str4)), "itoa 10");  
    Test((1653621 == AtoIby10("1653621")), "atoi 10");;
    Test(0 == strcmp("1G", ItoAAnyBase(52, str5, 36)), "itoa");  
    Test((52 == AtoIAnyBase("1G", 36)), "atoi");
    
    printf("Macro: ");
    if (1 == IS_LITTLE_ENDIAN(x))   
    {
        printf("\033[0;32m"); 
        printf("Little Endian System\n");
    }
    else
    {
        printf("\033[0;32m"); 
        printf("Big Endian System\n");
    }
    
    printf("\033[0m"); 
    
    printf("Function: ");
    if (1 == IsLittleEndian())   
    {
        printf("\033[0;32m"); 
        printf("Little Endian System\n");
    }
    else
    {
        printf("\033[0;32m"); 
        printf("Big Endian System\n");
    }
    
    printf("\033[0m"); 
    
    free(str1);
    free(str2);
    free(str3);
    free(str4);
    free(str5);
    free(str7);
    free(str8);
	
	return 0;
}
