/*************************************************
 * dict.h
 *
 * Closely adapted from the dictionary
 * example in K&R's 'The C Programming Language.'
 *************************************************/
#ifndef HASHSIZE
#define HASHSIZE 101
#endif

#ifndef DICTHEADER
#define DICTHEADER

struct nlist { /* table entry: */
  struct nlist *next; /* next entry in chain */
  char *name; /* defined name */
  char *defn; /* replacement text */
};
typedef struct nlist *dict;
#define DICTSIZE (sizeof(struct nlist) * HASHSIZE)

dict new_dict(int custom_size);
unsigned hash (char *s, int hashsize);
char *lookup(char *s);
struct nlist *install(char *name, char *defn);

#endif /* DICTHEADER */
