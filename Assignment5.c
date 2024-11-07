#include <stdio.h>
#include <stdbool.h>

#define P 5
#define R 3

int allocation[P][R];
int max[P][R];
int need[P][R];
int available[R];

void calculateNeed()
{
    for (int i = 0; i < P; i++)
    {
        for (int j = 0; j < R; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

bool isSafe()
{
    int work[R];
    bool finish[P] = {false};
    int safeSequence[P];
    int index = 0;

    for (int i = 0; i < R; i++)
    {
        work[i] = available[i];
    }

    int count = 0;
    while (count < P)
    {
        bool found = false;
        for (int p = 0; p < P; p++)
        {
            if (!finish[p])
            {
                bool canFinish = true;
                for (int j = 0; j < R; j++)
                {
                    if (need[p][j] > work[j])
                    {
                        canFinish = false;
                        break;
                    }
                }
                if (canFinish)
                {
                    for (int j = 0; j < R; j++)
                    {
                        work[j] += allocation[p][j];
                    }
                    safeSequence[index++] = p;
                    finish[p] = true;
                    found = true;
                    count++;
                }
            }
        }
        if (!found)
        {
            printf("System is in an unsafe state!\n");
            return false;
        }
    }

    printf("System is in a safe state.\nSafe sequence: ");
    for (int i = 0; i < P; i++)
    {
        printf("-> P%d ", safeSequence[i]);
    }
    printf("\n");

    return true;
}

bool requestResources(int processID, int request[])
{
    for (int j = 0; j < R; j++)
    {
        if (request[j] > need[processID][j])
        {
            printf("Error: Process has exceeded its maximum claim.\n");
            return false;
        }
        if (request[j] > available[j])
        {
            printf("Process %d must wait; not enough resources available.\n", processID);
            return false;
        }
    }

    for (int j = 0; j < R; j++)
    {
        available[j] -= request[j];
        allocation[processID][j] += request[j];
        need[processID][j] -= request[j];
    }
    calculateNeed();
    if (isSafe())
    {
        return true;
    }
    else
    {
        for (int j = 0; j < R; j++)
        {
            available[j] += request[j];
            allocation[processID][j] -= request[j];
            need[processID][j] += request[j];
        }
        calculateNeed();
        printf("Request cannot be granted, rolling back allocation.\n");
        return false;
    }
}

int main()
{
    int request[R];

    allocation[0][0] = 0;
    allocation[0][1] = 1;
    allocation[0][2] = 0;
    allocation[1][0] = 2;
    allocation[1][1] = 0;
    allocation[1][2] = 0;
    allocation[2][0] = 3;
    allocation[2][1] = 0;
    allocation[2][2] = 2;
    allocation[3][0] = 2;
    allocation[3][1] = 1;
    allocation[3][2] = 1;
    allocation[4][0] = 0;
    allocation[4][1] = 0;
    allocation[4][2] = 2;

    max[0][0] = 7;
    max[0][1] = 5;
    max[0][2] = 3;
    max[1][0] = 3;
    max[1][1] = 2;
    max[1][2] = 2;
    max[2][0] = 9;
    max[2][1] = 0;
    max[2][2] = 2;
    max[3][0] = 2;
    max[3][1] = 2;
    max[3][2] = 2;
    max[4][0] = 0;
    max[4][1] = 0;
    max[4][2] = 2;

    available[0] = 3;
    available[1] = 3;
    available[2] = 2;

    calculateNeed();

    request[0] = 1;
    request[1] = 0;
    request[2] = 2;
    if (requestResources(1, request))
    {
        printf("Resources granted for process 1.\n");
    }
    else
    {
        printf("Resources not granted for process 1.\n");
    }

    request[0] = 1;
    request[1] = 0;
    request[2] = 2;
    if (requestResources(0, request))
    {
        printf("Resources granted for process 0.\n");
    }
    else
    {
        printf("Resources not granted for process 0.\n");
    }

    return 0;
}
