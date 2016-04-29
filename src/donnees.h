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

#define MAXSIZE_BUF 1024
#define MAXSIZE_STR 256

#define MIN 0
#define MAX 1
#define SUM 2
#define AVG 3
#define ODD 4

#endif

typedef struct
{
	int fd;						//descripteur du fichier sur lequel on travaille
	int nb_val;					//nombre de valeurs du fichier
	double *retour;				//stocker le resultat du calcul
	pthread_mutex_t *mut_fic;	//pour protéger la lecture du fichier
	pthread_mutex_t *mut_ret;	//pour protéger la valeur de retour
} inf;
