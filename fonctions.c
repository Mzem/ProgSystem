#include "fonctions.h"

void* min(void* arg)
{
	inf* minimum = (inf*) arg;
	char* ch=malloc(sizeof(char)); //pour lire du ficher une chaine
	double x;
	*minimum->retour = 50;//a modifier(prend la premiere valeur pour min et max 0pour les autres)
	while(ch[0]!='\0')
		{//remplissage et comparaison en meme temps
			pthread_mutex_lock(minimum->mut_fic);
			myfgets(ch,minimum->fd);
			pthread_mutex_unlock(minimum->mut_fic);
			x=atof(ch);
			if (x < *minimum->retour){
				pthread_mutex_lock(minimum->mut_ret);
				*minimum->retour = x;
				pthread_mutex_unlock(minimum->mut_ret);
			}
		}
	free(ch);
	pthread_exit(NULL);
}

void* max(void* arg)
{ 
	inf* maximum = (inf*) arg;
	char ch[10]; //pour lire du ficher une chaine
	double x;
	maximum->retour = 0;//a modifier(prend la premiere valeur pour min et max 0pour les autres)
	while(ch[0]!='\0')
		{//remplissage et comparaison en meme temps
			pthread_mutex_lock(maximum->mut_fic);
			myfgets(ch,maximum->fd);
			pthread_mutex_unlock(maximum->mut_fic);
			x=atof(ch);
			if (x > *maximum->retour){
				pthread_mutex_lock(maximum->mut_ret);
				*maximum->retour = x;
				pthread_mutex_unlock(maximum->mut_ret);
			}
		}
	pthread_exit(NULL);
}

void* sum(void* arg)
{
	inf* somme = (inf*) arg;
	char ch[10]; //pour lire du ficher une chaine
	double x;
	somme->retour = 0;
	while(ch[0]!='\0')
		{//remplissage et comparaison en meme temps
			pthread_mutex_lock(somme->mut_fic);
			myfgets(ch,somme->fd);
			pthread_mutex_unlock(somme->mut_fic);
			x=atof(ch);
			pthread_mutex_lock(somme->mut_ret);
			*somme->retour += x;
			pthread_mutex_unlock(somme->mut_ret);
		}
	pthread_exit(NULL);
}

void* avg(void* arg)
{ 
	inf* avg = (inf*) arg;
	char ch[10]; //pour lire du ficher une chaine
	double x;
	avg->retour = 0;
	while(ch[0]!='\0')
		{//remplissage et comparaison en meme temps
			pthread_mutex_lock(avg->mut_fic);
			myfgets(ch,avg->fd);
			pthread_mutex_unlock(avg->mut_fic);
			x=atof(ch);
			pthread_mutex_lock(avg->mut_ret);
			*avg->retour += x;
			pthread_mutex_unlock(avg->mut_ret);
		}
	pthread_exit(NULL);
}

void* odd(void* arg)
{
	inf* odd = (inf*) arg;
	char ch[10]; //pour lire du ficher une chaine
	int x;
	odd->retour = 0;
	while(ch[0]!='\0')
		{//remplissage et comparaison en meme temps
			pthread_mutex_lock(odd->mut_fic);
			myfgets(ch,odd->fd);
			pthread_mutex_unlock(odd->mut_fic);
			x=atoi(ch);
			if(x%2==1){
				pthread_mutex_lock(odd->mut_ret);
				*odd->retour += 1;
				pthread_mutex_unlock(odd->mut_ret);
			}
		}
	pthread_exit(NULL);
}
