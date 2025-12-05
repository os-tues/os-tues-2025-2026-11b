#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    unsigned int N;
    int data;
    pthread_mutex_t mutex;
} args_t;

void *increment_N_times(void *args);

int main(int argc, char const *argv[]) {
    // pthread_mutex_t mutex;
    // pthread_mutex_init(&mutex, NULL);

    args_t args = {atoi(argv[1]), 0, PTHREAD_MUTEX_INITIALIZER};

    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    pthread_t thread;
    pthread_create(&thread, NULL, increment_N_times, &args);


    increment_N_times(&args);
    pthread_join(thread, NULL);

    printf("%d\n", args.data);
    return 0;
}

void *increment_N_times(void *args) {
    args_t *parsed_args = args;
    for (unsigned i = 0; i < parsed_args->N; i++) {
        // lock
        pthread_mutex_lock(&parsed_args->mutex);

        // (*parsed_args)++;
        parsed_args->data = parsed_args->data + 1;

        // unlock
        pthread_mutex_unlock(&parsed_args->mutex);
    }
    return NULL;
}