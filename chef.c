#include "chef.h"

inf *init_arg(inf *arg, int fd)
{
	pthread_mutex_t mut_fic = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_t mut_ret = PTHREAD_MUTEX_INITIALIZER;
	
	arg->fd = fd;
	arg->mut_fic = mut_fic;
	arg->mut_ret = mut_ret;
	arg->retour = NULL;
	
	return arg;
}

int recup_nbreValeurs(int fd)
{
	int nb;
	char *ch = malloc(sizeof(char));
	myfgets(ch, fd);
	nb = atoi(ch);
	return nb;
}

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

void creaEmployes(void *(*fct) (void *), int nb_thr, void *arg)
{
	int i;
	pthread_t thr[nb_thr];
	
	inf *s = (inf *) arg;
	for (i = 0; i < nb_thr; i++)
		pthread_create(thr + i, NULL, fct, s);
	
	//possibilite ajout var dans join, pour eventuelles erreurs
	//ou alors le nombre d'éléments lus par le thread pour comparer
	//à la première ligne du fichier (gestion d'erreur)
	for (i = 0; i < nb_thr; i++)
		pthread_join(thr[i], NULL);
}

void chef(char *cheminFic, char *cmd)
{
	int fd = open(cheminFic, O_RDONLY);
	if(fd < 0)
	{
		fprintf(stderr, "Erreur à l'ouverture du fichier %s\n", cheminFic);
		exit(EXIT_FAILURE);
	}
	
	inf *arg = NULL;
	arg = init_arg(arg, fd);
	
	switch(recherche_operation(cmd))
	{
		case(MIN) : creaEmployes(min, recup_nbreValeurs(fd), arg); break;
		case(MAX) : creaEmployes(max, recup_nbreValeurs(fd), arg); break;
		case(SUM) : creaEmployes(sum, recup_nbreValeurs(fd), arg); break;
		case(AVG) : creaEmployes(avg, recup_nbreValeurs(fd), arg); break;
		case(ODD) : creaEmployes(odd, recup_nbreValeurs(fd), arg); break;
		default :
		{
			fprintf(stderr, "Erreur commande non trouvée %s\n", cmd);
			break;
		}
	}
	
	//#### possibilite main ou directeur appelle un truc creat(O_RDWR); ou mkfifo("/tmp/resultats", r+w);
	//#### rajouter un truc du genre : communiqueResultat(arg, fic créé (ligne au dessus));
	
	if(arg->retour != NULL)
		free(arg->retour);
	close(fd);
	exit(EXIT_SUCCESS);
}
