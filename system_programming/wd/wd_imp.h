#ifndef __WD_IMP_H__
#define __WD_IMP_H__

#include <pthread.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>

#include "wd.h"

#include "./../include/scheduler.h"

#define SEM_PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)

pid_t partner_pid;
int is_alive;
sem_t *sem_wd_received_stop_signal;
sem_t *sem_self;
sem_t *sem_partner;

struct WatchDog
{
	pthread_t app_thread;
	scheduler_t *sched;
};

/* 
* creation and initiation of all structures needed for wd implementation:
* scheduler, tasks, sigactions
* receive address of status type.
* returns address of wd_t type initiated on success
* on faileure returns NULL and status is set appropriately 
*/
wd_t *WDInit(init_status_t *status);

/*
* 
*/
void *WDSchedulerRun(void *pack);

#endif