#include <stdio.h> /* printf() */
#include <unistd.h> /* sleep() */ 
#include <stdlib.h> /* malloc( ) */
#include <signal.h>
#include <assert.h>

#include "wd_imp_api.h"

static void ImAliveHandler(int param)
{
	write (1, "hi\n", 3);
}

static int TaskImAlive(void *wd)
{
	printf("my-%d partner%d\n", getpid(), partner_pid);
	kill(partner_pid, SIGUSR1);
}

wd_t *WDInit(init_status_t *status)
{
	ilrd_uid_t uid = {0};
	struct sigaction im_alive_sa;

	wd_t *wd = malloc(sizeof(*wd)); 
	if (NULL == wd)
	{
		return NULL;
	}

	im_alive_sa.sa_flags = SA_SIGINFO;
	sigemptyset(&im_alive_sa.sa_mask);
	im_alive_sa.sa_handler = ImAliveHandler;
	
	if (SIGACTION_FAIL == sigaction(SIGUSR1, &im_alive_sa, NULL))
	{
		*status = SIGACTION_FAIL;
		return NULL;
	}

	wd->sched = SchedulerCreate();
	if (NULL == wd->sched)
	{	
		*status = MEMORY_ALLOC_FAIL;

		return NULL;
	}

	uid = SchedulerAddTask(wd->sched, &TaskImAlive, 1, wd);
	printf("here?\n");
	if(UIDIsBad(uid))
	{
		printf("predestr\n");

		SchedulerDestroy(wd->sched);

		*status = MEMORY_ALLOC_FAIL;

		return NULL;
	}
	printf("here? ...   \n");

	assert(NULL != wd->sched);
	return wd;
}

void *WDSchedulerRun(void *pack)
{
	sleep(1);

	SchedulerRun(pack);
}