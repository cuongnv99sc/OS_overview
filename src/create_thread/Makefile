# Determine the operating system
UNAME_S := $(shell uname -s)

# Set compiler and flags based on OS
ifeq ($(UNAME_S),Darwin)
    CC = clang
else
    CC = gcc
endif

CFLAGS = -Wall -Wextra -Werror -lpthread

# Find all source files in current directory
SRCS := $(wildcard *.c)
BINS := $(SRCS:.c=)

# Targets
all: $(BINS)

# Generic rule for compiling each .c file to a binary
%: %.c
	$(CC) -o $@ $< $(CFLAGS)

# Clean target
clean:
	rm -f $(BINS)

# Phony targets
.PHONY: all clean
