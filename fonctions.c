#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "donnees.h"

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

void* min(void* arg)
{
	inf* minimum = (inf*) arg;
	char ch[100]; //pour lire du ficher une chaine
	double buf[minimum->nb_elements];//contiend les entiers du fichier
	int i;//compteur
	minimum->retour = 50;//a modifier(prend la premiere valeur pour min et max 0pour les autres)
	for (i = 0; i <minimum->nb_elements ; i++)
		{//remplissage et comparaison en meme temps
			myfgets(ch,minimum->fd);
			buf[i]=atof(ch);
			if (buf[i] < minimum->retour)
				minimum->retour = buf[i];
		}
	pthread_exit(NULL);
}

void* max(void* arg)
{
	inf* maximum = (inf*) arg;
	char ch[10]; //pour lire du ficher une chaine
	double buf[maximum->nb_elements];//contiend les entiers du fichier
	int i;//compteur
	maximum->retour = 0;//a modifier(prend la premiere valeur pour min et max 0pour les autres)
	for (i = 0; i <maximum->nb_elements ; i++)
		{//remplissage et comparaison en meme temps
			myfgets(ch,maximum->fd);
			buf[i]=atof(ch);
			if (buf[i] > maximum->retour)
				maximum->retour = buf[i];
		}
	pthread_exit(NULL);
}

void* sum(void* arg)
{
	inf* somme = (inf*) arg;
	char ch[10]; //pour lire du ficher une chaine
	double buf[somme->nb_elements];//contiend les entiers du fichier
	int i;//compteur
	somme->retour = 0;
	for (i = 0; i <somme->nb_elements ; i++)
		{//remplissage et comparaison en meme temps
			myfgets(ch,somme->fd);
			buf[i]=atof(ch);
			somme->retour += buf[i];
		}
	pthread_exit(NULL);
}

void* avg(void* arg)
{ 
	inf* avg = (inf*) arg;
	char ch[10]; //pour lire du ficher une chaine
	double buf[avg->nb_elements];//contiend les entiers du fichier
	int i;//compteur
	avg->retour = 0;
	for (i = 0; i <avg->nb_elements ; i++)
		{//remplissage et comparaison en meme temps
			myfgets(ch,avg->fd);
			buf[i]=atof(ch);
			avg->retour += buf[i];
		}
		avg->retour = avg->retour/avg->nb_elements;
	pthread_exit(NULL);
}

void* odd(void* arg)
{
	inf* odd = (inf*) arg;
	char ch[10]; //pour lire du ficher une chaine
	int buf[odd->nb_elements];//contiend les entiers du fichier
	int i;//compteur
	odd->retour = 0;
	for (i = 0; i <odd->nb_elements ; i++)
		{//remplissage et comparaison en meme temps
			myfgets(ch,odd->fd);
			buf[i]=atoi(ch);
			if(buf[i]%2==1)
				odd->retour += 1;
		}
	pthread_exit(NULL);
}
