#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* thread_function() {
    printf("Hello from the thread!\n");
    return NULL;
}

int main() {
    pthread_t thread_id;
    int result;

    result = pthread_create(&thread_id, NULL, thread_function, NULL);
    if (result != 0) {
        fprintf(stderr, "Error creating thread\n");
        exit(EXIT_FAILURE);
    }

    result = pthread_join(thread_id, NULL);
    if (result != 0) {
        fprintf(stderr, "Error joining thread\n");
        exit(EXIT_FAILURE);
    }

    printf("Thread has finished execution\n");
    return 0;
}
