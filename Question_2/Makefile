CC = gcc 
Flags = -Wall -g -Wextra
all: targil2 libpoisson.so

libpoisson.so: poisson.c
	$(CC) $(Flags) -shared -o libpoisson.so -fPIC poisson.c
targil2: targil2.c
	$(CC) $(Flags) -o targil2 targil2.c -lm

Phony: clean all 
clean:
	rm -f targil2