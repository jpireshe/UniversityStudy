#include <stdlib.h>
#include <stdio.h>

int readline(FILE *fp, char *buf, int maxlen)
{
	char c;
	int i = 0;

	while(i<maxlen && (c = fgetc(fp)) != '\n')
	{
		buf[i] = c;
		i++;
	}

	return(i);
}

int main()
{
	FILE *fp;

	fp = fopen("test.txt", "r");

	int maxlen = 128;
	char *buf = malloc(maxlen * sizeof(char));

	int r = readline(fp, buf, maxlen);

	printf("read %d bytes: %s\n", r, buf);

	fclose(fp);

	return(0);
}


