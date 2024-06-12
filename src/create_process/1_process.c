#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main() {
    pid_t pid;
    pid = fork();
    if (pid < 0) { 
        fprintf(stderr, "Fork failed");
        return 1;
    }
    else if (pid == 0) { 
        printf("This is the child process! PID: %d\n", getpid());
    }
    else { 
        printf("This is the parent process! PID: %d\n", getpid());
        printf("Child process ID: %d\n", pid);
    }
    return 0;
}
