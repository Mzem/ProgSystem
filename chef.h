#include "fonctions.h"

/*retourne la structure en arguments, avec des valeurs
 * initiales*/
void init_arg(inf *arg, int fd);

/* retourne la première ligne du fichier
 * et avance le pointeur de la même façon*/
int recup_nbreValeur(int fd);

/* Retourne l'entier (voir enum) corrspondant à la commande donnée*/
int recherche_operation(char *cmd);

/* Fonction qui va créer nb_thr threads exécutant la commande fct*/
void creaEmployes(void *(*fct) (void *), int nb_thr, void *arg);

/* Fonction principale du fichier chef
 * Effectue ce que doit faire un processus chef
 * à partir d'un fichier et d'une commande donnée*/
void chef(char *cheminFic, char *cmd);
