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
	
	shmid = shmget(key, SHSIZE, IPC_CREAT | 0776);

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
	
	memcpy(shm,"Hello",5);
	
	char* s = shm;
	s += 5;
	*s = 0; 
	
	while (*shm != '*') sleep(1);
	
	return 0;	
}

