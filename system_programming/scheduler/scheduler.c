#include <stdio.h> /* sizeof() */
#include <assert.h> /* assert */ 
#include <stdlib.h>	/* malloc */
#include <unistd.h> /* sleep */ 
#include "scheduler.h" /* scheduler API */
#include "priorityqueue.h" /* priority queue API */
#include "uid.h" /* UID API */
#include "task.h"	/*Task Functions*/

#define UNUSED(x) (void)(x)
#define FREE(ptr) free(ptr); ptr = NULL;

enum flag_status
{
	OFF,
	ON
};

int time_cmpr(void *task1, void *task2, void *param)
{
	assert(NULL != task1);
	assert(NULL != task2);
	
	UNUSED(param);
	
	return (int)(TaskGetTimeToRun(task2) - TaskGetTimeToRun(task1));
}

int UIDIsSameWrap(void *task, void *uid)
{
	return UIDIsSame(TaskGetUid(task), *(ilrd_uid_t *)uid);
}

struct Scheduler
{
	pq_t *queue;
	int remove_current_flag;
	int stop_flag;
	task_t *current_task;
};

scheduler_t *SchedulerCreate()
{
	scheduler_t *new_sched = (scheduler_t *)malloc(sizeof(scheduler_t));
	if (NULL == new_sched)
	{
		return NULL;
	}
	
	new_sched->queue = PQCreate(&time_cmpr, NULL);
	{
		if (NULL == new_sched->queue)
		{
			FREE(new_sched);
			return NULL;
		}
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
}

ilrd_uid_t SchedulerAddTask(scheduler_t *s, task_func_t to_do, time_t interval, void *param)
{
	ilrd_uid_t bad_uid = {0};
	task_t *new_task = NULL;
	 
	assert(NULL != s);
	
	new_task = TaskCreate(to_do, interval, param);
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
	if (NULL == s->current_task || !UIDIsSame(uid, TaskGetUid(s->current_task)))
	{
		TaskDestroy((task_t *)PQErase(s->queue, &UIDIsSameWrap, &uid));
	}
	else
	{
		TaskDestroy(s->current_task);
		s->remove_current_flag = ON;
	}
}

void SchedulerRun(scheduler_t *s)
{
	task_t *task = NULL;
	time_t task_run_time = 0;
	int task_run = 0;
	size_t time_left = time(NULL) - task_run_time;
	
	s->stop_flag = OFF;
	
	assert(NULL != s);
	
	while (s->stop_flag == OFF)
	{
		task = (task_t *)PQDequeue(s->queue);
		s->current_task = task;
		task_run_time = TaskGetTimeToRun(task);
		
		if (time(NULL) > task_run_time)
		{
			while(time_left)
			{
				time_left = sleep(time(NULL) - task_run_time);
			}
		}
		
		task_run = TaskRun(task);
		
		if (s->remove_current_flag == OFF && task_run == 0)
		{
			TaskUpdateTimeToRun(task);
			PQEnqueue(s->queue, task);
		}
		else
		{
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
	
	if (NULL != s->current_task)
	{
		TaskDestroy(s->current_task);
	}
	
	s->remove_current_flag = ON;
}
