/**************Logger****************
 *			Shye Shapira			*
 *			Reviewr: Ben			*
 ************************************/

#include <stdio.h>
#include "Logger.h"


int main()
{

char file[MAX_FILE_LEN];
match arr[ELEMEN_NUM];

InitializArr(arr);

printf("plesae enter file's full name:\n");
scanf("%s%*c", file);

InfraStruct(file, arr);

return 0;
}


