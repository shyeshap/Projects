
#include <stdio.h>		/* perror() 	*/
#include <stdlib.h>		/* exit()   	*/
#include <sys/types.h>	/* fork()   	*/
#include <sys/wait.h>	/* wait()   	*/
#include <unistd.h>		/* exec()  		*/
#include <string.h>		/* strcat() 	*/
#include <signal.h>		/* sigaction()	*/

volatile sig_atomic_t state = 0;

void SigusrHandler(int sig_num)
{
	struct sigaction sa;
	sa.sa_flags = 0;
	sa.sa_handler = SigusrHandler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);

	write(1, "pong\n", 6);
	state = 0;
}

int main()
{
	struct sigaction sa;
	
	sa.sa_handler = SigusrHandler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);

	while(1)
	{
		while (1 == state)
		{

		}

		state = 1;
		kill(getppid(), SIGUSR1);
	}

	return 0;
} 