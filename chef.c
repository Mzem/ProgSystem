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
	char ch[MAXSIZE_STR];
	myfgets(fd, ch);
	nb = atoi(ch);
	printf("dans le fichieril ya %d elements\n", nb);
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

void ecritureResultat(double retour)
{
	char ch[MAXSIZE_STR];
	int fd = open("resultats.txt", O_WRONLY | O_APPEND);
	if(fd < 0)
	{
		fprintf(stderr, "Erreur à l'ouverture du fichier resultats.txt\n");
		exit(EXIT_FAILURE);
	}
	
	sprintf(ch, "%f\n", retour);
	myfputs(fd, ch);
}

void creaEmployes(void *(*fct) (void *), int nb_val, void *arg)
{
	int i;
	char* ch;
	inf *s = (inf *) arg;
	int nb_thr = (nb_val / 100) + 1;
	//myfgets(s->fd,ch);
	//*s->retour=atof(ch);
	pthread_t thr[nb_thr];
	
	for (i = 0; i < nb_thr; i++)
		pthread_create(thr + i, NULL, fct, s);
	
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
	
	pthread_mutex_t fic = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_t ret = PTHREAD_MUTEX_INITIALIZER;
	
	inf *arg = malloc(sizeof(inf));
	init_arg(arg, fd, fic, ret);
	
	switch(recherche_operation(cmd))
	{
		case(MIN) : creaEmployes(min, arg->nb_val, arg); break;
		case(MAX) : creaEmployes(max, arg->nb_val, arg); break;
		case(SUM) : creaEmployes(sum, arg->nb_val, arg); break;
		case(AVG) : creaEmployes(sum, arg->nb_val, arg); break;
		case(ODD) : creaEmployes(odd, arg->nb_val, arg); break;
		default :
		{
			fprintf(stderr, "Erreur commande non trouvée %s\n", cmd);
			break;
		}
	}
	
	//Ecriture dans le fichier resultat
	ecritureResultat(*arg->retour);
	
	if(arg != NULL)
	{
		pthread_mutex_destroy(arg->mut_fic);
		pthread_mutex_destroy(arg->mut_ret);
		free(arg->retour);
	}
	free(arg);
	close(fd);
}
