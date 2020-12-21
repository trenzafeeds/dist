/**************
 * l1tests.h
 **************/

#include "system.h"
#include "memory.h"
#include "messages.h"
#include "threads.h"

#ifndef L1TESTSHEADER
#define L1TESTSHEADER

int memtest(int nodes);
int messagetest();
void *threadfunc(void *id);
int threadtest(int nodes);

int main();

#endif /* L1TESTSHEADER */
