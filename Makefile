# Main Makefile

# Define subdirectories
Q1 = Question_1
Q2 = Question_2
Q3 = Question_3
Q4 = Question_4
Q5 = Question_5
# List of subdirectories
SUBDIRS = $(Q1) $(Q2) $(Q3) $(Q4) $(Q5)
# Default target
all: $(SUBDIRS)

# Phony targets
.PHONY: all $(SUBDIRS) clean

all: $(SUBDIRS)

# Phony targets to avoid conflicts with files of the same name
.PHONY: all $(SUBDIRS) clean

# Target for each subdirectory
$(SUBDIRS):
	$(MAKE) -C $@

# Clean target
clean:
	for dir in $(SUBDIRS); do \
	    $(MAKE) -C $$dir clean; \
	donefi
