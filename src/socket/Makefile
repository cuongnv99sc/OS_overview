# Determine the operating system
UNAME_S := $(shell uname -s)

# Set compiler based on OS
ifeq ($(UNAME_S),Darwin)
    CC = clang
	CFLAGS = -Wall -Wextra -Werror
else
    CC = gcc
	CFLAGS = -Wall -Wextra -Werror -lpthread
endif

# Compiler flags
#CFLAGS = -Wall -Wextra -Werror -lpthread


all:
	$(CC) -o server server.c $(CFLAGS)
	$(CC) -o client client.c $(CFLAGS)
# Clean target
clean:
	rm -f client server

# Phony targets
.PHONY: all clean