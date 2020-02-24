#include <stdio.h>
#include <unistd.h>

#include "wd.h"

int main()
{
	init_status_t status = SUCCESS;
	wd_t *wd = NULL;
	int time_to_sleep = 60;
	
	wd = WDStart("wd_test", &status);

	while(0 < time_to_sleep)
	{
		time_to_sleep = sleep(time_to_sleep);
	}

	WDStop(wd);

	return 0;
}