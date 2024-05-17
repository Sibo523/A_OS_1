# Define the base name for executables (without extension)
TARGET = main

# Define the header file
HEADER = header.h

CC = gcc
Flags = -Wall -pg -Wextra -lm

# Define variants
VARIANTS = _q_n _q_n2 _q_n3
SIZES = 100 1000 10000
PROFILE_DIR = Profiling
all: $(VARIANTS)


# Rule to compile each variant of main executable
$(VARIANTS): %: main.o %.o
	$(CC) $(Flags) -o $@ $^

# Rule to compile each .c file into an object file
%.o: %.c $(HEADER)
	$(CC) $(Flags) -c -o $@ $<

run: all
	@for variant in $(VARIANTS); do \
		for size in $(SIZES); do \
			./$$variant 420 $$size; \
			gprof $$variant gmon.out > $(PROFILE_DIR)/$${variant}_profile_$${size}; \
			rm -f gmon.out; \
		done \
	done

.PHONY: clean
clean:
	rm -f $(VARIANTS) *.o gmon.out 
#	rm -rf $(PROFILE_DIR)/* 
#	^Depends if I want to keep the profiling files or not!/
#  	-rf is recursive force
