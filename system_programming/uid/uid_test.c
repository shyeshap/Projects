/********************************/
/*	    	  USER ID			*/
/*								*/
/*			Shye Shapira		*/
/*			 10/12/2019			*/
/********************************/

#include <stdio.h> /* printf() */

#include "uid.h"

#define GREEN "\033[;032m"
#define RED   "\033[;031m"
#define RESET "\033[0m"
#define TEST(test,mssg)\
            if (test)\
            {\
                printf(GREEN "SUCCESS: %s\n",mssg);\
                printf(RESET);\
            }\
            else\
            {\
                printf(RED "FAIL: %s\n",mssg);\
                printf(RESET);\
            }
            
  
int main()
{
	ilrd_uid_t uid, uid1;
	
	uid = UIDCreate();
	printf("%lu - %ld - %d\n", uid.counter, uid.time_stamp, uid.pid);
	
	uid1 = UIDCreate();
	printf("%lu - %ld - %d\n", uid1.counter, uid1.time_stamp, uid1.pid);
	
	TEST(0 == UIDIsBad(uid), "not bad");
	TEST(0 == UIDIsSame(uid, uid1), "not same");
	
	uid1.counter = 0;
	
	TEST(1 == UIDIsBad(uid1), "is bad");
	TEST(1 == UIDIsSame(uid, uid), "same");
	
	return 0;
}
