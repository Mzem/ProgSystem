#include "fonctions.h"

int isBlank_or_EOF(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == EOF);
}

char myfgetc(int fd)
{
	static char buf[MAXSIZE_BUF];
	static int ncar = 0;
	static char *p;
	
	if(ncar == 0)
	{
		ncar = read(fd, buf, MAXSIZE_BUF);
		p = buf;
	}
	return (ncar-- > 0) ? *p++ : EOF;
}

int myfgets(int fd, char *ch)
{
	if(ch == NULL)
		return -1;

	char c;
	//On supprime les blancs avant la chaine de caractere
	c = myfgetc(fd);
	while(isBlank_or_EOF(c))
		c = myfgetc(fd);
	
	if(c == EOF)
		return EOF;
	
	int i = 0;
	//On lit jusqu'au prochain blanc (c contient un non-blanc, non-EOF avant le do)
	do{
		*ch++ = c;
		c = myfgetc(fd);
	}while(i++ < MAXSIZE_STR-1 && !isBlank_or_EOF(c));
	
	//On ajoute le caractere de fin de chaine
	*ch = '\0';
	return 0;
}

int myputc(int fd, char c)
{
	char buf[1];
	buf[0] = c;
	
	//Ecrit un caractere
	if(write(fd, buf, 1) > 0)
		return 0;
		
	return -1;
}

int myfputs(int fd, char *ch)
{
	if(ch == NULL)
		return -1;
	
	char c;	
	while((c = *ch++) != '\0')
		myputc(fd, c);
	
	return 0;
}

void* min(void* arg)
{
	inf* minimum = (inf*) arg;
	char ch[MAXSIZE_STR];
	int i;
	double x;
	
	//minimum initialise a la premiere valeur du fichier
	//pthread_mutex_lock(minimum->mut_fic);
	myfgets(minimum->fd, ch);
	//pthread_mutex_unlock(minimum->mut_fic);
	
	*minimum->retour = atof(ch);
	
	// i = 1 parce qu'on a déjà lu la première valeur
	//## condition arret for a changer, marche ici car il n'y a qu'un thread
	for(i = 1; i < minimum->nb_val; i++)
	{
		//pthread_mutex_lock(minimum->mut_fic);
		myfgets(minimum->fd, ch);
		//pthread_mutex_unlock(minimum->mut_fic);
		
		x = atof(ch);
		if (x < *minimum->retour)
		{
				pthread_mutex_lock(minimum->mut_ret);
				*minimum->retour = x;
				pthread_mutex_unlock(minimum->mut_ret);
		}
	}
	
	pthread_exit(NULL);
}

void* max(void* arg)
{
	inf* maximum = (inf*) arg;
	char ch[MAXSIZE_STR];
	int i;
	double x;
	
	//maximum initialise a la premiere valeur du fichier
	//pthread_mutex_lock(maximum->mut_fic);
	myfgets(maximum->fd, ch);
	//pthread_mutex_unlock(maximum->mut_fic);
	
	*maximum->retour = atof(ch);
	
	// i = 1 parce qu'on a déjà lu la première valeur
	//## condition arret for a changer, marche ici car il n'y a qu'un thread
	for(i = 1; i < maximum->nb_val; i++)
	{
		//pthread_mutex_lock(maximum->mut_fic);
		myfgets(maximum->fd, ch);
		//pthread_mutex_unlock(maximum->mut_fic);
		
		x = atof(ch);
		if (x > *maximum->retour)
		{
				pthread_mutex_lock(maximum->mut_ret);
				*maximum->retour = x;
				pthread_mutex_unlock(maximum->mut_ret);
		}
	}
	
	pthread_exit(NULL);
}

void* odd(void* arg)
{
	inf* odd = (inf*) arg;
	char ch[MAXSIZE_STR];
	int i;
	double x;
	
	//odd initialise a la premiere valeur du fichier
	//pthread_mutex_lock(odd->mut_fic);
	myfgets(odd->fd, ch);
	//pthread_mutex_unlock(odd->mut_fic);
	
	*odd->retour = atof(ch);
	
	// i = 1 parce qu'on a déjà lu la première valeur
	//## condition arret for a changer, marche ici car il n'y a qu'un thread
	for(i = 1; i < odd->nb_val; i++)
	{
		//pthread_mutex_lock(odd->mut_fic);
		myfgets(odd->fd, ch);
		//pthread_mutex_unlock(odd->mut_fic);
		
		x = atof(ch);
		if (x < *odd->retour)
		{
				pthread_mutex_lock(odd->mut_ret);
				*odd->retour = x;
				pthread_mutex_unlock(odd->mut_ret);
		}
	}
	
	pthread_exit(NULL);
}

void* sum(void* arg)
{
	inf* sum = (inf*) arg;
	char ch[MAXSIZE_STR];
	int i;
	int x;
	
	//minimum initialise a la premiere valeur du fichier
	//pthread_mutex_lock(sum->mut_fic);
	myfgets(sum->fd, ch);
	//pthread_mutex_unlock(sum->mut_fic);
	
	*sum->retour = atof(ch);
	
	// i = 1 parce qu'on a déjà lu la première valeur
	//## condition arret for a changer, marche ici car il n'y a qu'un thread
	for(i = 1; i < sum->nb_val; i++)
	{
		//pthread_mutex_lock(minimum->mut_fic);
		myfgets(sum->fd, ch);
		//pthread_mutex_unlock(minimum->mut_fic);
		
		x = atoi(ch);
		if(x%2==1){
				pthread_mutex_lock(sum->mut_ret);
				*sum->retour += x;
				pthread_mutex_unlock(sum->mut_ret);
				}
	}
	pthread_exit(NULL);
}
