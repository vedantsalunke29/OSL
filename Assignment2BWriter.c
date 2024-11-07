#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void bubble_asc(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    printf("\nArray in ascending order: ");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <program_to_exec> <num1> <num2> ...\n", argv[0]);
        return 1;
    }

    int n = argc - 2;
    int arr[n];
    char *args[n + 2];  // Array to store arguments for execve
    args[0] = argv[1];  // The first argument should be the program to execute

    // Convert input strings to integers for sorting
    for (int i = 0; i < n; i++) {
        arr[i] = atoi(argv[i + 2]);
    }

    // Sort the array in ascending order
    bubble_asc(arr, n);

    // Convert sorted integers back to strings for execve arguments
    for (int i = 0; i < n; i++) {
        args[i + 1] = (char *)malloc(10);  // Allocate memory for each argument
        sprintf(args[i + 1], "%d", arr[i]);  // Convert integer to string
    }
    args[n + 1] = NULL;  // Null-terminate the argument array

    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        printf("\nI am Child Process, my PID is %d\n", getpid());
        printf("My Parent Process PID is %d\n", getppid());
        execve(argv[1], args, NULL);

        // If execve fails
        perror("execve failed");
        exit(1);
    } else if (pid > 0) {
        // Parent process
        int status;
        wait(&status);
        printf("\nI am Parent Process, my PID is %d\n", getpid());
    } else {
        // Fork failed
        perror("fork failed");
        return 1;
    }

    // Free allocated memory
    for (int i = 0; i < n; i++) {
        free(args[i + 1]);
    }

    return 0;
}
