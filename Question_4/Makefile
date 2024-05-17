# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -O2 -fprofile-arcs -ftest-coverage

# Target executable
TARGET = dijkstra

# Source files
SRCS = dijkstra.c

# Object files
OBJS = $(SRCS:.c=.o)

# Default rule
all: $(TARGET)

# Rule to build the target executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to build object files
%.o: %.c./
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to clean build files
clean:
	rm -f $(TARGET) $(OBJS) *.gcno *.gcda *.gcov dijk

# Rule to run gcov for code coverage
coverage: all
#use the vvvv if it doesn't work
# chmod +x test.sh
	./test.sh
	gcov $(SRCS)
# cat dijkstra.c.gcov 
# 	^^^This is to see the coverage of the code

# Explanation: technicaly at the start I needed it but now I don't need so if you have a problem you can use this :)
#chmod: is a command used to change the permissions of files and directories.
# +x: This adds the execute permission to the file.
# test.sh: This is the name of the file whose permissions are being modified.


.PHONY: all clean coverage