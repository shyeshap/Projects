
#include <mystring.h>


size_t mystrLen(const char *s);
int MyStrCmp(const char *s1, const char *s2);
char *MyStrCpy(char *dest, const char *src);

int main()
{
	char s[] = "Hello world";
	printf("the length of %s is %ld\n\n", s,mystrLen(s));
	

	/*test*/
	char s1[] = "ac";
	char s2[] = "A";
	char s3[] = "";
	char s4[] = "achg";
	printf("%d\n", strcmp(s1, s4));
	printf("%d\n", strcmp(s1, s2));
	printf("%d\n\n", strcmp(s2, s1));
	
	printf("%d\n", MyStrCmp(s1, s4));
	printf("%d\n", MyStrCmp(s1, s2));
	printf("%d\n\n", MyStrCmp(s2, s1));
	
	printf("%s\n", strcpy(s1, s2));
	printf("%s\n", strcpy(s1, s3));
	printf("%s\n\n", strcpy(s1, s4));

	printf("%s\n", MyStrCpy(s1, s2));
	printf("%s\n", MyStrCpy(s1, s3));
	printf("%s\n", MyStrCpy(s1, s4));
	
	
	
	return 0;
}
