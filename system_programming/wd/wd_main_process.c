#include <unistd.h> /* getppid() */

#include "wd_imp.h"

#define UNUSED(x) (void)(x)

int main(int argc, char *argv[])
{
	wd_t *wd = NULL;
	status_t status = 0;

	UNUSED(argc);

	sem_self = sem_open("/sem_wd_ready", O_CREAT, SEM_PERMS, 0);
	if (SEM_FAILED == sem_self)
	{
		status = OS_FUNC_FAIL;

		return 1;
	}

	sem_partner = sem_open("/sem_app_ready", O_CREAT, SEM_PERMS, 0);
	if (SEM_FAILED == sem_partner)
	{
		status = OS_FUNC_FAIL;

		return 1;
	}

	partner_pid = getppid();
	wd = WDInit(&status);

	wd->my_filename = argv[0];
	wd->partner_filename = argv[1];

	WDSchedulerRun(wd);

	return 0;
}