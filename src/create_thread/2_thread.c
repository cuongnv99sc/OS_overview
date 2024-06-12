#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void* threadFunction() {
    printf("Thread is running\n");
    // Do some work in the thread
    return NULL;
}

int main() {
    pthread_t thread;
    pthread_attr_t attr;
    struct sched_param param;

    pthread_attr_init(&attr);
    pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
    param.sched_priority = 1;
    pthread_attr_setschedparam(&attr, &param);

    if (pthread_create(&thread, &attr, threadFunction, NULL) != 0) {
        perror("Failed to create thread");
        return 1;
    }

    pthread_join(thread, NULL);

    pthread_attr_destroy(&attr);

    printf("Thread has finished executing\n");
    return 0;
}

