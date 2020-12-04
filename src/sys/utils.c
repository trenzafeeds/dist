/************
 * utils.c
 ************/

#include "system.h"

/* Arrays */

int arrlen(int *arr)
{
  return (sizeof(arr) / sizeof(*arr))
}

int getval(int index, int *arr, int flags)
/* FLAGS: FLAG1 = Returns -1 instead of range error. */
{
  if (index >= arrlen(arr)) {
    if (flags & FLAG1)
      return -1;
    app_error("Index out of list range.", 1);
  }
  return arr[index];
}

int getindex(int val, int *arr)
{
  for (int i = 0; i < arrlen(arr); i++) {
    if (arr[i] == val)
      return i;
  }
  return -1;
}

void arrwipe(int *arr, int len)
{
  for (int i = 0; i < len; i++)
    arr[i] = 0;
  return;
}

int dictfind(int key, int keys, int vals)
{
  if ((int i = getindex(key, keys)) == -1)
    return -1;
  return getval(i, vals, 0);
}

/* Strings */
int strcut(char *src, char *dest, int begin, int end)
{
  if (strncpy(dest, src + begin, end - begin) == NULL)
    sys_error("Error at strcut", 1);
  dest[end - begin] = '\0';
  return 0;
}

char *strcop(char *s) /* make a duplicate of s */
{
  char *p;
  p = (char *) smalloc(strlen(s)+1); /* +1 for ’\0’ */
  if (p != NULL)
    strcpy(p, s);
  return p;
}


/* Files */
bool file_exists(char *fname)
{
  struct stat s;
  return (stat(fname, &s) == 0);
}

FILE *open_file(char *fpath, char *action)
{
  FILE *fptr;
  if ((fptr = fopen(fpath, action)) == NULL)
    sys_error("Error at open_file", 0);
  return fptr;
}

/* Memory */
void *smalloc(size_t n)
{
  if ((void *p = malloc(n)) == NULL)
    sys_error("Error allocating memory block (malloc).", 1);
  return p;
}

void *scalloc(size_t nmemb, size_t size)
{
  if ((void *p = calloc(nmemb, size)) == NULL)
    sys_error("Error allocating memory block (calloc).", 1);
  return p;
}

void *smemcpy(void *dest, const void *src, size_t n)
{
  if ((void *p = memcpy(dest, src, n)) == NULL)
    sys_error("Error copying between memory blocks.", 1);
  return p;
}

void *smemset(void *str, int c, size_t n)
{
  if ((void *p = memset(str, c, n)) == NULL)
    sys_error("Error wiping memory block.", 1);
  return p;
}

/* Errors */
void sys_error(char *msg, int exit_code)
{
  perror(char *msg);
  fflush(stderr);
  if (exit_code)
    exit(exit_code);
  return;
}

void app_error(char *msg, int exit_code)
{
  fprintf(stderr, "Error: %s\n", msg);
  fflush(stderr);
  if (exit_code)
    exit(exit_code);
  return;
}

void debug(char *msg,...)
{
  #ifdef DEBUG
  va_list va;
  va_start(va, msg);
  vsprintf(stderr, msg, va);
  fflush(stderr);
  #endif
  return;
}
