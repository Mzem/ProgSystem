#ifndef DEF_DEF
#define DEF_DEF

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include "fonctions.h"

#endif

enum{MIN, MAX, SUM, AVG, ODD};

/* Fonction qui va créer nb_thr threads exécutant
 * la commande fct, et retourne la solution*/
int creaEmployes(void *(*fct) (void *), int nb_thr, void *arg)

/* Fonction principale du fichier chef
 * Effectue ce que doit faire un processus chef
 * à partir d'un fichier et d'une commande donnée*/
void chef(char *cheminFic, char *cmd);
