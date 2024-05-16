# Define the base name for executables (without extension)
TARGET = main

# Define the header file
HEADER = header.h

CC = gcc
all: _q_n _q_n^2 _q_n^3
# Define compiler flags for debugging and profiling
Flags = -Wall -pg -Wextra -lm

# Rule to compile each .cpp file into an object file
%.o: %.c $(HEADER)
	$(CC) $(Flags) -c -o $@ $<

# Rule to compile each variant of main executable
_q_n: main.o q_n.o
	$(CC) $(Flags) -o $@ $^

_q_n^2: main.o q_n^2.o
	$(CC) $(Flags) -o $@ $^

_q_n^3: main.o q_n^3.o
	$(CC) $(Flags) -o $@ $^
run: all3
	./_q_n 4 10000
	gprof _q_n gmon.out > _q_n_profile.txt
	rm -f gmon.out

	./_q_n2 4 100
	gprof _q_n2 gmon.out > _q_n2_profile.txt
	rm -f gmon.out

	./_q_n3 4 100
	gprof _q_n3 gmon.out > _q_n3_profile.txt
	rm -f gmon.out
.PHONY: clean
clean:
	rm -f _q_n* *.o gmon.out

