#include <stdio.h> /* printf() */
#include <unistd.h> /* sleep() */ 
#include <stdlib.h> /* malloc( ) */
#include <signal.h>
#include <assert.h>

#include "wd_imp.h"

/************** IMP FUNCTIONS DECLARATION ****************/
static void ImAliveHandler(int param);
static int TaskImAlive(void *wd);
static void IsPartnerAliveHndler(int sig);
static int TaskIsPartnerAlive(void *wd);
static void WDRBCleanUp(wd_t *wd);

/*********************************************************/

wd_t *WDInit(init_status_t *status)
{
	wd_t *wd = NULL;
	ilrd_uid_t uid = {0};
	struct sigaction im_alive_sa = {0};
	struct sigaction is_partner_alive_sa = {0};

	assert(NULL != status);

	wd = (wd_t *)malloc(sizeof(*wd)); 
	if (NULL == wd)
	{
		*status = MEMORY_ALLOC_FAIL;

		return NULL;
	}

	im_alive_sa.sa_handler = ImAliveHandler;
	if (0 > sigaction(SIGUSR1, &im_alive_sa, NULL))
	{
		free(wd);
		wd = NULL;

		*status = SIGACTION_FAIL;

		return NULL;
	}

	is_partner_alive_sa.sa_handler = IsPartnerAliveHndler;
	if (0 > sigaction(SIGUSR1, &im_alive_sa, NULL))
	{
		free(wd);
		wd = NULL;

		*status = SIGACTION_FAIL;

		return NULL;
	}

	wd->sched = SchedulerCreate();
	if (NULL == wd->sched)
	{	
		free(wd);
		wd = NULL;

		*status = MEMORY_ALLOC_FAIL;

		return NULL;
	}

	uid = SchedulerAddTask(wd->sched, TaskImAlive, 1, wd);
	if(UIDIsBad(uid))
	{
		free(wd);
		wd = NULL;

		SchedulerDestroy(wd->sched);

		*status = MEMORY_ALLOC_FAIL;

		return NULL;
	}

	uid = SchedulerAddTask(wd->sched, TaskIsPartnerAlive, 3, wd);
	if(UIDIsBad(uid))
	{
		free(wd);
		wd = NULL;

		SchedulerDestroy(wd->sched);
		*status = MEMORY_ALLOC_FAIL;

		return NULL;
	}

	sem_wd_received_stop_signal = sem_open("/sem_wd_received_stop_signal", O_CREAT, SEM_PERMS, 0);
	if (SEM_FAILED == sem_wd_received_stop_signal)
	{
		*status = SEM_FAIL;

		return NULL;
	}

	return wd;
}

void *WDSchedulerRun(void *wd)
{
	assert(NULL != wd);

	if (0 > sem_post(sem_partner))
	{
		printf("sem no post\n");
	}

	if (0 > sem_wait(sem_self))
	{
		printf("sem no wait\n");
	}
	
	SchedulerRun(((wd_t *)wd)->sched);

	WDRBCleanUp(((wd_t *)wd));
}

/******************** IMP FUNCTIONS ***********************/
static void ImAliveHandler(int sig)
{
	++is_alive;
}

static void IsPartnerAliveHndler(int sig)
{
	sem_post(sem_wd_received_stop_signal);
}

static int TaskImAlive(void *wd)
{
	int sem_val = 0;

	printf("Im alive: my-%d partner%d\n", getpid(), partner_pid);
	
	if (0 > sem_getvalue(sem_wd_received_stop_signal, &sem_val))
	{
		/* error */
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

	printf("*Is Alive: my-%d partner%d\n", getpid(), partner_pid);

	if(0 > sem_getvalue(sem_wd_received_stop_signal, &sem_val))
	{
		/* error */
	}

	if (0 == is_alive && 0 == sem_val)
	{
		resuscitated_process = fork();
		if (0 > resuscitated_process)
		{
			/*(*(init_status_t *)param) = FORK_FAIL;*/
		}

		if (0 < resuscitated_process)
		{
			execl("./wd.out", "./wd.out", NULL);
		}

		partner_pid = resuscitated_process;
	}

	is_alive = 0;

	return 0;
}

void WDRBCleanUp(wd_t *wd)
{
	SchedulerDestroy(wd->sched);

	sem_close(sem_wd_received_stop_signal);
	sem_unlink("/sem_wd_received_stop_signal");
	/*sem_close(sem_self)*/
	/*sem_unlink(sem_self)*/

	free(wd);
	wd = NULL;
}