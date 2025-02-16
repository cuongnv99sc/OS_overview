# Determine the operating system
UNAME_S := $(shell uname -s)

# Set compiler based on OS
ifeq ($(UNAME_S),Darwin)
    CC = clang
	CFLAGS = -Wall -Wextra -Werror -Iinclude
else
    CC = gcc
	CFLAGS = -Wall -Wextra -Werror -Iinclude -pthread
endif

# Compiler flags
#CFLAGS = -Wall -Wextra -Werror -Iinclude
#CFLAGS = -Wall

# Source files
SRC = $(wildcard src/*.c)

# Object files
OBJ = $(SRC:.c=.o)

# Output executable
TARGET = execute

# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

# Compile each source file into an object file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target
clean:
	rm -f $(OBJ) $(TARGET)

# Phony targets
.PHONY: all clean
