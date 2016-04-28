#include "fonctions.h"

/*retourne la structure en arguments, avec des valeurs
 * initiales*/
void init_arg(inf *arg, int fd, /*pthread_mutex_t fic,*/ pthread_mutex_t ret);

/* retourne la première ligne du fichier
 * et avance le pointeur de la même façon*/
int recup_nbreValeurs(int fd);

/* Retourne l'entier (voir enum) corrspondant à la commande donnée*/
int recherche_operation(char *cmd);

/* Ecrit dans le fichier resultats.txt la valeur de retour des threads*/ 
void ecritureResultat(double retour);

/* Fonction qui va créer nb_thr threads exécutant la commande fct*/
void creaEmployes(void *(*fct) (void *), int nb_val, void *arg);

/* Fonction principale du fichier chef
 * Effectue ce que doit faire un processus chef
 * à partir d'un fichier et d'une commande donnée*/
double chef(char *cheminFic, char *cmd);
