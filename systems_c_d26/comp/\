#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>

#define NT 4

typedef struct {
	int tn;
} threadarg;

int rets[NT];

void * threadfcn(void *varg)
{
	threadarg *args = (threadarg *) varg;

	printf("in threadfcn got number %d\n", args->tn);
	
	int i = 0;
	int j;

	for(j=0; j<INT_MAX; j++)
		i++;

	rets[args->tn] = i;
}

int main()
{
	int i;

	pthread_t tid[NT];
	threadarg targs[NT];

	for(i=0; i<NT; i++)
		targs[i].tn = i;

	for(i=0; i<NT; i++)
		pthread_create(&tid[i], NULL, threadfcn, (void *) &targs[i]);

	for(i=0; i<NT; i++)
	{
		pthread_join(tid[i], NULL);
		printf("thread %d returned %d!\n", i, rets[i]);
	}

	return(0);
}

