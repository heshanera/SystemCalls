#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{	
	//printf("%d",getid());
	pid_t pid1 = fork();
	
	if (pid1 < 0)
	{
		exit(1);
	}
	else if (pid1 == 0)
	{
		printf("CHILD2\n");
		wait(NULL);		
	}
	else
	{
		pid_t pid2 = fork();
		if (pid2 == 0)
		{
			printf("CHILD1\n");
			
		}
		else
		{
			printf("PARENT\n");
			
		}
		wait(NULL);
	}
	wait(NULL);



}
