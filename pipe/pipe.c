#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main()
{
	pid_t pid1;
	
	int pipe_id[2];		
	int ret = pipe(pipe_id);	
	
	char buf[20];
	
	if ( ret == -1 )
	{
		printf("Error");
		exit(1);
	}
	
	pid1 = fork();
	
	if (pid1 < 0)
	{
		printf("Error");
		exit(1);
	}
	else if (pid1 == 0)
	{
		/* Child Process */
		read(pipe_id[0],buf, 20 );
		printf("This is Child Process\n");
		printf("Message: %s\n", buf);
		
	} else {
		
		/* Parent Process */
		printf("This is Parent Process\n");
		write(pipe_id[1],"Hello from Parent",20);
	}
 			
			
	return 0;
}
