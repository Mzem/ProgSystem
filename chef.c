#include "chef.h"

void init_arg(inf *arg, int fd)
{
	pthread_mutex_t fic = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_t ret = PTHREAD_MUTEX_INITIALIZER;
	
	arg->fd = fd;
	arg->mut_fic = &fic;
	arg->mut_ret = &ret;
	arg->retour = malloc(sizeof(double));
}

int recup_nbreValeurs(int fd)
{
	int nb;
	char *ch = malloc(sizeof(char));
	myfgets(ch, fd);
	nb = atoi(ch); 
	printf("dans ce fichier il ya %d elements\n",nb);
	return nb;
}

int recherche_operation(char *cmd)
{
	if(!strcmp(cmd, "min"))
		return MIN;
	if(!strcmp(cmd, "max"))
		return MAX;
	if(!strcmp(cmd, "sum"))
		return SUM;
	if(!strcmp(cmd, "avg"))
		return AVG;
	if(!strcmp(cmd, "odd"))
		return ODD;
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
	inf *arg = malloc(sizeof(inf));
	init_arg(arg, fd);
	
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
	
	
	//printf("le retour de ce fichier est %f  \n",*arg->retour);
	
	//#### possibilite main ou directeur appelle un truc creat(O_RDWR); ou mkfifo("/tmp/resultats", r+w);
	//#### rajouter un truc du genre : communiqueResultat(arg, fic créé (ligne au dessus));
	//#### barriere() à rajouter, pour empecher free() avant fin des threads
	
	if(arg != NULL)
	{
		free(arg->retour);
		pthread_mutex_destroy(arg->mut_fic);
		pthread_mutex_destroy(arg->mut_ret);
	}
	free(arg);
	close(fd);
	exit(EXIT_SUCCESS);
}
