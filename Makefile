# General Makefile for small C programs
# Based on one by Alexender Hiam in Jan 2013
# Jim Mahoney | Jan 2016 | Public Domain

############################################################
# Modify these to fit your project.

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

tests:
	cd tests && make all
