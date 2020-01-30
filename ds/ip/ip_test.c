#include <stdio.h> /* printf() */
#include <stdlib.h> /*malloc() */
#include "ip.h"

#define RED "\033[31m"
#define GREEN "\033[32m"
#define WHITE "\033[0m"
#define BLUE printf("\x1b[34m")
#define RESET printf("\033[0m")

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

void TestIp()
{
	unsigned char ip[4] = {1,5,2,7};
	unsigned char *ip_buffer = (unsigned char *)malloc(40);

	IPConvertAddress(ip, ip_buffer);

	printf("%s\n", ip_buffer);

	free(ip_buffer);
}

int main()
{
	TestIp();

	return 0;
}