#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main()
{
    pid_t pid;
    char *message;
    int n;
    printf("Zombie program starting\n");
    pid = fork();
    switch (pid)
    {
    case -1:
        perror("fork failed");
    case 0:
        message = "This is the child";
        printf("Child process ID : %d\n", getpid());
        printf("Parent process ID : %d\n", getppid());
        n = 3;
        break;
    default:
        message = "This is the parent";
        printf("Parent process ID : %d\n", getpid());
        printf("Parent Parent's process ID : %d\n", getppid());
        n = 7;
        break;
    }
    for (; n > 0; n--)
    {
        puts(message);
        sleep(1);
    }
    int f = wait(NULL);
    printf("Terminated Child ID : %d\n", f);
    return 0;
}

// check the process by : ps -al