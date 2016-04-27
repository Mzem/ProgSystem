#include "directeur.h"

pid_t creerProcessus()
{
	pid_t pid;
	
	//On fork() tant que l'erreur est EAGAIN
	do{
		pid = fork();
	} while (pid == -1 && errno == EAGAIN);
	
	return pid;
}

int nbreValsTotal(char *argv[])
{
	return 1;
}

int creaResultats(int nombrDeProcessus)
{	//Creation d'un fichier et écriture du nombre de valeurs
	char ch[MAXSIZE_STR];
	int fd = creat("resultats.txt", 00666);

	sprintf(ch, "%d\n", nombrDeProcessus);	//écrit nombreDeProcessus dans ch
	myfputs(fd, ch);
	
	return fd;
}

double traiteResultats(char *argv[])
{
	double resultat;
	int cmd_avg = 0;
	
	switch(recherche_operation(argv[0]))
	{
		case(MIN) : resultat = chef("resultats.txt", "min"); break;
		case(MAX) : resultat = chef("resultats.txt", "max"); break;
		case(SUM) : resultat = chef("resultats.txt", "sum"); break;
		case(AVG) : resultat = chef("resultats.txt", "sum"); cmd_avg = 1; break;
		case(ODD) : resultat = chef("resultats.txt", "sum"); break;
		default :
		{
			fprintf(stderr, "Erreur commande non trouvée %s\n", argv[0]);
			break;
		}
	}
	return cmd_avg ? resultat / nbreValsTotal(argv) : resultat;
}


double directeur(int nombreDeProcessus, char* argv[])
{
	int i;
	
	//Creation d'un tableau de pid pour pouvoir stocker tous les pid de tous les processus fils
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
			printf("Je suis le processus n°%d de pid = %d\n", i+1, getpid());
			chef(argv[i+1], argv[0]);	//à modifier non ?
			exit(i+1);	//Code retour : numéro du processus (utilisé pour repérer son pid lors du wait)
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
			printf("Retour du fils n°%d de pid = %d\n", WEXITSTATUS(status), pid[WEXITSTATUS(status)-1]);	//pid[i] ne renvoie pas le bon pid
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
