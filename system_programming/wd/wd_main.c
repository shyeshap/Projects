#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include "wd_imp_api.h"

int main (int argc, char *argv[])
{
	wd_t *app_wd = NULL;

	init_status_t stat = 0;

	partner_pid = getppid();
	printf("yosav\n");

	app_wd = WDInit(&stat);
	assert(NULL != app_wd->sched);
	WDSchedulerRun(app_wd->sched);

	return 0;
}