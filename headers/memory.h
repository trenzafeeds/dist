/************
 * memory.h
 ************/

#include "system.h"

#ifndef MEMORYHEADER
#define MEMORYHEADER

struct block {
  int val;
  int auth;
};
#define B_SIZE sizeof(struct block)

typedef struct block *shared_memory;

struct block *new_block();
shared_memory new_shared_mem(int N);

struct block *read_block(int id, shared_memory shared_block);
int write_block(struct block *data, int id, shared_memory shared_block);
int wipe_block(int id, shared_memory shared_block);

#endif /* MEMORYHEADER */
