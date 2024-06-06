#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define NUM_THREAD 5

typedef struct sched_param sched_param_t;
volatile int running_threads = 0;
static pthread_t thread_arr[NUM_THREAD + 1];
static pthread_attr_t thread_attr_arr[NUM_THREAD + 1];
static sched_param_t param[NUM_THREAD + 1];
static int policy = SCHED_FIFO;
static pthread_mutex_t mutex;
static pthread_cond_t cond;

void* masterThread(void* arg) {
    sched_param_t* input = (sched_param_t*)arg;
    printf("Master thread %d is running.\n", input->sched_priority);
    while (running_threads < NUM_THREAD)
		usleep(1000);
    usleep(1000);

    printf("Master thread about to wake another threads.\n");
    pthread_mutex_lock(&mutex);
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&mutex);

    return NULL;
}

void* threadFunc(void* arg) {
    pthread_mutex_lock(&mutex);
    sched_param_t* input = (sched_param_t*)arg;
    printf("Thread %d is running.\n", input->sched_priority);
	running_threads++;
	pthread_cond_wait(&cond, &mutex);
    printf("Thread %d is received signal.\n", input->sched_priority);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    int res = 0;

    for (int i = 0; i <= NUM_THREAD; i++) {
        pthread_attr_init(&thread_attr_arr[i]);
        pthread_attr_setinheritsched(&thread_attr_arr[i], PTHREAD_EXPLICIT_SCHED);
        pthread_attr_setschedpolicy(&thread_attr_arr[i], policy);

         // Set different priorities for each thread
        param[i].sched_priority = i + 1; 
        pthread_attr_setschedparam(&thread_attr_arr[i], &param[i]);
    }

    for (int i = 0; i < NUM_THREAD; i++) {
        res = pthread_create(&thread_arr[i], 
                        &thread_attr_arr[i], 
                        threadFunc, 
                        (void*)&param[i]);

        if(res != 0) printf("Error creating thread: %s\n", strerror(res));
    }

    res = pthread_create(&thread_arr[NUM_THREAD], 
                    &thread_attr_arr[NUM_THREAD], 
                    masterThread, 
                    (void*)&param[NUM_THREAD]);
    if(res != 0) printf("Error creating thread: %s\n", strerror(res));

    for (int i = 0; i <= NUM_THREAD; i++) {
        pthread_join(thread_arr[i], NULL);
        pthread_attr_destroy(&thread_attr_arr[i]);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    printf("\nCriteria: Threads should be woken up in priority order\n");
    return 0;
}

