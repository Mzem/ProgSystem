#include "chef.h"

/* retourne un processus*/
pid_t creerProcessus();

/* retourne la somme de tous les headers des fichiers
 * en arguments, cad le nombre total de valeurs a traiter */
int nbreValsTotal(char *argv[]);

/* cree et initialise le fichier resultat
 * avec le nombre de processus (= nbre de resultats)
 *  en premiere ligne */
int creaResultats(int nbrDeProcessus);

/* Traite le fichier résultats en lui affectant la
 * bonne commande, retourne la solution globale*/
double traiteResultats(char *argv[]);

/*Appelle nombreDeProcessus processus fils qui appellent chef
 * avec la commande et les fichiers stockés dans argv */
double directeur(int nombreDeProcessus, char* argv[]);
