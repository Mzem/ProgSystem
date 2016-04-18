#ifndef DEF_DEF2
#define DEF_DEF2

#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

#define MIN 0
#define MAX 1
#define SUM 2
#define AVG 3
#define ODD 4

#endif

struct inf{
	int fd;					//descripteur du fichier sur lequel on travail
	double *retour;			//stocker le resultat du calcul
	pthread_mutex_t *mut_fic;//pour protéger la lecture du fichier
	pthread_mutex_t *mut_ret;//pour protéger la valeur de retour
};

typedef struct inf inf;
