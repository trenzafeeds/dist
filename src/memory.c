/***********
 * memory.c
 ***********/

#include "paxos.h"

struct block *new_block()
{
  return smalloc(B_SIZE);
}

shared_memory new_shared_mem(int N)
{
  return scalloc(B_SIZE * N);
}

struct block *read_block(int id, shared_memory shared_block)
{
  struct block *data = smalloc(B_SIZE);
  return smemcopy(data, shared_block[id], B_SIZE);
}


/* The following functions do not throw errors, but return -1 on
 * failed memory operations.
 */
int write_block(struct block *data, int id, shared_memory shared_block)
{
  if (memcopy(shared_block[id], data, B_SIZE) == NULL) {
    debug("Failed to write to block %n.", id);
    return -1;
  } else
    return 0;
}

int wipe_block(int id, shared_memory shared_block)
{
  if (memset(shared_blocks[id], 0, B_SIZE) == NULL) {
    debug("Failed to wipe block %n.", id);
    return -1;
  } else
    return 0;
}
