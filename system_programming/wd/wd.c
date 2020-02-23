#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <assert.h>

#include "/home/codezila/git/system_programming/include/scheduler.h"
#include "wd_imp_api.h"

wd_t *WDStart(const char *filename, init_status_t *status)
{
	wd_t *wd = {0};
	pid_t wd_pid = 0;

	wd_pid = fork();
	if (0 > wd_pid)
	{
		*status = FORK_FAIL;
		return wd;
	}

	if (0 == wd_pid)
	{
		printf("wd- %d\n", getpid());
		execl("./wd.out", "./wd.out", NULL);
	}
	printf("app- %d\n", getpid());

	partner_pid = wd_pid;

	printf("father2\n");
	wd = WDInit(status);
	assert(NULL != wd->sched);

	printf("yalla\n");

	if (0 != pthread_create(&wd->app_thread, NULL, WDSchedulerRun, wd->sched))
	{
		printf("pthread_fail");
	}
	
	return wd;
}

void WDStop(wd_t *wd)
{
	pthread_join(wd->app_thread, NULL);
}

