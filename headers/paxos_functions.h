/********************
 * paxos_functions.h
 ********************/

#include "system.h"

/* Message types */
/* Prepare statement */
#define MSG_PREP 1
/* Proposal AKA Accept Request */
#define MSG_PROP 2
/* Accept (acceptance of proposal) */
#define MSG_ACC 3
/* Teaching final value */
#define MSG_LEADER 4
/* Leader announcing round end */
#define MSG_END 5
/* Promise (or denial) */
#define MSG_PROM 6

#define RID(r, i, M) (i + (r*M))

/* Roles */
#define PREPARE 1
#define PROPOSE 2
#define ACCEPT 3

#define NO_VAL 0

#ifndef PFUNCTIONS
#define PFUNCTIONS

typedef struct _proc_info *proc_info;

char *type_to_name(int type);

int communicate(proc_info self);

int acc_prep(proc_info self);
int accept(proc_info self);
int count_acc(proc_info self);
int acc_prom(proc_info self);
int prepare(proc_info self);
int propose(proc_info self);
int leader_count(proc_info self);

int fail(proc_info self);

#endif /* PFUNCTIONS */
