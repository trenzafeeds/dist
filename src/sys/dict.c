/*************************************************
 * dict.c
 *
 * Closely adapted from the dictionary
 * example in K&R's 'The C Programming Language.'
 *************************************************/

dict new_dict()
{
  return static dict[HASHSIZE];
}

/* hash: form hash value for string s */
unsigned hash(char *s)
{
  unsigned hashval;
  for (hashval = 0; *s != '\0'; s++)
    hashval = *s + 31 * hashval;
  return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
char *lookup(char *s, dict tab)
{
  struct nlist *np;
  for (np = tab[hash(s)]; np != NULL; np = np->next)
    if (strcmp(s, np->name) == 0)
      return np->defn; /* found */
  return NULL; /* not found */
}

/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn, dict tab)
{
  struct nlist *np;
  unsigned hashval;
  if ((np = lookup(name)) == NULL) { /* not found */
    np = (struct nlist *) malloc(sizeof(*np));
    if (np == NULL || (np->name = strcop(name)) == NULL)
      return NULL;
    hashval = hash(name);
    np->next = tab[hashval];
    tab[hashval] = np;
  } else /* already there */
    free((void *) np->defn); /*free previous defn */
  if ((np->defn = strcop(defn)) == NULL)
    return NULL;
  return np;
}
