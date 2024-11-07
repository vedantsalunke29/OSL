#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
int main()
{
    pid_t pid;
    char *message;
    int n;
    printf("Orphan program starting\n");
    pid = fork();
    switch (pid)
    {
    case -1:
        perror("fork failed");
    case 0:
        message = "This is the child";
        printf("Child process ID : %d", getpid());
        printf("Parent process ID : %d", getppid());
        n = 7;
        break;
    default:
        message = "This is the parent";
        printf("Parent process ID : %d", getpid());
        printf("Parent Parent's process ID : %d", getppid());
        n = 3;
        break;
    }
    for (; n > 0; n--)
    {
        puts(message);
        sleep(1);
    }
}

// check the process by : ps -al