#include <unistd.h>
#include <stdio.h>
#include <assert.h>

#include "wd_imp.h"

int main (int argc, char *argv[])
{
	wd_t *wd = NULL;
	init_status_t stat = 0;

	sem_self = sem_open("/sem_wd_ready", O_CREAT, SEM_PERMS, 0);
	if (SEM_FAILED == sem_self)
	{
		/**status = SEM_FAIL;*/
		printf("sem open 1 fail\n");
		return 1;
	}

	sem_partner = sem_open("/sem_app_ready", O_CREAT, SEM_PERMS, 0);
	if (SEM_FAILED == sem_partner)
	{
		/**status = SEM_FAIL;*/
		printf("sem open 2 fail\n");
		return 1;
	}

	partner_pid = getppid();
	wd = WDInit(&stat);
	WDSchedulerRun(wd);

	return 0;
}