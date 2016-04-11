#include "functions.h"

enum color {red, green, blue, yellow, orange};

int main(int argc, char* argv[]){
	pid_t pidt;
	pid_t pid[5];
	int count[5];
	int status;
	int i;
	char* filename;

	filename = getFilename(argc, argv);
	
	for(i = 0; i < 5; i++)
	{
		if((pid[i] = fork()) < 0)
		{
			exit(1);
		}
		else if(pid[i] == 0)
		{
			int numfound;
			numfound = childGetCount(i, filename);
			exit(numfound);
		}
	}

	int j;
	for(i = 0; i < 5; i++)
	{
		pidt = wait(&status);
		for(j = 0; j < 5; j++)
		{
			if(pidt == pid[j])	
				count[j] = (status / 256);
		}
	}

	printf("red:      %d\n", count[red]);
	printf("green:    %d\n", count[green]);
	printf("blue:     %d\n", count[blue]);
	printf("yellow:   %d\n", count[yellow]);
	printf("orange:   %d\n", count[orange]);


	return 0;
}



























