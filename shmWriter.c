// Writer process
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

int main()
{
	// ftok to generate unique key
	key_t key = ftok("shmfile", 65);

	// shmget returns an identifier in shmid
	// r-4 w-2 x-1
	int shmid = shmget(key, 1024, 0666 | IPC_CREAT);

	// shmat to attach to shared memory
	char *str = (char *)shmat(shmid, NULL, 0);

	printf("Write Data : ");
	fgets(str, 1024, stdin);
	printf("Data written in memory: %s\n", str);

	// detach from shared memory
	shmdt(str);

	return 0;
}
