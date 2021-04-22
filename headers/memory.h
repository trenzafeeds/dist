/************
 * memory.h
 ************/

#include "system.h"

#ifndef MEMORYHEADER
#define MEMORYHEADER
//#define MEMORY -- Should be defined by Makefile

#ifdef MEMORY
#define TIMEOUT 1
#endif

#define IND(i) (i - FIRSTID)

struct block {
  int cid;
  int id;
  int val;
};
#define B_SIZE sizeof(struct block)

typedef struct block *shared_memory;

struct mem_arg {
  int id;
  shared_memory smem;
};
#define MEM_ARG_SIZE sizeof(struct mem_arg)

#ifdef MEMORY
typedef struct _proc_info *proc_info;
struct _proc_info {
  int pid;
  int round;
  int cid;
  int role;
  int M;

  int highest_seen;

  int highest_old_id;
  int old_id_val;

  int accepted_id;
  int accepted_val;
  
  shared_memory smem;
};
#define PROC_INFO_SIZE sizeof(struct _proc_info);
#endif

struct block *new_block();
shared_memory new_shared_mem(int N);

int read_block(struct block *container, int id, shared_memory shared_block);
int write_block(struct block *data, int id, shared_memory shared_block);
int wipe_block(struct block *target);

#endif /* MEMORYHEADER */
