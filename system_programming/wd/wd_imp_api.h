#ifndef __WD_IMP_H__
#define __WD_IMP_H__

#include <pthread.h>

#include "wd.h"

#include "./../include/scheduler.h"

pid_t partner_pid;

struct WatchDog
{
	pthread_t app_thread;
	scheduler_t *sched;
};

wd_t *WDInit(init_status_t *status);

void *WDSchedulerRun(void *pack);

#endif