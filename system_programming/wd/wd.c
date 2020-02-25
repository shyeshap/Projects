/************************************
 *				WD 					*
 *			Shye Shapira			*
 ************************************/

#include <pthread.h>	/* pthread_create() */
#include <unistd.h>		/* fork() excel() getppid() */
#include <assert.h>		/* assert() */
#include <time.h>		/* clock() */
#include <signal.h>		/* SIGUSR2, SIGTERM */

#include "scheduler.h"	/* scheduler IMP */
#include "wd_imp.h"		/* wd imp IMP */

sem_t *sem_is_wd_up;

wd_t *WDStart(const char *filename, status_t *status)
{
	wd_t *app_wd = NULL;
	pid_t wd_pid = 0;
	int sem_val = 0;

	assert(NULL != filename);
	assert(NULL != status);

	app_wd = WDInit(status);
	if (NULL == app_wd)
	{
		return NULL;
	}

	app_wd->my_filename = filename;
	app_wd->partner_filename = WD_PATH;
	
	sem_is_wd_up = sem_open("/sem_is_wd_up", O_CREAT, SEM_PERMS, 0);
	if (SEM_FAILED == sem_is_wd_up)
	{
		*status = OS_FUNC_FAIL;

		return NULL;
	}

	sem_self = sem_open("/sem_app_ready", O_CREAT, SEM_PERMS, 0);
	if (SEM_FAILED == sem_self)
	{
		*status = OS_FUNC_FAIL;
		
		sem_close(sem_is_wd_up);
		sem_unlink("/sem_is_wd_up");

		return NULL;
	}

	sem_partner = sem_open("/sem_wd_ready", O_CREAT, SEM_PERMS, 0);
	if (SEM_FAILED == sem_partner)
	{
		*status = OS_FUNC_FAIL;

		sem_close(sem_is_wd_up);
		sem_unlink("/sem_is_wd_up");
		sem_close(sem_self);
		sem_unlink("/sem_app_ready");

		return NULL;
	}

	if (0 != pthread_create(&app_wd->app_thread, NULL, WDSchedulerRun, app_wd))
	{
		*status = OS_FUNC_FAIL;

		sem_close(sem_is_wd_up);
		sem_unlink("/sem_is_wd_up");
		sem_close(sem_self);
		sem_unlink("/sem_app_ready");
		sem_close(sem_partner);
		sem_unlink("/sem_wd_ready");
	
		return NULL;
	}
	
	if (0 > sem_getvalue(sem_is_wd_up, &sem_val))
	{
		*status = OS_FUNC_FAIL;

		sem_close(sem_is_wd_up);
		sem_unlink("/sem_is_wd_up");
		sem_close(sem_self);
		sem_unlink("/sem_app_ready");
		sem_close(sem_partner);
		sem_unlink("/sem_wd_ready");

		return NULL;
	}

	if (0 == sem_val)
	{
		wd_pid = fork();
		if (0 > wd_pid)
		{
			*status = OS_FUNC_FAIL;

			sem_close(sem_is_wd_up);
			sem_unlink("/sem_is_wd_up");
			sem_close(sem_self);
			sem_unlink("/sem_app_ready");
			sem_close(sem_partner);
			sem_unlink("/sem_wd_ready");

			return app_wd;
		}

		else if (0 == wd_pid)
		{
			execl(WD_PATH, WD_PATH, filename, NULL);
		}

		partner_pid = wd_pid;

		if (0 > sem_post(sem_is_wd_up))
		{
			*status = OS_FUNC_FAIL;
			
			return NULL;
		}
	}

	else
	{
		partner_pid = getppid();
	}
	
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
			app_wd->status = OS_FUNC_FAIL;

			return;
		}
	}

	if (0 == sem_val)
	{
		if (0 != sem_post(sem_wd_received_stop_signal))
		{
			app_wd->status = OS_FUNC_FAIL;

			return;
		}

		kill(partner_pid, SIGTERM);
	}

	if (0 != sem_close(sem_is_wd_up))
	{
		app_wd->status = OS_FUNC_FAIL;

		return;
	}

	if (0 != sem_unlink("/sem_is_wd_up"))
	{
		app_wd->status = OS_FUNC_FAIL;

		return;
	}

	if (0 != pthread_join(app_wd->app_thread, NULL))
	{
		app_wd->status = OS_FUNC_FAIL;

		return;
	}
}

