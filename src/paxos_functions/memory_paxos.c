/******************
 * memory_paxos.c
 ******************/

#include "paxos_functions.h"
#include "memory.h"

int communicate(proc_info self)
{
  if ((self->cid == 0) || (self->role == ACCEPT))
    return 0;
  struct block *read = scalloc(1, B_SIZE);
  for (int i; i < self->M; i++) {
    if (i != IND(self->pid)) {
      read_block(self->read, i, self->smem);
      if (read->cid > self->cid) {
	self->highest_seen = read->cid;
	free(read);
	self->role = ACCEPT;
	return 0;
      }
      else if ((read->id >= self->highest_old_id) && (self->role == PREPARE)) {
	self->highest_old_id = read->id;
	self->old_id_val = read->val;
      }
    }
  }
  free(read);
  if (self->role == PREPARE) {
    self->role = PROPOSE;
    return MSG_PROM;
  } else {
    return MSG_END;
  }
}

int acc_prom(proc_info self)
{
  return 1;
}

int prepare(proc_info self)
{
  self->role = PREPARE;
  self->cid = RID(self->round, self->pid, self->M);
  while (self->cid < self->highest_seen) {
    self->round++;
    self->cid = RID(self->round, self->pid, self->M);
  }
  struct block *write = scalloc(1, B_SIZE);
  write->cid = self->cid;
  write_block(write, IND(self->pid), self->smem);
  free(write);
  return 0;
}

int propose(prop_info self)
{
  self->role = PROPOSE;
  self->accepted_id = self->cid;
  if (self->old_id_val != NO_VAL)
    self->accepted_val = self->old_id_val;
  else
    self->accepted_val = self->pid;
  struct block *write = scalloc(1, B_SIZE);
  write->cid = self->cid;
  write->id = self->accepted_id;
  write->val = self->accepted_val;
  write_block(write, IND(self->pid), self->smem);
  free(write);
  return 0;
}
