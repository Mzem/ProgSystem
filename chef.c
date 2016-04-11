#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#include "fonctions.h"

//changer l'emplacement de la déclaration (ne laisser que dans un .h)
enum{MIN, MAX, SUM, AVG, ODD};

int recherche_operation(char *cmd)
{
	if(!strcmp(cmd, "min"))
		return 0;
	if(!strcmp(cmd, "max"))
		return 1;
	if(!strcmp(cmd, "sum"))
		return 2;
	if(!strcmp(cmd, "avg"))
		return 3;
	if(!strcmp(cmd, "odd"))
		return 4;
	return -1;
}

int creaEmployes(void *(*fct) (void *), int nb_thr, void *arg)
{
	int i;
	pthread_t thr[nb_thr];
	
	for (i = 0; i < nb_thr; i++)
	{
		//maj indices de arg a ajouter
		pthread_create(thr + i, NULL, fct, arg);
		//arg est modifie par les threads
		//besoin mutex pour proteger resultat dans fonctions
	}
	
	//possibilite ajout var dans join, pour eventuelles erreurs
	for (i = 0; i < nb_thr; i++)
		pthread_join(thr[i], NULL);
	
	return 0;	
	//return getResultat((inf *) arg);
}

void chef(char *cheminFic, char *cmd)
{
	//Ouverture du fichier donné en argument
	int fd = open(cheminFic, O_RDONLY);
	if(fd < 0)
	{
		fprintf(stderr, "Erreur à l'ouverture du fichier %s\n", cheminFic);
		exit(EXIT_FAILURE);
	}
	
	//recuperation taille fichier, determination nbre thread à utiliser
	int nb_thr = 0;
	//a faire proprement
	void *arg = NULL;
	//struct donnee *arg = init_struct();
	
	//recup commande, lancement threads
	switch(recherche_operation(cmd))
	{
		//ne compile pas encore car les fonctions.h ne sont pas encore au format void * fct(void *)
		case(MIN) : creaEmployes(min, nb_thr, arg); break;
		case(MAX) : creaEmployes(max, nb_thr, arg); break;
		case(SUM) : creaEmployes(sum, nb_thr, arg); break;
		case(AVG) : creaEmployes(avg, nb_thr, arg); break;
		case(ODD) : creaEmployes(odd, nb_thr, arg); break;
		default :
		{
			fprintf(stderr, "Erreur commande non trouvée %s\n", cmd);
			break;
		}
	}	
	
	//Retour au proc directeur la solution du fichier + nb élémemnts (avg)
	//Communication par pipes ?
	
	//libération des ressources, terminaison du processus
	//au cas ou on malloc pour la structure
	//libereMem(arg);
	close(fd);
	exit(EXIT_SUCCESS);
}
