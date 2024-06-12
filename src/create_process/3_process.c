#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2;
    
    pid1 = fork();
    if (pid1 < 0) { 
        fprintf(stderr, "Fork failed");
        return 1;
    } else if (pid1 == 0) { 
        execl("./child1", "child1", NULL); 
        fprintf(stderr, "Exec failed for child1");
        return 1;
    }

    pid2 = fork();
    if (pid2 < 0) { 
        fprintf(stderr, "Fork failed");
        return 1;
    } else if (pid2 == 0) { 
        execl("./child2", "child2", NULL); 
        fprintf(stderr, "Exec failed for child2");
        return 1;
    }

    wait(NULL);
    wait(NULL);

    printf("Parent process finished.\n");
    return 0;
}

