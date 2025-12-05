#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define BUFFER_SIZE 10
#define CONSUME_N_TIMES 1
#define PRODUCE_N_TIMES 100
#define MAX_SECONDS 1

void *producer(void *args);
void *consumer(void *args);
void print_buffer(int *buffer, int buffer_size);

typedef struct
{
    int *buffer;
    int *current_buffer_size;
    pthread_mutex_t *buffer_mutex;
} thread_args_t;

int main(int argc, char const *argv[])
{
    int buffer[BUFFER_SIZE] = {0};
    int current_buffer_size = 0;
    pthread_mutex_t buffer_lock = PTHREAD_MUTEX_INITIALIZER;

    const int CONSUMER_COUNT = 10;
    const int PRODUCER_COUNT = 10;

    thread_args_t args = {buffer, &current_buffer_size, &buffer_lock};

    pthread_t consumer_threads[CONSUMER_COUNT];
    pthread_t producer_threads[PRODUCER_COUNT];

    for (unsigned int i = 0; i < CONSUMER_COUNT; i++)
    {
        pthread_create(&consumer_threads[i], NULL, consumer, &args);
    }

    for (unsigned int i = 0; i < PRODUCER_COUNT; i++)
    {
        pthread_create(&producer_threads[i], NULL, producer, &args);
    }

    for (unsigned int i = 0; i < CONSUMER_COUNT; i++)
    {
        pthread_join(consumer_threads[i], NULL);
    }

    for (unsigned int i = 0; i < PRODUCER_COUNT; i++)
    {
        pthread_join(producer_threads[i], NULL);
    }
    // print_buffer(&buffer, current_buffer_size);

    return 0;
}

void *producer(void *args)
{
    thread_args_t parsed_args = *(thread_args_t *)args;

    for (unsigned int i = 0; i < PRODUCE_N_TIMES; i++)
    {
        pthread_mutex_lock(parsed_args.buffer_mutex);
        if (*parsed_args.current_buffer_size != BUFFER_SIZE)
        {
            parsed_args.buffer[(*(parsed_args.current_buffer_size))++] = 1;
        } else {
            printf("missfire\n");
        }
        printf("PRODUCE - ");
        print_buffer(parsed_args.buffer, *(parsed_args.current_buffer_size));
        pthread_mutex_unlock(parsed_args.buffer_mutex);
        sleep(rand() % MAX_SECONDS);
    }

    return NULL;
}

void *consumer(void *args)
{
    thread_args_t parsed_args = *(thread_args_t *)args;

    for (unsigned int i = 0; i < PRODUCE_N_TIMES; i++)
    {
        pthread_mutex_lock(parsed_args.buffer_mutex);
        if (*parsed_args.current_buffer_size != 0)
        {
            parsed_args.buffer[--(*(parsed_args.current_buffer_size))] = 0;
        } else {
            printf("missfire\n");
        }
        printf("CONSUME - ");
        print_buffer(parsed_args.buffer, *(parsed_args.current_buffer_size));
        pthread_mutex_unlock(parsed_args.buffer_mutex);
        sleep(rand() % MAX_SECONDS);
    }
    return NULL;
}

void print_buffer(int *buffer, int buffer_size)
{
    printf("[ ");
    for (unsigned int i = 0; i < BUFFER_SIZE; i++)
    {
        printf("%d ", buffer[i]);
    }
    printf(" ] - size = %d\n", buffer_size);
}