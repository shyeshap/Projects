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
	write(1, "ping ", 6);
	state = 1;
}

void Sigusr2Handler(int sig_num)
{
	write(1, "pong\n", 6);
	state = 0;
}

int main()
{
	pid_t pid = 0;
	struct sigaction sa;
	struct sigaction sa_parent;

	sa.sa_handler = Sigusr2Handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR2, &sa, NULL);

	sa_parent.sa_flags = 0;
	sa_parent.sa_handler = Sigusr1Handler;
	sigemptyset(&sa_parent.sa_mask);
	sigaction(SIGUSR1, &sa_parent, NULL);


		pid = fork();

		if (0 > pid)
		{
			perror("fork() failed");
			exit(EXIT_FAILURE);
		}

		else if (0 < pid)
		{	
			printf("parent's pid: %d, child's pid: %d\n", getpid(), pid);

			while(1)
			{	
				while (1 == state)
				{

				}

				state = 1;
				kill(pid, SIGUSR1);
			}
			
		}

		else
		{
			while(1)
			{
				while (0 == state)
				{

				}

				state = 0;
				kill(getppid(), SIGUSR2);	
			}
		}

	return 0;
}

int Ex1()
{
	pid_t pid = 0;
	struct sigaction sa;
	struct sigaction sa_parent;

	sa.sa_handler = Sigusr2Handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR2, &sa, NULL);

	sa_parent.sa_flags = 0;
	sa_parent.sa_handler = Sigusr1Handler;
	sigemptyset(&sa_parent.sa_mask);
	sigaction(SIGUSR1, &sa_parent, NULL);

	while (1)
	{
		pid = fork();

		if (0 > pid)
		{
			perror("fork() failed");
			exit(EXIT_FAILURE);
		}

		else if (0 < pid)
		{	
			printf("parent's pid: %d, child's pid: %d\n", getpid(), pid);

			if (0 > pid)
			{
				perror("fork() faild");
			}

			while(1)
			{		
				sleep(1);
				kill(pid, SIGUSR1);
				pause();
			}
			
		}

		else
		{
			while(1)
			{
				pause();
				kill(getppid(), SIGUSR2);	
			}
		}
	}
}

int Ex2()
{
	pid_t pid = 0, pid2 = 0;
	struct sigaction sa;
	struct sigaction sa_parent;
	char *const args[] = {"./pong.out", NULL};

	sa.sa_handler = Sigusr2Handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR2, &sa, NULL);

	sa_parent.sa_flags = 0;
	sa_parent.sa_handler = Sigusr1Handler;
	sigemptyset(&sa_parent.sa_mask);
	sigaction(SIGUSR1, &sa_parent, NULL);

	while (1)
	{
		pid = fork();

		if (0 > pid)
		{
			perror("fork() failed");
			exit(EXIT_FAILURE);
		}

		else if (0 < pid)
		{	
			printf("parent's pid: %d, child's pid: %d\n", getpid(), pid);

			if(0 == pid2)
			{
				if (0 != execvp(args[0], args))
				{
					perror("execpv() failed");
					exit(EXIT_FAILURE);
				}
			}

			while(1)
			{		
				sleep(1);
				kill(pid, SIGUSR1);
				kill(pid2, SIGUSR1);
				pause();
			}
			
		}

		else
		{
			if (0 != execvp(args[0], args))
			{
				perror("execpv() failed");
				exit(EXIT_FAILURE);
			}
	
		}
	}

	return 0;
} 