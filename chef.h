#ifndef DEF_DEF1
#define DEF_DEF1

#include "fonctions.h"
#include "donnees.h"


#endif

void init_arg(inf *arg);

int recup_nbreValeur(int fd);

/* Retourne l'entier (voir enum) corrspondant à la commande donnée*/
int recherche_operation(char *cmd);

/* Fonction qui va créer nb_thr threads exécutant
 * la commande fct, et retourne la solution*/
int creaEmployes(void *(*fct) (void *), int nb_thr, void *arg);

/* Fonction principale du fichier chef
 * Effectue ce que doit faire un processus chef
 * à partir d'un fichier et d'une commande donnée*/
void chef(char *cheminFic, char *cmd);
