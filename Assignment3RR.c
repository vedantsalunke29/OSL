#include <stdio.h>
#include <stdbool.h>
#define MAX_PROCESS 10
typedef struct
{
    int id;         // Process ID
    int arrival;    // Arrival time
    int burst;      // Burst time
    int remaining;  // Remaining burst time
    int waiting;    // Waiting time
    int turnaround; // Turnaround time
} Process;
void roundRobin(Process proc[], int n, int quantum)
{
    int i, time = 0, completed = 0;
    int totalWaitingTime = 0, totalTurnaroundTime = 0;
    // Initialize remaining burst times
    for (i = 0; i < n; i++)
    {
        proc[i].remaining = proc[i].burst;
    }
    while (completed < n)
    {
        bool found = false;
        for (i = 0; i < n; i++)
        {
            if (proc[i].arrival <= time && proc[i].remaining > 0)
            {
                found = true;
                if (proc[i].remaining > quantum)
                {
                    proc[i].remaining -= quantum;
                    time += quantum;
                }
                else
                {
                    time += proc[i].remaining;
                    proc[i].remaining = 0;
                    proc[i].turnaround = time - proc[i].arrival;
                    proc[i].waiting = proc[i].turnaround - proc[i].burst;
                    totalWaitingTime += proc[i].waiting;
                    totalTurnaroundTime += proc[i].turnaround;
                    completed++;
                }
            }
        }
        if (!found)
        {
            time++;
        }
    }

    printf("\nRound Robin Scheduling:\n");
    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].id, proc[i].arrival, proc[i].burst,
               proc[i].waiting, proc[i].turnaround);
    }
    printf("\nAverage Waiting Time: %.2f", (float)totalWaitingTime / n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)totalTurnaroundTime / n);
}
int main()
{
    int n, i, quantum;
    Process proc[MAX_PROCESS];
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        proc[i].id = i + 1;
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &proc[i].arrival, &proc[i].burst);
    }
    printf("Enter time quantum for Round Robin: ");
    scanf("%d", &quantum);
    roundRobin(proc, n, quantum);
    return 0;
}

/*
Enter the number of processes: 5
Enter arrival time and burst time for process 1: 2 6
Enter arrival time and burst time for process 2: 5 2
Enter arrival time and burst time for process 3: 1 8
Enter arrival time and burst time for process 4: 0 3
Enter arrival time and burst time for process 5: 4 4
Enter time quantum for Round Robin: 3

Round Robin Scheduling:
Process ID      Arrival Time    Burst Time      Waiting Time    Turnaround Time
1               2               6               9               15
2               5               2               1               3
3               1               8               14              22
4               0               3               0               3
5               4               4               13              17

Average Waiting Time: 7.40
Average Turnaround Time: 12.00
*/