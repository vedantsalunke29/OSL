#include <stdio.h>
#include <limits.h>
#define MAX_PROCESS 10

typedef struct
{
       int id;         // Process ID
       int arrival;    // Arrival time
       int burst;      // Burst time
       int remaining;  // Remaining burst time for preemption
       int completion; // Completion time
       int waiting;    // Waiting time
       int turnaround; // Turnaround time
       int start;      // Start time for Gantt chart
} Process;

void preemptive_sjf(Process proc[], int n)
{
       int time = 0, completed = 0, shortest = -1;
       int minRemainingTime = INT_MAX;
       int totalWaitingTime = 0, totalTurnaroundTime = 0;
       int isProcessSelected = 0;

       // Initialize remaining time
       for (int i = 0; i < n; i++)
       {
              proc[i].remaining = proc[i].burst;
              proc[i].start = -1; // Mark start time as unset
       }

       printf("\nGantt Chart:\n");

       while (completed != n)
       {
              // Find process with the shortest remaining time among processes that have arrived
              shortest = -1;
              minRemainingTime = INT_MAX;
              isProcessSelected = 0;

              for (int i = 0; i < n; i++)
              {
                     if (proc[i].arrival <= time && proc[i].remaining > 0 && proc[i].remaining < minRemainingTime)
                     {
                            minRemainingTime = proc[i].remaining;
                            shortest = i;
                            isProcessSelected = 1;
                     }
              }

              // If no process is selected, increment time and continue
              if (!isProcessSelected)
              {
                     time++;
                     continue;
              }

              // Set start time for the first execution of the process
              if (proc[shortest].start == -1)
              {
                     proc[shortest].start = time;
              }

              // Execute the process for 1 time unit
              proc[shortest].remaining--;
              time++;

              // Print Gantt chart process start
              printf("|  P%d  ", proc[shortest].id);

              // If process finishes execution
              if (proc[shortest].remaining == 0)
              {
                     completed++;
                     proc[shortest].completion = time;
                     proc[shortest].turnaround = proc[shortest].completion - proc[shortest].arrival;
                     proc[shortest].waiting = proc[shortest].turnaround - proc[shortest].burst;
                     totalWaitingTime += proc[shortest].waiting;
                     totalTurnaroundTime += proc[shortest].turnaround;
              }
       }

       printf("|\n");

       // Display process details
       printf("\nPreemptive SJF Scheduling:\n");
       printf("Process ID\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
       for (int i = 0; i < n; i++)
       {
              printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
                     proc[i].id, proc[i].arrival, proc[i].burst,
                     proc[i].completion, proc[i].waiting, proc[i].turnaround);
       }

       // Display average waiting and turnaround times
       printf("\nAverage Waiting Time: %.2f", (float)totalWaitingTime / n);
       printf("\nAverage Turnaround Time: %.2f\n", (float)totalTurnaroundTime / n);
}

int main()
{
       int n;
       Process proc[MAX_PROCESS];

       printf("Enter the number of processes: ");
       scanf("%d", &n);

       for (int i = 0; i < n; i++)
       {
              proc[i].id = i + 1;
              printf("Enter arrival time and burst time for process %d: ", i + 1);
              scanf("%d %d", &proc[i].arrival, &proc[i].burst);
              proc[i].completion = 0;
       }

       preemptive_sjf(proc, n);

       return 0;
}

/*
Enter the number of processes: 5
Enter arrival time and burst time for process 1: 2 6
Enter arrival time and burst time for process 2: 5 2
Enter arrival time and burst time for process 3: 1 8
Enter arrival time and burst time for process 4: 0 3
Enter arrival time and burst time for process 5: 4 4

Gantt Chart:
|  P4  |  P4  |  P4  |  P1  |  P5  |  P2  |  P2  |  P5  |  P5  |  P5  |  P1  |  P1  |  P1  |  P1  |  P1  |  P3  |  P3  |  P3  |  P3  |  P3  |  P3  |  P3  |  P3  |

Preemptive SJF Scheduling:
Process ID      Arrival Time    Burst Time      Completion Time Waiting Time    Turnaround Time
4               0               3               3               0               3
3               1               8               23              14              22
1               2               6               15              7               13
5               4               4               10              2               6
2               5               2               7               0               2

Average Waiting Time: 4.60
Average Turnaround Time: 9.20
*/