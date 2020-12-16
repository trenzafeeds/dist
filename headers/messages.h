/****************
 * messages.h
 ****************/

#include "system.h"

/* POSIX Messages Libraries */
#include <mqueue.h>
#include <fcntl.h>

#define DESCSIZE 4
#define DESCPREF "/_"

#define MAXMSG 5

#ifndef MESSAGESHEADER
#define MESSAGESHEADER

typedef struct _message *message;
struct _message {
  int m_val;
  int m_auth;
};
#define M_SIZE sizeof(struct _message)

message new_message(int value, int author);
int send_m(message m_content, int *dests, int N);
message receive_m(mqd_t mqdes);

char *nid(int id);
mqd_t init_queue(char *desc, long flags, long m_max, long m_size);
mqd_t open_queue(char *desc, int permissions);
int close_queue(mqd_t mq_des);

#endif /* MESSAGESHEADER */
