#include "chef.h"

/* retourne un processus*/
pid_t creerProcessus();

/*Appelle nombreDeProcessus processus fils qui appellent chef
 * avec la commande et les fichiers stockés dans argv */
void directeur(int nombreDeProcessus, char* argv[]);
