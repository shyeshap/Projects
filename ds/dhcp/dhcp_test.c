#include <stdio.h> /* printf() */

#include "dhcp.h"

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

void TestDhcpCreate()
{
	ip_t sub = {7,4,3,0};
	dhcp_t *dhcp = DhcpCreate(sub, 24);
	TEST(253 == DhcpCountFree(dhcp), "free leafs = 253");

	DhcpFreeIp(dhcp, sub);
	TEST(254 == DhcpCountFree(dhcp), "free leafs = 254");

	DhcpDestroy(dhcp);
}

void TestDhcpAlloc()
{
	ip_t sub = {7,4,3,0};
	ip_t requested = {7,4,3,5}, requested2 = {0,0,0,0}, requested3 = {0,0,3,255};
	ip_t alloc = {0,0,0,0};
	dhcp_t *dhcp = DhcpCreate(sub, 22);
	TEST(1021 == DhcpCountFree(dhcp), "free leafs = 1021");

	TEST(0 == DhcpAllocIp(dhcp, requested, alloc), "as requested");
	TEST(requested[2] == alloc[2], "2");
	TEST(requested[3] == alloc[3], "3");

	TEST(1 == DhcpAllocIp(dhcp, requested2, alloc), "not as requested");
	TEST(0 == alloc[2], "2");
	TEST(1 == alloc[3], "3");

	TEST(1 == DhcpAllocIp(dhcp, requested2, alloc), "not as requested");
	TEST(0 == alloc[2], "2");
	TEST(2 == alloc[3], "3");

	TEST(1 == DhcpAllocIp(dhcp, requested3, alloc), "not as requested");
	TEST(0 == alloc[2], "2");
	TEST(3 == alloc[3], "3");

	DhcpDestroy(dhcp);
}

int main()
{
	TestDhcpCreate();
	TestDhcpAlloc();

	return 0;
}