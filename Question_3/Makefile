CC = gcc
Flags = -Wall -g -Wextra
LIBS = -L. -lpoisson -lm # Add -lm to link against the math library

all: main libpoisson.so

main: main.o libpoisson.so
	$(CC) $(Flags) -o main main.c $(LIBS)

main.o: main.c targil3.c
	$(CC) $(Flags) -c $^

libpoisson.so: targil3.c
	$(CC) $(Flags) -shared -o libpoisson.so -fPIC -c targil3.c

.PHONY: clean all

clean:
	rm -f main libpoisson.so *.o
