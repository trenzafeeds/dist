/************
 * node.h
 ************/

#include "paxos.h"

#ifndef NODEH
#define NODEH

struct args {
  int id;
  int nodecount;
  void *extra;
};
#define ARGSIZE sizeof(struct args)

pthread_cond_t setup;
pthread_mutex_t lock;

void node(struct args *argstruct);

#endif /* NODEH */
