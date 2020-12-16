# General Makefile for small C programs
# Based on one by Alexender Hiam in Jan 2013
# Jim Mahoney | Jan 2016 | Public Domain

############################################################
# Modify these to fit your project.

# The name of the target executable
TARGET  = tests/L1tests

# Space separated list of all source files
SOURCES = src/sys/l1tests.c src/memory.c src/messages.c src/sys/utils.c

# Space separated directories containing source files
INCLUDE_DIRS = headers

# Compiler flags (e.g. optimization, links, etc.):
CFLAGS = -O2 -g -w

# Compiler:
CC = gcc

############################################################
# You probably won't need to change this part.

# Append -I to each include dir
INCLUDES = $(foreach dir, $(INCLUDE_DIRS), -I$(dir))

# Create list of the object files
OBJECTS = $(SOURCES:.c=.o)

all: $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJECTS) -o $(TARGET) -lrt
	make clean

%.o: %.c
	@echo "Compiling $<"
	$(CC) -c $(CFLAGS) $(INCLUDES) -o $@ $< -lrt

clean:
	@echo "Cleaning"
	rm -f *.o *.d
	cd src && rm -f *.o
	cd src/sys && rm -f *.o
