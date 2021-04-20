# General Makefile for small C programs
# Based on one by Alexender Hiam in Jan 2013
# Jim Mahoney | Jan 2016 | Public Domain

############################################################
# Modify these to fit your project.

# Functions
prep_path = $(foreach path, $(2), $(1)/$(path))

# Space separated directories containing source files
INCLUDE_DIRS = ../headers
SRC_DIR = ../src

SYS_SOURCES = sys/utils.c threads.c paxos/driver.c
SYS_ALL := $(call prep_path, $(SRC_DIR), $(SYS_SOURCES))

MESSAGE_T = message_paxos
MESSAGE_SOURCES = messages.c paxos_functions/message_paxos.c \
nodes/message_node.c
MESSAGE_ALL = $(SYS_ALL) $(call prep_path, $(SRC_DIR), $(MESSAGE_SOURCES))

RING_T = ring_paxos
RING_SOURCES = messages.c paxos_functions/ring_paxos.c \
nodes/message_node.c
RING_ALL = $(SYS_ALL) $(call prep_path, $(SRC_DIR), $(RING_SOURCES))
# Compiler flags (e.g. optimization, links, etc.):
CFLAGS = -O2 -g -Wall -lrt -lpthread

# Compiler:
CC = gcc

############################################################
# You probably won't need to change this part.

# Append -I to each include dir
INCLUDES := $(foreach dir, $(INCLUDE_DIRS), -I$(dir))
CFLAGS += $(INCLUDES)

# Create list of the object files
MESSAGE_OBJ = $(MESSAGE_ALL:.c=.o)
RING_OBJ = $(RING_ALL:.c=.o)

paxos_message : ../src/paxos/paxos.c
	$(CC) $(CFLAGS) $(INCLUDES) -include messages.h -c \
../src/paxos/paxos.c -o ../src/paxos/paxos_message.o

%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

messages: $(MESSAGE_OBJ) paxos_message
	$(CC) $(CFLAGS) $(MESSAGE_OBJ) ../src/paxos/paxos_message.o -o $(MESSAGE_T)

ring: $(RING_OBJ) paxos_message
	$(CC) $(CFLAGS) $(RING_OBJ) ../src/paxos/paxos_message.o -o $(RING_T)
