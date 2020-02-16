#include <stdio.h>		/* perror() 	*/
#include <stdlib.h>		/* exit()   	*/
#include <sys/types.h>	/* fork()   	*/
#include <sys/wait.h>	/* wait()   	*/
#include <unistd.h>		/* exec()  		*/
#include <string.h>		/* strcat() 	*/
#include <signal.h>		/* sigaction()	*/

volatile sig_atomic_t state = 0;

void Sigusr1Handler(int sig_num)
{
	struct sigaction sa;
	sa.sa_flags = 0;
	sa.sa_handler = Sigusr1Handler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);

	write(1, "ping ", 6);
	state = 1;
}

int main()
{
	pid_t pid = 0;
	struct sigaction sa;
	char *const args[] = {"./pong.out" ,NULL};

	sa.sa_flags = 0;
	sa.sa_handler = Sigusr1Handler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);

	pid = fork();

	if (0 > pid)
	{
		perror("fork() failed");
		exit(EXIT_FAILURE);
	}
	
	if (0 == pid)
	{	
		if (0 != execvp("./pong.out", args))
		{
			perror("execvp() failed");
			exit(EXIT_FAILURE);
		}
	}	
	
	else if (0 < pid)
	{
		while(1)
		{
			while (0 == state)
			{

			}

			state = 0;
			kill(pid, SIGUSR1);
		}
	}		

	return 0;
} 