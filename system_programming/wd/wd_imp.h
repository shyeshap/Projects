#ifndef __WD_IMP_H__
#define __WD_IMP_H__

#include <pthread.h>	/* pthread_t */
#include <fcntl.h>      /* For O_* constants */
#include <sys/stat.h>   /* For mode constants */
#include <semaphore.h>	/* sem_t */

#include "scheduler.h"	/* scheduler API */
#include "wd.h"			/* wd API */

#define SEM_PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)

/**********globals**********/
pid_t partner_pid;
int is_alive;
sem_t *sem_wd_received_stop_signal;
sem_t *sem_self;
sem_t *sem_partner;
/****************************/

struct WatchDog
{
	pthread_t app_thread;
	scheduler_t *sched;
	const char *my_filename;
	const char *partner_filename;
	status_t status;
};

/* 
* creation and initiation of all structures needed for wd implementation:
* scheduler, tasks, sigactions
* receive address of status type.
* returns address of wd_t type initiated on success
* on faileure returns NULL and status is set appropriately 
*/
wd_t *WDInit(status_t *status);

/*
* 
*/
void *WDSchedulerRun(void *pack);

#endif