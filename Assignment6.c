#include <stdio.h>
#include <stdlib.h>
#define FRAME_SIZE 3
#define TOTAL_PAGES 10

void pageReplacementFCFS(int pages[], int n);
void pageReplacementLRU(int pages[], int n);
void pageReplacementOptimal(int pages[], int n);

int main()
{
    int pages[TOTAL_PAGES] = {0, 1, 2, 3, 0, 1, 1, 4, 0, 1};
    printf("Page Replacement Algorithms Simulation\n");
    printf("\nFCFS Page Replacement:\n");
    pageReplacementFCFS(pages, TOTAL_PAGES);
    printf("\nLRU Page Replacement:\n");
    pageReplacementLRU(pages, TOTAL_PAGES);
    printf("\nOptimal Page Replacement:\n");
    pageReplacementOptimal(pages, TOTAL_PAGES);
    return 0;
}

void pageReplacementFCFS(int pages[], int n)
{
    int frame[FRAME_SIZE];
    int pageFaults = 0;

    for (int i = 0; i < FRAME_SIZE; i++)
        frame[i] = -1;
        
    for (int i = 0; i < n; i++)
    {
        int j = 0;
        for (; j < FRAME_SIZE; j++)
        {
            if (frame[j] == pages[i])
            {
                break;
            }
        }
        if (j == FRAME_SIZE)
        {
            frame[pageFaults % FRAME_SIZE] = pages[i];
            pageFaults++;
            printf("(Page Fault number %d) ", pageFaults);
        }
        printf("Page %d -> Frames: ", pages[i]);
        for (int k = 0; k < FRAME_SIZE; k++)
        {
            if (frame[k] != -1)
                printf("%d ", frame[k]);
            else
                printf("- ");
        }
        printf("\n");
    }
    printf("Total Page Faults (FCFS): %d\n", pageFaults);
}


void pageReplacementLRU(int pages[], int n)
{
    int frame[FRAME_SIZE]; // Frame to hold pages
    int pageFaults = 0;
    int i, j;

    // Initialize frame to -1 to indicate empty slots
    for (i = 0; i < FRAME_SIZE; i++)
        frame[i] = -1;

    for (i = 0; i < n; i++)
    {
        int found = 0;

        // Check if the page is already in the frame
        for (j = 0; j < FRAME_SIZE; j++)
        {
            if (frame[j] == pages[i])
            {
                found = 1;
                // Move the page to the most recent position
                int temp = frame[j];
                for (int k = j; k < FRAME_SIZE - 1; k++)
                {
                    frame[k] = frame[k + 1];
                }
                frame[FRAME_SIZE - 1] = temp;
                break;
            }
        }

        // If page is not found, a page fault occurs
        if (!found)
        {
            pageFaults++;
            printf("(Page Fault number %d) ", pageFaults);

            for (j = 0; j < FRAME_SIZE - 1; j++)
            {
                frame[j] = frame[j + 1];
            }
            frame[FRAME_SIZE - 1] = pages[i];
        }

        // Print frame content after each page insertion
        printf("Page %d -> Frames: ", pages[i]);
        for (j = 0; j < FRAME_SIZE; j++)
        {
            if (frame[j] != -1)
                printf("%d ", frame[j]);
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("Total Page Faults (LRU): %d\n", pageFaults);
}

void pageReplacementOptimal(int pages[], int n)
{
    // Initialize the frame with -1 values (indicating empty slots)
    int frame[FRAME_SIZE] = {-1, -1, -1};
    int pageFaults = 0; // Counter for page faults

    // Loop through each page in the reference string
    for (int i = 0; i < n; i++)
    {
        int isPageInFrame = 0;

        // Check if the current page is already in any frame slot
        for (int j = 0; j < FRAME_SIZE; j++)
        {
            if (frame[j] == pages[i])
            {
                isPageInFrame = 1; // Page found in frame, no replacement needed
                break;
            }
        }

        // If the page is not found in the frame, we have a page fault
        if (!isPageInFrame)
        {
            int optimalIndex = -1, farthest = -1;

            // Loop to find the frame slot that will be used farthest in the future
            for (int j = 0; j < FRAME_SIZE; j++)
            {
                int usage = -1;

                // Check when this frame's page will be used next
                for (int k = i + 1; k < n; k++)
                {
                    if (frame[j] == pages[k])
                    {
                        usage = k;
                        break;
                    }
                }

                // If a page is not used again, choose this frame slot
                if (usage == -1)
                {
                    optimalIndex = j;
                    break;
                }

                // Find the page with the farthest usage in the future
                if (usage > farthest)
                {
                    farthest = usage;
                    optimalIndex = j;
                }
            }

            // Replace the frame slot page with the current page
            frame[optimalIndex] = pages[i];
            pageFaults++;
            printf("(Page Fault number %d) ", pageFaults);
        }

        // Display the frame's current state
        printf("Page %d -> Frames: ", pages[i]);
        for (int j = 0; j < FRAME_SIZE; j++)
        {
            if (frame[j] != -1)
                printf("%d ", frame[j]);
            else
                printf("- ");
        }
        printf("\n");
    }

    // Print total number of page faults
    printf("Total Page Faults (Optimal): %d\n", pageFaults);
}
