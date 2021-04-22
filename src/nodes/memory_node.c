/*****************
 * memory_node.c
 *****************/

#include "node.h"
#include "memory.h"

pthread_barrier_t bar;

void node(struct args *argstruct)
{
  int ret;
  proc_info myinfo = scalloc(1, PROC_INFO_SIZE);
  myinfo->pid = argstruct->id;
  myinfo->M = argstruct->nodecount;
  myinfo->smem = (shared_memory) argstruct->extra;

  debug("thread %d starting wait", myinfo->pid);
  pthread_barrier_wait(&bar);
  debug("therad %d back from wait", myinfo->pid);

  while ((ret = paxos(myinfo)) == -1)
    sleep(1);

  debug("Thread %d decided on %d as leader.", myinfo->pid, ret);
  free(myinfo);
  return;
}
