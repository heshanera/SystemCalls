#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>


#define SHSIZE 100

int main()
{
	
	int shmid;
	key_t key;
	char *shm;
	
	key = 9856;
	
	shmid = shmget(key, SHSIZE, 0776);

	if ( shmid == -1 )
	{
		perror("shmget");
		exit(1);
	}	
	
	shm = shmat(shmid, NULL, 0);
	
	if (shm == (char *)-1)
	{
		perror("shmat");
		exit(1);
	}

	char* s;
	for (s = shm; *s != 0; s++)
	{
		printf("%c",*s);
	}
	
	*shm = '*'; 
	
	
	return 0;	
}

