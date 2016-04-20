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

void creaResultats()
{
	char ch[MAXSIZE_STR];
	int fd = open("resultats.txt", O_WRONLY & O_CREAT, 00666);

	sprintf(ch, "%d", recup_nbreValeurs(fd));
	myputs(fd, ch);
	
	close(fd);
}

double traiteResultats(char *argv[])
{
	char ch[MAXSIZE_STR];
	double res_global;
	int fd = open("resultats.txt", O_RDONLY);
	int cmd_avg = 0;
	
	while(recup_nbreValeurs(fd) != 1)
	{
		switch(recherche_operation(argv[0]))
		{
			case(MIN) : chef("resultats.txt", "min"); break;
			case(MAX) : chef("resultats.txt", "max"); break;
			case(SUM) : chef("resultats.txt", "sum"); break;
			case(AVG) : chef("resultats.txt", "sum"); cmd_avg = 1; break;
			case(ODD) : chef("resultats.txt", "sum"); break;
			default :
			{
				fprintf(stderr, "Erreur commande non trouvée %s\n", argv[0]);
				break;
			}
		}
		lseek(fd, 0, SEEK_SET); //replace au debut pour recup_nbreValeurs
	}
	//Il n'y a qu'une valeur à la sortie de la boucle
	myfgets(fd, ch);
	res_global = atof(ch);
	
	close(fd);
	return cmd_avg ? res_global / nbreValsTotal(argv)  : res_global;
}

double directeur(int nombreDeProcessus, char* argv[])
{
	int i;
	
	pid_t *pid = NULL;
	pid = malloc(nombreDeProcessus*sizeof(pid_t));
	//Creation du fichier qui sert à stocker les résultats
	creaResultats();
	
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
	
	return traiteResultats(argv);
}
