/*************
 * driver.c
 *************/

#include "driver.h"
#define TESTNODES 5

pthread_barrier_t bar;

int main(int argc, char *argv[])
{
  int nodes;
  srandom(time(0));

  if (argc <= 1)
    nodes = TESTNODES;
  else {
    nodes = atoi(argv[1]);
    if (nodes > MAXNODES) {
      printf("Error: MAXNODES is currently %d. Recompile with larger MAXNODES.",\
             MAXNODES);
      exit(1);
    } else if (nodes < 5) {
      printf("Error: Sorry, Paxos only likes to be run with 5 or more nodes.\n");
      exit(1);
    }
  }
  debug("starting with %d nodes", nodes);

  struct args *targs = scalloc(nodes, ARGSIZE);
  void *pass[nodes];
  pthread_t *thread_array = new_thread_array(nodes);
  pthread_barrier_init(&bar, NULL, nodes);
  for (int i = 0; i < nodes; i++) {
    targs[i].id = FIRSTID + i;
    targs[i].nodecount = nodes;
    pass[i] = &targs[i];
  }
  debug("Here");
  create_threads(thread_array, nodes, NULL, &node, pass);
  sleep(1);
  pthread_cond_broadcast(&setup);
  debug("About to join");
  join_threads(thread_array, nodes, NULL);
  free(targs);
  free(thread_array);
  return 0;
}
