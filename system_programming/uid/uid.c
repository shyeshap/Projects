/********************************/
/*	    	  USER ID			*/
/*								*/
/*			Shye Shapira		*/
/*			 10/12/2019			*/
/********************************/

#include <time.h> /* time_t */
#include <stdio.h> /* size_t */
#include <sys/types.h> /* pid_t */
#include <unistd.h> /* getpid() */

#include "uid.h"
	
ilrd_uid_t UIDCreate()
{
	static size_t counter = 0UL;
	ilrd_uid_t uid = {0};
	
	uid.time_stamp = time(NULL);
	uid.counter = ++counter;
	uid.pid = getpid();
	
	return uid;
}

int UIDIsBad(ilrd_uid_t uid)
{
	return (uid.pid == 0 ||
			uid.counter == 0 ||
			uid.time_stamp == 0);
}

int UIDIsSame(ilrd_uid_t uid1, ilrd_uid_t uid2)
{
	return (uid1.pid == uid2.pid &&
			uid1.counter == uid2.counter &&
			uid1.time_stamp == uid2.time_stamp);
}
