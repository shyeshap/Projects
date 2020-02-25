#include <stdlib.h> /* malloc( ) */
#include <string.h> /* strcpy() */
#include <signal.h> /* sigaction() */
#include <assert.h> /* assert() */
#include <unistd.h> /* getpid() */

#include "wd_imp.h" /* wd_imp IMP */

#define UNUSED(x) (void)(x)
#define INTERVAL (1)

/************** IMP FUNCTIONS DECLARATION ****************/
static int SchedulerInit(wd_t *wd);
static int HandlersInit(wd_t *wd);
static void ImAliveHandler(int param);
static int TaskImAlive(void *wd);
static void IsPartnerAliveHndler(int sig);
static int TaskIsPartnerAlive(void *wd);
static void WDRBCleanUp(wd_t *wd);
/*********************************************************/

wd_t *WDInit(status_t *status)
{
	wd_t *wd = NULL;

	assert(NULL != status);

	wd = (wd_t *)malloc(sizeof(*wd)); 
	if (NULL == wd)
	{
		*status = MEMORY_ALLOC_FAIL;

		return NULL;
	}

	if (0 != HandlersInit(wd))
	{
		free(wd);
		wd = NULL;

		*status = OS_FUNC_FAIL;
	}

	if (0 != SchedulerInit(wd))
	{
		free(wd);
		wd = NULL;

		*status = MEMORY_ALLOC_FAIL;

		return NULL;
	}

	sem_wd_received_stop_signal = sem_open("/sem_wd_received_stop_signal", O_CREAT, SEM_PERMS, 0);
	if (SEM_FAILED == sem_wd_received_stop_signal)
	{
		SchedulerDestroy(wd->sched);

		free(wd);
		wd = NULL;

		*status = OS_FUNC_FAIL;

		return NULL;
	}

	return wd;
}

void *WDSchedulerRun(void *wd)
{
	int sem_val = 0; 

	assert(NULL != wd);

	while (0 == sem_val)
	{
		if (0 > sem_post(sem_partner))
		{
			((wd_t *)wd)->status = OS_FUNC_FAIL;

			return NULL;
		}

		if (0 > sem_wait(sem_self))
		{
			((wd_t *)wd)->status = OS_FUNC_FAIL;

			return NULL;
		}

		SchedulerRun(((wd_t *)wd)->sched);

		if (0 > sem_getvalue(sem_wd_received_stop_signal, &sem_val))
		{
			((wd_t *)wd)->status = OS_FUNC_FAIL;

			return NULL;
		}
	}

	WDRBCleanUp(((wd_t *)wd));

	return wd;
}

/******************** IMP FUNCTIONS ***********************/
static int SchedulerInit(wd_t *wd)
{
	ilrd_uid_t uid = {0};

	wd->sched = SchedulerCreate();
	if (NULL == wd->sched)
	{	
		return 1;
	}

	uid = SchedulerAddTask(wd->sched, TaskImAlive, INTERVAL, wd);
	if(UIDIsBad(uid))
	{
		SchedulerDestroy(wd->sched);

		return 1;
	}

	uid = SchedulerAddTask(wd->sched, TaskIsPartnerAlive, INTERVAL * 3, wd);
	if(UIDIsBad(uid))
	{
		SchedulerDestroy(wd->sched);
		
		return 1;
	}

	return 0;
}

static int HandlersInit(wd_t *wd)
{
	struct sigaction im_alive_sa = {0};
	struct sigaction is_partner_alive_sa = {0};

	im_alive_sa.sa_handler = ImAliveHandler;
	if (0 > sigaction(SIGUSR1, &im_alive_sa, NULL))
	{
		return 1;
	}

	is_partner_alive_sa.sa_handler = IsPartnerAliveHndler;
	if (0 > sigaction(SIGUSR2, &is_partner_alive_sa, NULL))
	{
		return 1;
	}

	return 0;
}

static void ImAliveHandler(int sig)
{
	UNUSED(sig);

	++is_alive;
}

static void IsPartnerAliveHndler(int sig)
{
	UNUSED(sig);

	if (0 != sem_post(sem_wd_received_stop_signal))
	{
		return;
	}
}

static int TaskImAlive(void *wd)
{
	int sem_val = 0;

	if (0 > sem_getvalue(sem_wd_received_stop_signal, &sem_val))
	{
		((wd_t *)wd)->status = OS_FUNC_FAIL;

		return 1;
	}

	if (0 < sem_val)
	{
		SchedulerStop(((wd_t *)wd)->sched);
	}

	kill(partner_pid, SIGUSR1);

	return 0;
}

static int TaskIsPartnerAlive(void *wd)
{
	pid_t resuscitated_process = 0;
	int sem_val = 0;

	if(0 > sem_getvalue(sem_wd_received_stop_signal, &sem_val))
	{
		((wd_t *)wd)->status = OS_FUNC_FAIL;

		return 1;
	}

	if (0 == is_alive && 0 == sem_val)
	{
		kill(partner_pid, SIGKILL);

		resuscitated_process = fork();
		if (0 > resuscitated_process)
		{
			((wd_t *)wd)->status = OS_FUNC_FAIL;

			return 1;
		}

		if (0 == resuscitated_process)
		{
			execl(((wd_t *)wd)->partner_filename, ((wd_t *)wd)->partner_filename, ((wd_t *)wd)->my_filename, NULL);
		}
		
		SchedulerStop(((wd_t *)wd)->sched);
		partner_pid = resuscitated_process;
	}

	is_alive = 0;

	return 0;
}

void WDRBCleanUp(wd_t *wd)
{
	SchedulerDestroy(wd->sched);

	if (0 != sem_close(sem_wd_received_stop_signal))
	{
		wd->status = OS_FUNC_FAIL;
	}

	if (0 != sem_unlink("/sem_wd_received_stop_signal"))
	{
		wd->status = OS_FUNC_FAIL;
	}

	if (0 != sem_close(sem_self))
	{
		wd->status = OS_FUNC_FAIL;
	}

	if (0 != sem_close(sem_partner))
	{
		wd->status = OS_FUNC_FAIL;
	}

	if (0 != sem_unlink("/sem_app_ready"))
	{
		wd->status = OS_FUNC_FAIL;
	}

	if (0 != sem_unlink("/sem_wd_ready"))
	{
		wd->status = OS_FUNC_FAIL;
	}

	free(wd);
	wd = NULL;
}