#include <stdio.h> 	/* sizeof() */
#include <assert.h>	/* assert */ 
#include <stdlib.h>	/* malloc */ 
#include <time.h> 	/* time_t */

#include "task.h"	/* task API */
#include "uid.h"	/* UID API */

#define UNUSED(x) (void)(x)
#define FREE(ptr) free(ptr); ptr = NULL;

task_t *TaskCreate(task_func_t to_do, time_t interval, void *param)
{
	task_t *new_task = (task_t *)malloc(sizeof(task_t));
	if (NULL != new_task)
	{
		new_task->uid = UIDCreate();
		if (1 == UIDIsBad(new_task->uid))
		{
			FREE(new_task);
			return NULL;
		}
		
		new_task->task_func = to_do;
		new_task->run_time = time(NULL) + interval;
		new_task->interval = interval;
		new_task->param = param;
	}
	return new_task;
}

void TaskDestroy(task_t *t)
{
	assert(NULL != t);
	
	FREE(t);
}

ilrd_uid_t TaskGetUid(task_t *t)
{
	assert(NULL != t);
	
	return t->uid;
}

int TaskIsMatch(const task_t *t1, const task_t *t2)
{
	assert(NULL != t1);
	assert(NULL != t2);
	
	return (UIDIsSame(t1->uid, t2->uid) &&
			t1->task_func == t2->task_func &&
			t1->interval == t2->interval &&
			t1->param == t2->param);
}

time_t TaskGetTimeToRun(const task_t *t)
{
	assert(NULL != t);
	
	return t->run_time;
}

int TaskRun(const task_t *t)
{
	assert(NULL != t);
	
	return t->task_func(t->param);
}

void TaskUpdateTimeToRun(task_t *t)
{
	t->run_time += t->interval;
}
