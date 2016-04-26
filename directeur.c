#include "directeur.h"

pid_t creerProcessus()
{
	pid_t pid;
	
	//Donc on fork() tant que l'erreur est EAGAIN
	do{
		pid = fork();
	} while (pid == -1 && errno == EAGAIN);
	
	return pid;
}

int nbreValsTotal(char *argv[])
{
	return 1;
}

int creaResultats(int nbrDeProcessus)
{
	char ch[MAXSIZE_STR];
	int fd = creat("resultats.txt", 00666);

	sprintf(ch, "%d\n", nbrDeProcessus);
	myfputs(fd, ch);
	
	return fd;
}

double traiteResultats(char *argv[])
{
	double resultat;
	
	switch(recherche_operation(argv[0]))
	{
		case(MIN) : resultat = chef("resultats.txt", "min"); break;
		case(MAX) : resultat = chef("resultats.txt", "max"); break;
		case(SUM) : //on utilise la fonction commande sum, d'où l'omission du break
		case(AVG) : //idem
		case(ODD) : resultat = chef("resultats.txt", "sum"); break;
		default :
		{
			fprintf(stderr, "Erreur commande non trouvée %s\n", argv[0]);
			break;
		}
	}
	return resultat;
}


double directeur(int nombreDeProcessus, char* argv[])
{
	int i;
	
	pid_t *pid = NULL;
	pid = malloc(nombreDeProcessus*sizeof(pid_t));
	//Creation du fichier qui sert à stocker les résultats
	creaResultats(nombreDeProcessus);
	
	//Reduction en nombreDeProcessus processus et lancement des chefs
	for (i = 0; i < nombreDeProcessus; i++)
	{
		pid[i] = creerProcessus();
		//Si une erreur irrecuperable s'est produite
		if (pid[i] == -1)
		{
			perror("fork : ");
			exit(EXIT_FAILURE);
		}
		//Si on est dans un processus fils, on va effectuer une action chef
		else if (pid[i] == 0)
		{
			printf("Je suis le processus n°%d\n", getpid());
			chef(argv[i+1], argv[0]);
			exit(EXIT_SUCCESS);
		}
	}
	
	//Attente des processus
	for (i = 0; i < nombreDeProcessus; i++)
	{
		int status;
		if( waitpid(pid[i], &status, 0) == -1)
		{
			perror("wait : ");
			exit(EXIT_FAILURE);
		}
		
		if(WIFEXITED(status))
		{
			printf("Retour du fils. n° : %d\n", pid[i]);
		}
		else 
			fprintf(stderr,"Erreur : le fils a quitte avec une erreur\n");
	}
	
	//liberation de la memoire
	free(pid);
	
	double resultat;
	resultat = traiteResultats(argv);
	return resultat;
}
