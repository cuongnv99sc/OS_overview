# Determine the operating system
UNAME_S := $(shell uname -s)

# Set compiler based on OS
ifeq ($(UNAME_S),Darwin)
    CC = clang
else
    CC = gcc
endif

# Compiler flags
#CFLAGS = -Wall -Wextra -Werror -Iinclude


all:
	$(CC) -o process_heap_size process_heap_size.c
# Clean target
clean:
	rm -f process_heap_size

# Phony targets
.PHONY: all clean