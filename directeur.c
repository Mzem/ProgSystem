#include "donnees.h"
#include "chef.h"

//Creer des fonctions simples min max sum avg odd qui rassemblent les resultats ?

pid_t creerProcessus()
{
	pid_t pid;
	
	//EAGAIN : code d'erreur stocke dans errno apres un fork, signale qu'on doit refaire le fork()
	//Donc on fork() tant que l'erreur est EAGAIN
	do{
		pid = fork();
	} while ( pid == -1 && errno == EAGAIN );
	
	return pid;
}

void directeur(int resultats[], int nombreDeProcessus, char* argv[])
{	//Appelle nombreDeProcessus processus fils qui appellent chef et renvoient un resultat qui sera stocke dans le tableau resultats[]
	int i;
	int resultat = 0;	//Entier stockant le resultat de l'operation de chaque processus fils
	
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
			
			//La fonction chef ne retourne pas encore de resultat, je veux le stocker dans la variable resultat
			//resultat = chef(argv[i+2],argv[1]);
			
			//Code retour qui renvoie le resultat de l'operation, de cette facon le resultat sera retourne au pere
			exit(resultat);
		}
	}
	
	//Synchronisation avec les nombreDeProcessus processus
	for (i = 0; i < nombreDeProcessus; i++)
	{
		int status;
		
		if( wait(&status) == -1)
		{
			perror("wait : ");
			exit(EXIT_FAILURE);
		}
		
		//Si le retour du fils s'est bien passe, on affiche le resultat de son operation
		if(WIFEXITED(status))
		{
			resultats[i] = WEXITSTATUS(status);
			printf("Retour du fils : %d\n",resultats[i]);
		}
		else 
			fprintf(stderr,"Erreur : le fils n'a pas quitte\n");
	}
	printf("Pere fini\n");
}
