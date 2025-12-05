#include <stdio.h>
#include <pthread.h>
#define BUFFER_SIZE 10
#define CONSUME_N_TIMES 1
#define PRODUCE_N_TIMES 1

void *producer(void *args);
void *consumer(void *args);
void print_buffer(int *buffer);

typedef struct {
    int *buffer;
    int *current_buffer_size;
} thread_args_t;

int main(int argc, char const *argv[])
{
    int buffer[BUFFER_SIZE] = {0};
    int current_buffer_size = 0;
    const int CONSUMER_COUNT = 10;
    const int PRODUCER_COUNT = 10;

    thread_args_t args = {buffer, &current_buffer_size};

    print_buffer(buffer);

    pthread_t consumer_threads[CONSUMER_COUNT];
    pthread_t producer_threads[PRODUCER_COUNT];

    for (unsigned int i = 0; i < CONSUMER_COUNT; i++) {
        pthread_create(&consumer_threads[i], NULL, consumer, &args);
    }

    for (unsigned int i = 0; i < PRODUCER_COUNT; i++) {
        pthread_create(&producer_threads[i], NULL, producer, &args);
    }

    for (unsigned int i = 0; i < CONSUMER_COUNT; i++) {
        pthread_join(consumer_threads[i], NULL);
    }

    for (unsigned int i = 0; i < PRODUCER_COUNT; i++) {
        pthread_join(producer_threads[i], NULL);
    }
    print_buffer(&buffer);

    return 0;
}

void *producer(void *args) {
    thread_args_t parsed_args = * (thread_args_t *)args;

    for (unsigned int i = 0; i < PRODUCE_N_TIMES; i++) {
        // parsed_args.buffer[*(parsed_args.current_buffer_size)++] = 1;
    }

    printf("Producer\n");
    printf("%d\n", *(parsed_args.current_buffer_size));
    return NULL;
}

void *consumer(void *args) {
    printf("Consumer\n");
    return NULL;
}

void print_buffer(int *buffer) {
    printf("[ ");
    for (unsigned int i = 0; i < BUFFER_SIZE; i++) {
        printf("%d ", buffer[i]);
    }
    printf(" ]\n");
}