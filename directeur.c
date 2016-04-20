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

void directeur(double resultats[], int nombreDeProcessus, char* argv[])
{
	int i;
	
	//Reduction en nombreDeProcessus processus et lancement des chefs
	for (i = 0; i < nombreDeProcessus; i++)
	{
		pid_t pid = creerProcessus();
		
		//Si une erreur irrecuperable s'est produite
		if (pid == -1)
		{
			perror("fork : ");
			exit(EXIT_FAILURE);
		}
		
		//Si on est dans un processus fils, on va effectuer une action chef puis retourner le resultat
		else if (pid == 0)
		{
			printf("Je suis le processus n°%d\n",i+1);
			chef(argv[i+1], argv[0], resultats + i);
			exit(getpid());
		}
	}
	//######### En gros recup resultat sera : do{ directeur(1, {"resultats.txt"}) }while( resultat != solution globale )
	for (i = 0; i < nombreDeProcessus; i++)
	{
		int status;
		
		if( wait(&status) == -1)
		{
			perror("wait : ");
			exit(EXIT_FAILURE);
		}
		
		if(WIFEXITED(status))
		{
			printf("Retour du fils : %f\n", resultats[i]);
		}
		else 
			fprintf(stderr,"Erreur : le fils a quitte avec une erreur\n");
	}
	printf("Pere fini\n");
}
