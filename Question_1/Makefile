CC = gcc 
Flags = -Wall -g -Wextra

all: file1 file2 file3 targil2

file1: file1.c
	$(CC) $(Flags) -o file1 file1.c
file2: file2.c
	$(CC) $(Flags) -o file2 file2.c
file3: file3.c
	$(CC) $(Flags) -o file3 file3.c
targil2: targil2.c
	$(CC) $(Flags) -o targil2 targil2.c -lm
Phony: clean all 
clean:
	rm -f file1 file2 file3