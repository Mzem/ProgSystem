#include "donnees.h"

int isBlank_or_EOF(char c);

/*Retourne le prochain caractere du fichier ou EOF */
char myfgetc(int fd);

/* Retourne -1 si aucune chaine de caractere n'est lue,
 * retourne 0 et stocke la prochaine chaine dans ch
 * si l'opération s'est bien passee. */
int myfgets(int fd, char *ch);

void* min(void* arg);

//~ void* max(void* arg);
//~ 
//~ void* sum(void* arg);
//~ 
//~ void* avg(void* arg);
//~ 
//~ void* odd(void* arg);


