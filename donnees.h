#ifndef DEF_DEF2
#define DEF_DEF2

#include <stdio.h> 
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>

#define N 4	//Nombre de processus


enum{MIN, MAX, SUM, AVG, ODD};

struct inf{
	int fd;		//pointeur sur le debut (a part  la premiere ligne a gerer par sonny)
	pthread_t thr;	//entier, avoir l'info du thread en cours
	double retour;		//stocker le resultat du calcul
	pthread_mutex_t mut_fic; //pour protéger la lecture du fichier
	pthread_mutex_t mut_ret; //pour protéger la valeur de retour
};
typedef struct inf inf;


#endif
