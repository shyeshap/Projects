#include <stdio.h>
#include <string.h>

#define GRN  "\x1B[32m"
#define RED  "\x1B[31m"
#define RESET "\x1B[0m"

int IsRotate(char *s1, char *s2)
{
	char *run1 = s1, *run2 = s2;
	unsigned int count = 0;
	if (strlen(s1) == strlen(s2))
	{
		while (*run1 != '\0')
		{
			run2 = s2;
			count = 0;
			while ((*run1 != *run2) && (*run2 != '\0'))
			{
				run2++;
			}
			if (*run2 == '\0')
			{
				break;
			}
			while ((*run1 == *run2) && (*run2 != '\0'))
			{
				run1++;
				run2++;
				count++;
			}
		}
		run1 = s1;
		if (strncmp(run1, run2, (strlen(s1) - count)) == 0)
		{
			return 1;
		}
	}
	return 0;
}

void test(int cond, const char *msg)
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
	char *a = "abc", *b = "efg", *c = "cab", *d = "12345", *e = "45123", 
	*f = "121234", *g = "123412";
	test(IsRotate(a, b) == 0, "simple test");
	test(IsRotate(a, c) == 1, "rotated simple test");
	test(IsRotate(d, e) == 1, "first given test");
	test(IsRotate(f, g) == 1, "second given test");
	test(IsRotate("1234", "12345") == 0, "different length");
	test(IsRotate("512345", "123455") == 1, "different length");
	test(IsRotate("121234", "123413") == 0, "different length");
	return 0;
}
