
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    printf("This is child2 process. PID: %d\n", getpid());
    return 0;
}

