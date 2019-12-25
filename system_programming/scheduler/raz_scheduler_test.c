#include <stdio.h>/*printf()*/
#include <unistd.h> /*sleep()*/
#include <stdlib.h>

#include "../include/scheduler.h"

#define RUN_TEST(test, errmsg)\
							{\
								if(test)\
								{\
									printf("SUCCESS\n");\
								}\
								else\
								{\
									printf("\033[1;31m");\
									printf("%s \n", errmsg);\
									printf("\033[0m");\
								}\
							}

#define UNUSED(x) (void)(x)
#define FREE(ptr) free(ptr); ptr = NULL;

typedef struct Remove
{
	scheduler_t *s;
	ilrd_uid_t uid;
}remove_t;

static int ToDo1Sec(void *data)
{
	printf("Every 1 Seconds \n");
	UNUSED(data);
	return 0;
}

static int ToDo5Sec(void *data)
{
	printf("Every 5 Seconds \n");
	UNUSED(data);
	return 0;
}

static int StopScheduler(void *data)
{
	SchedulerStop(data);
	return 0;
}

static int Remove(void *data)
{
	remove_t *NewRemove = (remove_t*)data;
	SchedulerRemoveTask(NewRemove->s,NewRemove->uid);

	return 0;
}


void TestSchedulerCreate()
{
	scheduler_t *newScheduler = SchedulerCreate();
	RUN_TEST(0 == SchedulerSize(newScheduler), "FAIL: WRONG CREATE SIZE (0)");
	RUN_TEST(1 == SchedulerIsEmpty(newScheduler), "FAIL: WRONG CREATE SIZE (0)");

	SchedulerDestroy(newScheduler);
	printf("\n");
	
}

void TestSchedulerAddTask()
{
	scheduler_t *newScheduler = SchedulerCreate();
	RUN_TEST(0 == SchedulerSize(newScheduler), "FAIL: WRONG CREATE SIZE (0)");
	RUN_TEST(1 == SchedulerIsEmpty(newScheduler), "FAIL: WRONG CREATE SIZE (0)");
	SchedulerAddTask(newScheduler, &ToDo1Sec,1, NULL);
	RUN_TEST(1 == SchedulerSize(newScheduler), "FAIL: WRONG CREATE SIZE (0)");
	RUN_TEST(0 == SchedulerIsEmpty(newScheduler), "FAIL: WRONG CREATE SIZE (0)");
	SchedulerAddTask(newScheduler, &ToDo5Sec,5, NULL);
	RUN_TEST(2 == SchedulerSize(newScheduler), "FAIL: WRONG SIZE (2)");

	SchedulerDestroy(newScheduler);
	printf("\n");
	
}

void TestSchedulerRemoveItsSelf()
{
	
	scheduler_t *newScheduler = SchedulerCreate();
	ilrd_uid_t newUid;

	
	remove_t NewRemove;
	NewRemove.s =  newScheduler;

free(NULL);
	printf ("HIIIIIIIII");
	RUN_TEST(0 == SchedulerSize(newScheduler), "FAIL: WRONG CREATE SIZE (0)");
	RUN_TEST(1 == SchedulerIsEmpty(newScheduler), "FAIL: WRONG IS EMPTY (1)");
	
	SchedulerAddTask(newScheduler, &ToDo1Sec,1, NULL);
	SchedulerAddTask(newScheduler, &ToDo5Sec,5, NULL);

	RUN_TEST(0 == SchedulerIsEmpty(newScheduler), "FAIL: WRONG IS EMPTY (1)");
	RUN_TEST(2 == SchedulerSize(newScheduler), "FAIL: WRONG CREATE SIZE (2)");

	newUid = SchedulerAddTask(newScheduler, &Remove, 5, &NewRemove);
	NewRemove.uid = newUid;

	SchedulerAddTask(newScheduler, &StopScheduler,6, newScheduler);
	RUN_TEST(4 == SchedulerSize(newScheduler), "FAIL: WRONG CREATE SIZE (4)");
	SchedulerRun(newScheduler);
	RUN_TEST(3 == SchedulerSize(newScheduler), "FAIL: WRONG CREATE SIZE (3)");
	SchedulerRun(newScheduler);

	SchedulerDestroy(newScheduler);
	printf("\n");
}

void TestSchedulerRemoveTask()
{
	scheduler_t *newScheduler = SchedulerCreate();
	ilrd_uid_t uid1;

	remove_t NewRemove;
	NewRemove.s =  newScheduler;

	uid1= SchedulerAddTask(newScheduler, &ToDo1Sec,1, NULL);
	SchedulerRemoveTask(newScheduler, uid1);
	NewRemove.uid = SchedulerAddTask(newScheduler, &ToDo5Sec,5, NULL);
	
	SchedulerAddTask(newScheduler, &Remove, 3, &NewRemove);
	SchedulerAddTask(newScheduler, &StopScheduler,4, newScheduler);

	SchedulerRun(newScheduler);
	RUN_TEST(2 == SchedulerSize(newScheduler), "FAIL: WRONG CREATE SIZE (0)");
	SchedulerRun(newScheduler);

	SchedulerDestroy(newScheduler);
	printf("\n");
}

void TestSchedulerClear()
{
	scheduler_t *newScheduler = SchedulerCreate();
	SchedulerAddTask(newScheduler, &ToDo1Sec,1, NULL);
	SchedulerAddTask(newScheduler, &ToDo5Sec,5, NULL);
	SchedulerClear(newScheduler);
	RUN_TEST(1 == SchedulerIsEmpty(newScheduler), "FAIL: EMPTY AFTER CLEAR (1)");
	RUN_TEST(0 == SchedulerSize(newScheduler), "FAIL: WRONG CREATE SIZE (0)");

	SchedulerDestroy(newScheduler);
	printf("\n");

}

void TestSchedulerRun()
{
	scheduler_t *newScheduler = SchedulerCreate();
	SchedulerAddTask(newScheduler, &ToDo5Sec,5, NULL);
	SchedulerAddTask(newScheduler, &ToDo1Sec,1, NULL);
	SchedulerAddTask(newScheduler, &StopScheduler,10, newScheduler);

	RUN_TEST(3 == SchedulerSize(newScheduler), "FAIL: WRONG CREATE SIZE (0)");

	SchedulerRun(newScheduler);
	SchedulerRun(newScheduler);

	SchedulerDestroy(newScheduler);
	printf("\n");

}

int main(int argc, char const *argv[])
{	
	printf("TestSchedulerCreate()\n");
	TestSchedulerCreate();

	printf("TestSchedulerAddTask()\n");
	TestSchedulerAddTask();

	printf("TestSchedulerRemoveItsSelf()\n");
	TestSchedulerRemoveItsSelf();

	printf("TestSchedulerRemoveTask()\n");
	TestSchedulerRemoveTask();

	printf("TestSchedulerRun()\n");
	TestSchedulerRun();

	printf("TestSchedulerClear()\n");
	TestSchedulerClear();
	
	UNUSED(argv);
	UNUSED(argc);
	return 0;
}
