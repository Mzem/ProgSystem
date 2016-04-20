#include "chef.h"

void init_arg(inf *arg, int fd, pthread_mutex_t fic, pthread_mutex_t ret)
{	
	arg->fd = fd;
	arg->nb_val = recup_nbreValeurs(fd);
	arg->mut_fic = &fic;
	arg->mut_ret = &ret;
	arg->retour = malloc(sizeof(double));
}

int recup_nbreValeurs(int fd)
{
	int nb;
	char *ch = malloc(MAXSIZE_STR*sizeof(char));
	myfgets(fd, ch);
	nb = atoi(ch);
	printf("dans ce fichier il ya %d elements\n",nb);
	free(ch);
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

void creaEmployes(void *(*fct) (void *), int nb_val, void *arg)
{
	int i;
	inf *s = (inf *) arg;
	int nb_thr = (nb_val / 100) + 1;
	pthread_t thr[nb_thr];
	
	for (i = 0; i < nb_thr; i++)
		pthread_create(thr + i, NULL, fct, s);
	
	for (i = 0; i < nb_thr; i++)
		pthread_join(thr[i], NULL);
}

void chef(char *cheminFic, char *cmd, double *resultat)
{
	int fd = open(cheminFic, O_RDONLY);
	if(fd < 0)
	{
		fprintf(stderr, "Erreur à l'ouverture du fichier %s\n", cheminFic);
		exit(EXIT_FAILURE);
	}
	
	inf *arg = malloc(sizeof(inf));
	pthread_mutex_t fic = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_t ret = PTHREAD_MUTEX_INITIALIZER;
	init_arg(arg, fd, fic, ret);
	
	switch(recherche_operation(cmd))
	{
		case(MIN) : creaEmployes(min, arg->nb_val, arg); break;
		//~ case(MAX) : creaEmployes(max, arg->nb_vl, arg); break;
		//~ case(SUM) : creaEmployes(sum, arg->nb_val, arg); break;
		//~ case(AVG) : creaEmployes(avg, arg->nb_val, arg); break;
		//~ case(ODD) : creaEmployes(odd, arg->nb_val, arg); break;
		default :
		{
			fprintf(stderr, "Erreur commande non trouvée %s\n", cmd);
			break;
		}
	}
	
	*resultat = *arg->retour;
	printf("le retour de ce fichier est %f  \n",*arg->retour);
	
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
