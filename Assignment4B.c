#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define MAX_READERS 3
#define MAX_WRITERS 3

pthread_mutex_t rw_mutex;
pthread_mutex_t read_count_mutex;
int read_count = 0;
int data = 10;

void *reader(void *arg)
{
    long int rno;
    rno = (long int)arg;
    pthread_mutex_lock(&read_count_mutex);
    read_count++;
    pthread_mutex_unlock(&read_count_mutex);
    if (read_count == 0)
    {
        pthread_mutex_lock(&rw_mutex);
    }
    printf("Reader %ld entered critical section\n", rno);
    printf("Reader %ld is reading data %d\n", rno, data);
    pthread_mutex_lock(&read_count_mutex);
    read_count--;
    pthread_mutex_unlock(&read_count_mutex);
    if (read_count == 0)
    {
        pthread_mutex_unlock(&rw_mutex);
    }
    printf("Reader %ld existed critical section\n", rno);

    return NULL;
}

void *writer(void *arg)
{
    long int wno;
    wno = (long int)arg;

    pthread_mutex_lock(&rw_mutex);
    printf("writer %ld entered critical section\n", wno);

    printf("Writer %ld is writing data %d\n", wno, ++data);

    printf("Writer %ld existed critical section\n", wno);
    pthread_mutex_unlock(&rw_mutex);

    return NULL;
}

int main()
{
    pthread_t readers[MAX_READERS], writers[MAX_WRITERS];

    pthread_mutex_init(&rw_mutex, NULL);
    pthread_mutex_init(&read_count_mutex, NULL);

    for (long int i = 0; i < MAX_READERS; i++)
    {
        pthread_create(&readers[i], NULL, reader, (void *)i + 1);
    }

    for (long int i = 0; i < MAX_WRITERS; i++)
    {

        pthread_create(&writers[i], NULL, writer, (void *)i + 1);
    }

    for (int i = 0; i < MAX_READERS; i++)
    {
        pthread_join(readers[i], NULL);
    }

    for (int i = 0; i < MAX_WRITERS; i++)
    {
        pthread_join(writers[i], NULL);
    }

    pthread_mutex_destroy(&rw_mutex);
    pthread_mutex_destroy(&read_count_mutex);
    return 0;
}