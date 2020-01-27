/************************************************
*
* File: scheduler_test.c
* Ex: system programing, scheduler
* writer: Israel Drayfus
* Description: run and test functions of scheduler.
*
*************************************************/

#include <stdio.h> /*printf()*/

#include "scheduler.h" /*API header*/

#define RED "\033[31m"
#define GREEN "\033[32m"
#define WHITE "\033[0m"

#define TEST(test, errMsg) if (test)\
						   {\
						      printf(GREEN);\
						      printf("%s\n", "SUCCESS");\
						   }\
						   else\
						   {\
						      printf(RED);\
						      printf("%s, %s\n", "FAILURE", errMsg);\
						   }\
						   printf(WHITE);

#define UNUSED(param) (void)param

#define DELAY_10 3
#define DELAY_3 1

typedef void (*Scheduler_func)(scheduler_t *s);

typedef struct Pack
{
	Scheduler_func func;
	scheduler_t *s;
}scduler_pack_t;
 
int PrintTest(void *param)
{
	UNUSED(param);
	
	printf("\033[36m");
	printf("Test\n");
	printf(WHITE);
	
	return 0;
}

int Stop(void *param)
{
	((scduler_pack_t *)param)->func(((scduler_pack_t *)param)->s);
	
	return 0;
}

void TestTask()
{
	char buff[100];
	ilrd_uid_t uid;
	time_t time = 0;
	
	task_t *task = TaskCreate(PrintTest, (time_t)10, NULL);
	
	uid = TaskGetUid(task);
	strftime (buff, 100, "%Y-%m-%d %H:%M:%S", localtime(&uid.time_stamp));
	printf("time: %s, counter: %lu, pid: %d\n", buff, uid.counter, uid.pid);
	
	time = TaskGetTimeToRun(task);
	strftime (buff, 100, "%Y-%m-%d %H:%M:%S",
	          localtime(&time)
	         );
	printf("time: %s\n", buff);
	TaskRun(task);
	time = TaskGetTimeToRun(task);
	strftime (buff, 100, "%Y-%m-%d %H:%M:%S",
	          localtime(&time)
	         );
	printf("time: %s\n", buff);
	
	TaskDestroy(task);
}

void Test1(scheduler_t *scduler)
{
	scduler_pack_t pack;
	
	TEST(1 == SchedulerIsEmpty(scduler), "IsEmpty(), True");
	TEST(0 == SchedulerSize(scduler), "Size(), empty list");
	SchedulerAddTask(scduler, PrintTest, DELAY_10, NULL);
	
	pack.func = SchedulerStop;
	pack.s = scduler;
	SchedulerAddTask(scduler, Stop, DELAY_10, &pack);
	TEST(0 == SchedulerIsEmpty(scduler), "IsEmpty(), False");
	TEST(2 == SchedulerSize(scduler), "Size(), two items list");
	printf("run1:");
	SchedulerRun(scduler);
	printf("run2:");
	SchedulerRun(scduler);
	SchedulerClear(scduler);
	TEST(0 == SchedulerSize(scduler), "Size after Clear, empty list");
	printf("\n");
	
	/*
	SchedulerAddTask(scduler, PrintTest, DELAY_10, NULL);
	SchedulerAddTask(scduler, PrintTest, DELAY_10, NULL);
	SchedulerAddTask(scduler, Stop, DELAY_10, &pack);
	SchedulerRun(scduler);
	SchedulerRemoveTask(
	*/
}

void Test(scheduler_t *scduler)
{
	scduler_pack_t pack;
	
	SchedulerAddTask(scduler, PrintTest, DELAY_3, NULL);
	
	pack.func = SchedulerStop;
	pack.s = scduler;
	SchedulerAddTask(scduler, Stop, DELAY_10, &pack);
	SchedulerRun(scduler);
	
	printf("\n");
}

int main()
{
	/*TestTask();
	*/
	scheduler_t *scduler = SchedulerCreate();
	
	Test1(scduler);
	/*
	Test(scduler);
	*/
	SchedulerDestroy(scduler);
	
	return 0;
}
