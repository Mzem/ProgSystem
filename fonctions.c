#include "fonctions.h"

char getchar2(int fd){
	static char buf[1024];
	static int ncar=0;
	static char* p;
	if(ncar==0){
		ncar=read(fd,buf,1024);
		p=buf;
	}
	return (ncar-->0)? *p++ : EOF;
}

void myfgets(char* ch,int fd){
	int x;
	x=getchar2(fd);
	while((x!='\n')&&(x!='\0')){
		*ch++=x;
		x=getchar2(fd);
	}
	*ch='\0';
}


//############ MODIFIER mutex_lock(&mut) et mutex_unlock(&mut), pour le retour et la lecture fic
void* min(void* arg)
{
	inf* minimum = (inf*) arg;
	char ch[100]; //pour lire du ficher une chaine
	double x;
	*minimum->retour = 50;//a modifier(prend la premiere valeur pour min et max 0pour les autres)
	while(ch[0]!='\0')
		{//remplissage et comparaison en meme temps
			myfgets(ch,minimum->fd);
			x=atof(ch);
			if (x < *minimum->retour)
				*minimum->retour = x;
		}
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
			myfgets(ch,maximum->fd);
			x=atof(ch);
			if (x > *maximum->retour)
				*maximum->retour = x;
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
			myfgets(ch,somme->fd);
			x=atof(ch);
			*somme->retour += x;
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
			myfgets(ch,avg->fd);
			x=atof(ch);
			*avg->retour += x;
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
			myfgets(ch,odd->fd);
			x=atoi(ch);
			if(x%2==1)
				*odd->retour += 1;
		}
	pthread_exit(NULL);
}
