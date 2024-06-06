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
	$(CC) -o server server.c 
	$(CC) -o client client.c
# Clean target
clean:
	rm -f client server

# Phony targets
.PHONY: all clean