#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char * argv[])
{
	pid_t pid = 0;

	pid = fork();

	if (pid > 0)
	{
		printf("parent : %u\n", getpid());
	}

	else
	{
		printf("child : %u\n", getpid());
		printf("child parent : %u\n", getppid());
	}

	return 0;
} 