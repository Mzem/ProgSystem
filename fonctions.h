#include "donnees.h"

int isBlank_or_EOF(char c);

/*Retourne le prochain caractere du fichier ou EOF */
char myfgetc(int fd);

/* Retourne EOF si aucune chaine de caractere n'est lue,
 * retourne 0 et stocke la prochaine chaine dans ch
 * si l'opération s'est bien passee.
 * Retourne -1 si aucune chaine n'est donnee en argument */
int myfgets(int fd, char *ch);

/* Ecrit le caractere c dans le fichier fd,
 *  retourne 0 si succes, -1 sinon.
 */
int myputc(int fd, char c);

/* Ecrit la chaine de caractere ch dans le fichier fd
 * Retourne 0 si succes, -1 si erreur
 */
int myfputs(int fd, char *ch);

void* min(void* arg);

//~ void* max(void* arg);
//~ 
//~ void* sum(void* arg);
//~ 
//~ void* odd(void* arg);


