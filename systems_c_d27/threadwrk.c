#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>
#include <unistd.h>

#define NT 4

typedef struct {
	int tn;
} threadarg;

int rets[NT];

void * threadfcn(void *varg)
{
	threadarg *arg = (threadarg *) varg;

	printf("in threadfcn %d\n", arg->tn);
	fflush(NULL);

	int i = 0;
	int j;
	for(j=0; j<INT_MAX; j++)
		i++;

	//rets[arg->tn] = i;
	
	char *fn = malloc(128 * sizeof(char));
	sprintf(fn, "tmp_%d.bin", getpid());
	FILE *fp = fopen(fn, "wb");
	fwrite(&i, sizeof(int), 1, fp);
	fclose(fp);
	free(fn);

}

int main()
{
	int i, cpid, wpid, r;

	//pthread_t tid[NT];
	threadarg targs[NT];

	for(i=0; i<NT; i++)
		targs[i].tn = i;

	for(i=0; i<NT; i++)
	{
		//pthread_create(&tid[i], NULL, threadfcn, (void *) &targs[i]); 
		cpid = fork();
		if(cpid == 0)
		{
			threadfcn((void *) &targs[i]);
			return 0;
		}
	}

	for(i=0; i<NT; i++)
	{
		//pthread_join(tid[i], NULL);
		wpid = wait(NULL);

		char *fn = malloc(128 * sizeof(char));
        	sprintf(fn, "tmp_%d.bin", wpid);
		FILE *fp = fopen(fn, "rb");
		fread(&r, sizeof(int), 1, fp);
		fclose(fp);
		remove(fn);
		free(fn);

		printf("thread %d returned %d\n", i, r);
	}

	return 0;
}


