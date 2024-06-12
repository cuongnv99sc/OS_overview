#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#define NUM_CHILDREN 3
int main() {
    pid_t pid;
    int i;
    for (i = 0; i < NUM_CHILDREN; i++) {
        pid = fork();
        if (pid < 0) { 
            fprintf(stderr, "Fork failed");
            return 1;
        } else if (pid == 0) { 
            printf("Child %d: PID = %d, Parent PID = %d\n", i, getpid(), getppid());
            sleep(2); 
            exit(0); 
        }
    }
    for (i = 0; i < NUM_CHILDREN; i++) {
        pid_t wpid = wait(NULL); 
        printf("Parent: Child with PID = %d has finished\n", wpid);
    }
    printf("Parent process finished.\n");
    return 0;
}

