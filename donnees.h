

enum{MIN, MAX, SUM, AVG, ODD};

struct inf{
	int fd;		//pointeur sur le debut (a part  la premiere ligne a gerer par sonny)
	double retour;		//stocker le resultat du calcul
	pthread_t thr;	//entier, avoir l'info du thread en cours
	pthread_mutex_t mut_fic; //pour protéger la lecture du fichier
	pthread_mutex_t mut_ret; //pour protéger la valeur de retour
	pthread_mutex_t mut_nb;  //pour protéger le nb_elements
};
typedef struct inf inf;
