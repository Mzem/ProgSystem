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




enum{MIN, MAX, SUM, AVG, ODD};

struct inf{
	int fd;		//pointeur sur le debut (a part  la premiere ligne a gerer par sonny)
	double retour;		//stocker le resultat du calcul
	int nb_elements;
	pthread_t thr;	//entier, avoir l'info du thread en cours
	pthread_mutex_t mut_fic; //pour protéger la lecture du fichier
	pthread_mutex_t mut_ret; //pour protéger la valeur de retour
	pthread_mutex_t mut_nb;  //pour protéger le nb_elements
};
typedef struct inf inf;


#endif
