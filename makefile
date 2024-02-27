CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# List of source files
SRCS = Main.c StrList.c

# List of header files
HDRS = StrList.h

# List of object files
OBJS = $(SRCS:.c=.o)

# Executable name
EXEC = main

# Rule to build the executable
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to build object files from source files
%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c -o $@ $<

# Phony target to clean the project
clean:
	rm -f $(OBJS) $(EXEC)