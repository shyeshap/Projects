/********************************/
/*			SCHEDULER			*/
/*								*/
/*			SHYE SHAPIRA		*/
/*			17/12/19			*/
/********************************/

#include <stdio.h>			/* sizeof() */
#include <assert.h>			/* assert */ 
#include <stdlib.h>			/* malloc */
#include <unistd.h> 		/* sleep */ 

#include "/home/codezila/git/ds/include/priorityq.h" /* priority queue API */
#include "/home/codezila/git/system_programming/include/uid.h"	/* UID API */
#include "/home/codezila/git/system_programming/include/task.h"	/*Task Functions*/
#include "/home/codezila/git/system_programming/include/scheduler.h" /* scheduler API */

#define UNUSED(x) (void)(x)
#define FREE(ptr) free(ptr); ptr = NULL;

enum flag_status
{
	OFF,
	ON
};

struct Scheduler
{
	pq_t *queue;
	int remove_current_flag;
	int stop_flag;
	task_t *current_task;
};

static int time_cmpr(void *task1, void *task2, void *param)
{
	assert(NULL != task1);
	assert(NULL != task2);
	
	UNUSED(param);
	
	return (TaskGetTimeToRun(task2) - TaskGetTimeToRun(task1));
}

static int UIDIsSameWrap(void *task, void *uid)
{
	return UIDIsSame(TaskGetUid(task), *(ilrd_uid_t *)uid);
}

scheduler_t *SchedulerCreate()
{
	scheduler_t *new_sched = (scheduler_t *)malloc(sizeof(scheduler_t));
	if (NULL == new_sched)
	{
		return NULL;
	}
	
	new_sched->queue = PQCreate(&time_cmpr, NULL);

	if (NULL == new_sched->queue)
	{
		FREE(new_sched);
		return NULL;
	}

	new_sched->remove_current_flag = OFF;
	new_sched->stop_flag = OFF;
	new_sched->current_task = NULL;
	
	return new_sched;
}

void SchedulerDestroy(scheduler_t *s)
{
	assert(NULL != s);
	
	while (!SchedulerIsEmpty(s))
	{
		TaskDestroy(PQDequeue(s->queue));
	}
	
	PQDestroy(s->queue);
	FREE(s);
}

ilrd_uid_t SchedulerAddTask(scheduler_t *s, task_func_t to_do, time_t interval, void *param)
{
	ilrd_uid_t bad_uid = {0};
	task_t *new_task = TaskCreate(to_do, interval, param);;
	 
	assert(NULL != s);
	
	if (NULL != new_task)
	{
		if (1 == PQEnqueue(s->queue, new_task))
		{
			FREE(new_task);
			return bad_uid;
		}
	}
	
	return new_task->uid;
}

void SchedulerRemoveTask(scheduler_t *s, ilrd_uid_t uid)
{
	task_t *remove = NULL;

	if (NULL == s->current_task || !UIDIsSame(uid, TaskGetUid(s->current_task)))
	{
		remove = ((task_t *)PQErase(s->queue, &UIDIsSameWrap, &uid));
		if (NULL != remove)
		{
			TaskDestroy(remove);
		}
	}
	
	else
	{
		s->remove_current_flag = ON;
	}
}

void SchedulerRun(scheduler_t *s)
{
	task_t *task = NULL;
	int task_run = 0;
	
	assert(NULL != s);
		
	s->stop_flag = OFF;
	
	while (s->stop_flag == OFF)
	{
		task = (task_t *)PQDequeue(s->queue);
		s->current_task = task;
		
		if (time(NULL) < TaskGetTimeToRun(task))
		{
			while (sleep(TaskGetTimeToRun(task) - time(NULL)));
		}
		
		task_run = TaskRun(task);
		
		if (s->remove_current_flag == OFF && task_run == 0)
		{
			TaskUpdateTimeToRun(task);
			PQEnqueue(s->queue, task);
		}
		else
		{
			TaskDestroy(s->current_task);
			s->remove_current_flag = OFF;
		}
	}
}

void SchedulerStop(scheduler_t *s)
{
	assert(NULL != s);
	
	s->stop_flag = ON;
}

size_t SchedulerSize(const scheduler_t *s)
{
	assert(NULL != s);
	
	return PQSize(s->queue);
}

int SchedulerIsEmpty(const scheduler_t *s)
{
	assert(NULL != s);
	
	return PQIsEmpty(s->queue);
}

void SchedulerClear(scheduler_t *s)
{
	while (!SchedulerIsEmpty(s))
	{
		TaskDestroy(PQDequeue(s->queue));
	}
}
