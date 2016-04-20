#include "directeur.h"

pid_t creerProcessus()
{
	pid_t pid;
	
	//Donc on fork() tant que l'erreur est EAGAIN
	do{
		pid = fork();
	} while ( pid == -1 && errno == EAGAIN );
	
	return pid;
}

void directeur(int nombreDeProcessus, char* argv[])
{
	int i;
	
	pid_t *pid = NULL;
	pid = malloc(nombreDeProcessus*sizeof(pid_t));

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
	
	//Tous les processus ont effectué leur travail, on peut lire le fichier resultats
	

	free(pid);
}
