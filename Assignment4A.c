#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define BUFFER_SIZE 5
#define NUM_PRODUCERS 4
#define NUM_CONSUMERS 4
#define NUM_ITEMS 10

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;
sem_t empty;
sem_t full;
pthread_mutex_t mutex;
void *producer(void *arg)
{
    for (int i = 0; i < NUM_ITEMS; i++)
    {
        int item = rand() % 100;
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[in] = item;
        printf("Producer %ld produced: %d\n", (long)arg, item);
        in = (in + 1) % BUFFER_SIZE;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        sleep(rand() % 2);
    }
    return NULL;
}
void *consumer(void *arg)
{
    for (int i = 0; i < NUM_ITEMS; i++)
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        int item = buffer[out];
        printf("Consumer %ld consumed: %d\n", (long)arg, item);
        out = (out + 1) % BUFFER_SIZE;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        sleep(rand() % 3);
    }
    return NULL;
}
int main()
{
    pthread_t producers[NUM_PRODUCERS], consumers[NUM_CONSUMERS];

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    for (long i = 0; i < NUM_PRODUCERS; i++)
    {
        pthread_create(&producers[i], NULL, producer, (void *)i);
    }

    for (long i = 0; i < NUM_CONSUMERS; i++)
    {
        pthread_create(&consumers[i], NULL, consumer, (void *)i);
    }

    for (int i = 0; i < NUM_PRODUCERS; i++)
    {
        pthread_join(producers[i], NULL);
    }

    for (int i = 0; i < NUM_CONSUMERS; i++)
    {
        pthread_join(consumers[i], NULL);
    }

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
    return 0;
}