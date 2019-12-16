#include <stdio.h>
#include <stdlib.h>

#define SIZEOF_VAR(x) (char *)(&x + 1) - (char *)(&x)
#define SIZOF_TYPE(type) (size_t)(1 + (type *)0)

int main()
{ 
    double x;
 
	printf("%ld\n", SIZEOF_VAR(x)); 
 	printf("%ld\n", SIZOF_TYPE(double)); 
    
    return 0; 
} 
