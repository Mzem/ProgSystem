#include "fonctions.h"

/*
 int main (int argc, char* argv[])
{
	int num[N], i;
	pthread_t thr[N];	//tableau de N thread
	for (i = 0; i < N; i++)
	{//creer le thread
		num[i] = i+1;
		pthread_create(&thr[i],NULL,affichage,(void*)&num[i]);
	}
	void* join;
	for (i = 0; i < N; i++)
	{
		pthread_join(thr[i],&join);
		printf("%d\n",*(int*)(join));
		free(join);
	}
	return 0;
}
code pour creer un thread utilisee par le prof

struct inf{
	int debut;		//indices dans le tableau de ou à ou chercher le max
	int fin;		//indice fin
	int retour;		//stocker le max
	pthread_t thr;	//entier, avoir l'info du thread en cours
}
est ce possible de mettre debut et fin pointeurs sur des element du fichier?
sinon est ce possible de remplir un tableau a partir de chaque fichier ?
 */
