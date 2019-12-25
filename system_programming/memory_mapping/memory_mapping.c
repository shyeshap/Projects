#include <stdlib.h> /* malloc */

int global = 3;
const int const_global = 10;
static int stat_global = 7;
static const int const_stat_global = 9;

static void Stat()
{

}

void exter()
{

}

int main(int argc, char *argv[], char **envp)
{
	int *heap = (int *)malloc(sizeof(int));
	int local = 8;
	const int const_local = 5;
	static int stat_local = 1;
	static const int const_stat_local = 2;
	char *str = "Hello world";
	
	char **arg = argv;
	char **env = envp;
	
	Stat();
	exter();
	
	free(heap);
	
	return 0;
}
