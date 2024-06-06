#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    size_t allocation_size = 1024 * 1024 * 1024; //1Gbyte
    size_t total_allocated = 0;
    void *memory_block;

    memory_block = malloc(allocation_size);
    while (1) {
        memory_block = malloc(allocation_size);

        if (memory_block == NULL) {
            printf("Total allocated memory size: %zu GB\n", total_allocated / (1024 * 1024 * 1024));
            break;
        }

        total_allocated += allocation_size;
        printf("Allocation: %zu GB\n", total_allocated / (1024 * 1024 * 1024));
    }

    while(1) {usleep(100);}
    return 0;
}