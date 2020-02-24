#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <assert.h>
#include <time.h> /* clock() */
#include <signal.h> /* SIGUSR2, SIGTERM */

#include "/home/codezila/git/system_programming/include/scheduler.h"
#include "wd_imp.h"

wd_t *WDStart(const char *filename, init_status_t *status)
{
	wd_t *app_wd = NULL;
	pid_t wd_pid = 0;

	assert(NULL != filename);
	assert(NULL != status);

	app_wd = WDInit(status);
	
	sem_self = sem_open("/sem_app_ready", O_CREAT, SEM_PERMS, 0);
	if (SEM_FAILED == sem_self)
	{
		*status = SEM_FAIL;

		return NULL;
	}

	sem_partner = sem_open("/sem_wd_ready", O_CREAT, SEM_PERMS, 0);
	if (SEM_FAILED == sem_partner)
	{
		*status = SEM_FAIL;

		return NULL;
	}

	if (0 != pthread_create(&app_wd->app_thread, NULL, WDSchedulerRun, app_wd))
	{
		*status = PTHREAD_CREATE_FAIL;
		return app_wd;
	}

	wd_pid = fork();
	if (0 > wd_pid)
	{
		*status = FORK_FAIL;
		return app_wd;
	}

	else if (0 == wd_pid)
	{
		execl("./wd.out", "./wd.out", NULL);
	}

	partner_pid = wd_pid;
	
	return app_wd;
}

void WDStop(wd_t *app_wd)
{
	clock_t start = clock();
	int sem_val = 0;

	assert(NULL != app_wd);

	while (0 == sem_val &&
			1 > ((clock() - start) / CLOCKS_PER_SEC))
	{
		kill(partner_pid, SIGUSR2);
		if (0 > sem_getvalue(sem_wd_received_stop_signal, &sem_val))
		{

		}
	}

	if (0 == sem_val)
	{
		sem_post(sem_wd_received_stop_signal);
		kill(partner_pid, SIGTERM);
	}

	pthread_join(app_wd->app_thread, NULL);
}

