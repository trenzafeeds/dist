/********************
 * message_node.c
 ********************/

#include "node.h"
#include "messages.h"

pthread_barrier_t bar;

void node(struct args *argstruct)
{
  int ret;
  proc_info myinfo = scalloc(1, PROC_INFO_SIZE);
  myinfo->pid = argstruct->id;
  myinfo->M = argstruct->nodecount;
  char *myq = nid(argstruct->id);
  myinfo->listen = init_queue(myq, O_NONBLOCK, MAXMSG, M_SIZE);
  int cleared = clear_queue(myinfo->listen);
  debug("Thread %d cleared %d messages.", myinfo->pid, cleared);

  debug("thread %d starting wait", myinfo->pid);
  pthread_barrier_wait(&bar);
  debug("thread %d back from wait", myinfo->pid);
  
  while ((ret = paxos(myinfo)) == -1)
    sleep(1);

  debug("Thread %d decided on %d as leader.", myinfo->pid, ret);
  close_queue(myinfo->listen);
  mq_unlink(myq);
  free(myinfo);
  return; 
}
