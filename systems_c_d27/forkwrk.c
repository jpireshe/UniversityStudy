#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

int main()
{
	int ppid = getpid();

	printf("ppid %d\n", ppid);

	int cpid = fork();

	if(cpid == 0)
	{
		return 0;
	}

	int mypid = getpid();

	printf("got here! %d\n", mypid);

	int r = wait(NULL);

	printf("waited and got %d\n", r);

	while(1) { }

	return 0;
}

