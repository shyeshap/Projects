#include <stdio.h> /* printf() */

#define UNUSED(param) (void)param;

#define RED "\033[31m"
#define GREEN "\033[32m"
#define WHITE "\033[0m"
#define BLUE "\n\x1b[34m"
#define RESET "\033[0m\n"

#define TEST(test, Msg) if (test)\
						   {\
						      printf(GREEN "%s - %s" RESET, "SUCCESS", Msg);\
						   }\
						   else\
						   {\
						      printf(RED);\
						      printf(RED "%s, %s\n" RESET, "FAILURE", Msg);\
						   }\
						   printf(WHITE);		   
