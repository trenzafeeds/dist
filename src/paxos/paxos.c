/*************
 * paxos.c
 *************/

#include "paxos.h"

int paxos(proc_info self)
{
  int m_type;
  if ((m_type = communicate(self))) {
    self->timeout = 0;
    switch(m_type) {
    case MSG_PREP:
      debug("Thread %d received PREP", self->pid);
      acc_prep(self);
      break;
    case MSG_PROP:
      debug("Thread %d received PROP", self->pid);
      accept(self);
      debug("%d FINISHED ACCEPT", self->pid);
      break;
    case MSG_ACC:
      debug("Thread %d received ACC", self->pid);
      count_acc(self);
      break;
    case MSG_LEADER:
      debug("Thread %d received LEADER", self->pid);
      if (leader_count(self))
	return self->pid;
      break;
    case MSG_END:
      debug("Thread %d received END", self->pid);
      return self->accepted_val;
    default:
      if (m_type >= MSG_PROM) {
	debug("Thread %d received PROM", self->pid);
	if (acc_prom(self))
	  propose(self);
      } else {
	debug("Message type received %d", m_type);
	app_error("Unrecognized message type.", 1);
      }
    }
  } else {
    /*
    if (self->role == ACCEPT) {
      self->timeout++;
      if (self->timeout > self->M) {
	debug("TIMEOUT");
	self->timeout = 0;
	self->role = PREPARE;
      }
    }
    */
    if (self->role != ACCEPT) {
      debug("Thread %d sending PREPARE", self->pid);
      prepare(self);
    }
  }
  //fail(self);
  return -1;
}
