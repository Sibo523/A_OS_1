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
	chmod +x test.sh
	./test.sh
	gcov $(SRCS)


.PHONY: all clean coverage