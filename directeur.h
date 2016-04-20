#include "chef.h"

/* retourne un processus*/
pid_t creerProcessus();

/*Appelle nombreDeProcessus processus fils qui appellent chef et
 * renvoient un resultat qui sera stocke dans le tableau resultats[] */
void directeur(double resultats[], int nombreDeProcessus, char* argv[]);
