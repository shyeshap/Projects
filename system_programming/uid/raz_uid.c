/*
 * Author: Raz KaziRo
 * Purpose: Answares for System Programing - UID.
 * Date: 15.12.2019
 * Language: C
 * Reviewer: Ben Zaad
 */

#include <time.h> 	   /*time_t*/
#include <unistd.h>	   /*getpid()*/
#include <sys/types.h> /*pid_t()*/

#include "uid.h" /*UID Functions()*/

ilrd_uid_t UIDCreate()
{	
	static size_t counter = 0;
	ilrd_uid_t new_pid = {0};

	new_pid.time_stamp = time(NULL);
	new_pid.counter = ++counter;
	new_pid.pid = getpid();

	return new_pid;
}

int UIDIsBad(ilrd_uid_t uid)
{
	return (0 == uid.counter || 0 == uid.time_stamp || 0 == uid.pid);
}

int UIDIsSame(ilrd_uid_t uid1, ilrd_uid_t uid2)
{
	return (uid1.time_stamp == uid2.time_stamp 
		&& uid1.counter == uid2.counter
		&& uid1.pid == uid2.pid);
}
