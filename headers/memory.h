/************
 * memory.h
 ************/

#include "system.h"

#ifndef MEMORYHEADER
#define MEMORYHEADER

#define MAXNODES 5

struct block {
  int val;
  int auth;
};
#define B_SIZE sizeof(struct block)

typedef struct block *shared_memory;

struct block *new_block();
shared_memory new_shared_mem(int N);

int read_block(struct block *container, int id, shared_memory shared_block);
int write_block(struct block *data, int id, shared_memory shared_block);
int wipe_block(struct block *target);

#endif /* MEMORYHEADER */
