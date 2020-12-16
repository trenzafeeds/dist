/************
 * l1tests.c
 ************/

#include "l1tests.h"

int memtest(int nodes)
{
  int tval = 5;
  int tauth = 1;
  int tblockid = 1;
  int ret;
  
  printf("Starting L1 shared memory test...\n");
  shared_memory smem = new_shared_mem(nodes);
  debug("Created shared block for %i processes.", nodes);
  
  struct block *wblock = new_block();
  wblock->val = tval;
  wblock->auth = tauth;
  ret = write_block(wblock, tblockid, smem);
  debug("write_block returned %i.", ret);

  ret = wipe_block(wblock);
  debug("wipe_block returned %i.", ret);

  ret = read_block(wblock, tblockid, smem);
  debug("read_block returned %i.", ret);

  if ((wblock->val == tval) && (wblock->auth == tauth)) {
    printf("L1 shared memory test successful.\n");
    ret = 0;
  } else {
    printf("L1 shared memory test failed, check debug log for details.\n");
    ret = 1;
  }

  free(smem);
  free(wblock);
  return ret;
}

int messagetest()
{
  int qid = 101;
  long qflags = O_CREAT | O_RDWR | O_NONBLOCK;
  int tval = 5;
  int tauth = 1;
  int ret;

  printf("Starting L1 message passing test...\n");
  mqd_t mqueue = init_queue(nid(qid), qflags, MAXMSG, M_SIZE);
  debug("Initiated test message queue %s with id %i.", nid(qid), qid);

  message tmessage = new_message(tval, tauth);
  ret = send_m(tmessage, &qid, 1);
  debug("send_m returned %i.", ret);

  message rmessage = receive_m(mqueue);
  if (rmessage == -1)
    debug("recieve_m failed.");
  else {
    debug("recieve_m returned successfully.");
    if ((rmessage->m_val == tval) && (rmessage->m_auth == tauth)) {
      printf("L1 message passing test successful.\n");
      ret = 0;
    } else {
      printf("L1 message passing test failed, check debug log for details.\n");
      ret = 1;
    }
  }

  free(tmessage);
  mq_unlink(nid(qid));
  return ret;
}

int main()
{
  int rc = 0;
  debug("Debug messages enabled.");
  rc += memtest(5);
  rc += messagetest();
  return rc;
}