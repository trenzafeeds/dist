/***************
 * messages.c
 ***************/

#include "messages.h"

message new_message(int value, int author)
{
  message new_m = smalloc(M_SIZE);
  new_m->m_val = value;
  new_m->m_auth = author;
  return new_m;
}

int send_m(message m_content, int *dests)
{
  int retval = 0;
  for (int i = 0; i < arrlen(dests); i++) {
    char *path = nid(dests[i]);
    mqd_t target = open_queue(path, O_WRONLY);
    free(path);
    if (mq_send(target, (char *) m_content, M_SIZE, 0) == 1) {
      sys_error("Error at send_m", 0);
      retval = -1;
    }
    close_queue(target);
  }
  free(m_content);
  return retval;
}

message receive_m(mqd_t mqdes)
{
  message m_content = smalloc(M_SIZE);
  if (mq_receive(mqdes, (char *) m_content, M_SIZE, NULL) == -1)
    return -1;
  return m_content;
}

char *nid(int id)
{
  char *desc = scalloc(sizeof(char) * DESCSIZE);
  snprintf(desc, DESCSIZE, "%s%x", DESCPREF, id); // Prefix, then ID in hex
  return desc;
}

mqd_t init_queue(char *desc, long flags, long m_max, long m_size)
{
  mqd_t mq_des;
  mode_t mode = 0664;
  struct mq_attr attr;
  attr.mq_maxmsg = m_max;
  attr.mq_msgsize = m_size;
  if ((mq_des = mq_open(desc, flags, mode, &attr)) == -1)
    sys_error("Error at init_queue", 1);
  return mq_des;
}

mqd_t open_queue(char *desc, int permissions)
{
  mqd_t mq_des;
  if ((mq_des = mq_open(desc, permissions)) == -1)
    sys_error("Error at open_queue", 1);
  return mq_des;
}

int close_queue(mqd_t mq_des)
{
  int retval;
  if ((retval = mq_close(mq_des)) == -1)
    sys_error("Error at close_queue", 1);
  return retval; 
}