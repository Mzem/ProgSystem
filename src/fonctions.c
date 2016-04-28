#include "fonctions.h"

int isBlank(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

char myfgetc(int fd)
{
	char buf[1];
	
	//Ecrit un caractere
	if(read(fd, buf, 1) > 0)
		return buf[0];
		
	return -1;
}

int myfgets(int fd, char *ch)
{
	if(ch == NULL)
		return -1;
	char c;
	//On supprime les blancs avant la chaine de caractere
	c = myfgetc(fd);
	while(isBlank(c))
		c = myfgetc(fd);
	
	if(c == EOF) 
		return EOF;
		
	int i = 0;
	//On lit jusqu'au prochain blanc ou EOF(c contient un non-blanc avant le do)
	do{
		*ch++ = c;
		c = myfgetc(fd);
	}while(i++ < MAXSIZE_STR-1 && !isBlank(c) && c != EOF);
	
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
	int err;
	double x;

	// i = 1 parce qu'on a déjà lu la première valeur
	//100 vals maxs par thread
	for(i = 1; i < 100; i++)
	{
		//pthread_mutex_lock(minimum->mut_fic); perror("MUTEX");
		err = myfgets(minimum->fd, ch);
		//pthread_mutex_unlock(minimum->mut_fic);
		
		if(err == EOF || err == -1) break;
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
	int err;
	double x;

	for(i = 1; i < 100; i++)
	{
		//pthread_mutex_lock(maximum->mut_fic);
		err = myfgets(maximum->fd, ch);
		//pthread_mutex_unlock(maximum->mut_fic);
		
		if(err == EOF || err == -1) break;
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

void* sum(void* arg)
{
	inf* sum = (inf*) arg;
	char ch[MAXSIZE_STR];
	int i;
	int err;
	double x;
	
	
	// i = 1 parce qu'on a déjà lu la première valeur
	for(i = 1; i < 100; i++)
	{
		//pthread_mutex_trylock(sum->mut_fic);
		err = myfgets(sum->fd, ch);
		//pthread_mutex_unlock(sum->mut_fic);
		
		if(err == EOF || err == -1) break;
		x = atof(ch);
		
		pthread_mutex_lock(sum->mut_ret);
		*sum->retour += x;
		pthread_mutex_unlock(sum->mut_ret);
	}
	pthread_exit(NULL);
}

void* odd(void* arg)
{
	inf* odd = (inf*) arg;
	char ch[MAXSIZE_STR];
	int i;
	int err;
	int x;
	
	// i = 1 parce qu'on a déjà lu la première valeur
	for(i = 1; i < 100; i++)
	{
		//pthread_mutex_lock(odd->mut_fic);
		err = myfgets(odd->fd, ch);
		//pthread_mutex_unlock(odd->mut_fic);
		
		if(err == EOF || err == -1) break;
		x = atoi(ch);
		if(x%2==1)
		{
			pthread_mutex_lock(odd->mut_ret);
			*odd->retour += 1;
			pthread_mutex_unlock(odd->mut_ret);
		}
	}
	pthread_exit(NULL);
}
