#include <stdio.h>	/* printf() */
#include <stdlib.h> /* atoi() */
#include <assert.h> /* assert() */
#include <unistd.h> /* sleep() */

#include "wd.h" 	/* wd IMP */

int main(int argc, char *argv[])
{
	status_t status = SUCCESS;
	wd_t *wd = NULL;
	int time_to_sleep = 100;

	wd = WDStart(argv[0], &status);

	while(0 < time_to_sleep)
	{
		time_to_sleep = sleep(time_to_sleep);
	}

	WDStop(wd);

	printf("return status: %d\n", status);

	return 0;
}