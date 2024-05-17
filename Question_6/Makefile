CC = gcc 
Flags = -Wall -g -Wextra

all: add2PB findPhone

add2PB: add2PB.c 
	$(CC) $(Flags) -o $@ $^
findPhone: findPhone.c
	$(CC) $(Flags) -o $@ $^

Phony: clean all 
clean:
	rm -f add2PB findPhone