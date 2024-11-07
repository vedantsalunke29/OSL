#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int choice, track, no_req, head, head1, distance;
int disc_req[100], finish[100];
void menu()
{
    printf("\n\n********MENU********");
    printf("\n1. Input data\n 2. SSTF \n 3. SCAN \n 4. C-LOOK \n 5. Exit");
    printf("\n\n Enter your choice");
    scanf("%d", &choice);
}
void input()
{
    int i;
    printf("Enter Total number of tracks");
    scanf("%d", &track);
    printf("Enter total number of disc requests");
    scanf("%d", &no_req);
    printf("\n Enter disc requests in FCFS order");
    for (i = 0; i < no_req; i++)
    {
        scanf("%d", &disc_req[i]);
    }
    printf("\n Enter current head position");
    scanf("%d", &head1);
}

void sstf()
{
    int min, diff;
    int pending = no_req;
    int i, distance = 0, index;
    head = head1;

    for (i = 0; i < no_req; i++)
    {
        finish[i] = 0;
    }

    printf("\n%d=>", head);

    while (pending > 0)
    {
        min = 9999;

        for (i = 0; i < no_req; i++)
        {
            diff = abs(head - disc_req[i]);
            if (finish[i] == 0 && diff < min)
            {
                min = diff;
                index = i;
            }
        }
        finish[index] = 1;
        distance += abs(head - disc_req[index]);
        head = disc_req[index];
        pending--;
        printf("%d=>", head);
    }
    printf("End");
    printf("\n\n Total Distance Traversed=%d", distance);
}

void sort()
{
    int i, j, temp;
    for (i = 0; i < no_req; i++)
    {
        for (j = 0; j < no_req; j++)
        {
            if (disc_req[i] < disc_req[j])
            {
                temp = disc_req[i];
                disc_req[i] = disc_req[j];
                disc_req[j] = temp;
            }
        }
    }
}
void scan()
{
    int index, dir;
    int i;
    distance = 0;
    head = head1;

    printf("\nEnter the direction of head \n1 - Towards higher disc (Right) \n0 - Towards lower disc (Left): ");
    scanf("%d", &dir);

    sort();

    // Find index of the first request greater than or equal to head
    for (i = 0; i < no_req; i++)
    {
        if (disc_req[i] >= head)
        {
            index = i;
            break;
        }
    }

    printf("\n%d=>", head);

    if (dir == 1)
    { // Moving towards higher end
        // Service all requests to the right of the current head position
        for (i = index; i < no_req; i++)
        {
            printf("%d=>", disc_req[i]);
            distance += abs(head - disc_req[i]);
            head = disc_req[i];
        }

        // Move to the end of the track
        distance += abs(head - (track - 1));
        head = track - 1;
        printf("%d=>", head);

        // Reverse direction and service remaining requests on the left side
        for (i = index - 1; i >= 0; i--)
        {
            printf("%d=>", disc_req[i]);
            distance += abs(head - disc_req[i]);
            head = disc_req[i];
        }
    }
    else
    { // Moving towards lower end
        // Service all requests to the left of the current head position
        for (i = index - 1; i >= 0; i--)
        {
            printf("%d=>", disc_req[i]);
            distance += abs(head - disc_req[i]);
            head = disc_req[i];
        }

        // Move to the beginning of the track
        distance += abs(head - 0);
        head = 0;
        printf("0=>");

        // Reverse direction and service remaining requests on the right side
        for (i = index; i < no_req; i++)
        {
            printf("%d=>", disc_req[i]);
            distance += abs(head - disc_req[i]);
            head = disc_req[i];
        }
    }
    printf("End");
    printf("\nTotal Distance Traversed = %d", distance);
}

void clook()
{
    int index, dir;
    int i;
    distance = 0;
    head = head1;

    printf("\nEnter the direction of head \n1 - Towards higher disc \n0 - Towards lower disc: ");
    scanf("%d", &dir);

    sort();

    // Find index of the first request greater than or equal to head
    for (i = 0; i < no_req; i++)
    {
        if (disc_req[i] >= head)
        {
            index = i;
            break;
        }
    }

    printf("\n%d=>", head);

    if (dir == 1)
    { // Moving towards higher end
        for (i = index; i < no_req; i++)
        { // Service right side
            printf("%d=>", disc_req[i]);
            distance += abs(head - disc_req[i]);
            head = disc_req[i];
        }
        // Jump to the beginning of the list and service from there
        for (i = 0; i < index; i++)
        {
            printf("%d=>", disc_req[i]);
            distance += abs(head - disc_req[i]);
            head = disc_req[i];
        }
    }
    else
    { // Moving towards lower end
        for (i = index - 1; i >= 0; i--)
        { // Service left side
            printf("%d=>", disc_req[i]);
            distance += abs(head - disc_req[i]);
            head = disc_req[i];
        }
        // Jump to the end of the list and service from there
        for (i = no_req - 1; i >= index; i--)
        {
            printf("%d=>", disc_req[i]);
            distance += abs(head - disc_req[i]);
            head = disc_req[i];
        }
    }
    printf("End");
    printf("\nTotal Distance Traversed = %d", distance);
}

int main()
{
    while (1)
    {
        menu();
        switch (choice)
        {
        case 1:
            input();
            break;
        case 2:
            sstf();
            break;
        case 3:
            scan();
            break;
        case 4:
            clook();
            break;
        case 5:
            exit(0);
            break;
        default:
            printf("\n Enter valid choice");
            break;
        }
    }

    return 0;
}
/*
Author : Avinash J Kokare

YouTube Channel link : https://www.youtube.com/c/avinashkokare27

*/
/*
Input
100
11
45 21 67 90 4 50 89 52 61 87 25
50
*/
