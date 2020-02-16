
#define _POSIX_C_SOURCE 199309L

#include <stdio.h>		/* perror() 	*/
#include <stdlib.h>		/* exit()   	*/
#include <sys/types.h>	/* fork()   	*/
#include <sys/wait.h>	/* wait()   	*/
#include <unistd.h>		/* exec()  		*/
#include <string.h>		/* strcat() 	*/
#include <signal.h>		/* sigaction()	*/

volatile sig_atomic_t state = 0;

void SigusrHandler(int sig_num, siginfo_t *info, void *param)
{
	write(1, "ping ", 6);
	state = 0;
	
	kill(info->si_pid, SIGUSR1);
}

int main()
{
	struct sigaction sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = SigusrHandler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);

	while (0 == state)
	{
		
	}

	state = 0;

	return 0;
}
