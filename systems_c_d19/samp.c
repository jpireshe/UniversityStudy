#include <stdlib.h>
#include <stdio.h>

void does_work(char ** msg)
{
	msg[0] = malloc(3 * sizeof(char));
	msg[0][0] = 'a';
	msg[0][1] = 'b';
	msg[0][2] = '\0';

	msg[1] = malloc(2 * sizeof(char));
	msg[1][0] = 'c';
	msg[1][1] = '\0';
}

void print_work(char ** msg)
{
	printf("%s\n", msg[0]);
	printf("%s\n", msg[1]);
}

int main()
{
	char **msg;
	msg = malloc(2 * sizeof(char *));
	does_work(msg);
	print_work(msg);		

	return(0);
}

