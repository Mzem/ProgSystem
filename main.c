#include <stdio.h>
#include <stdlib.h>
#include "directeur.h"


int main(int argc, char* argv[]) 
{
	if(argc < 3) //pas d'operation ou pas de fichier
	{
		fprintf(stderr,"Erreur : arguments manquants\n");
		return EXIT_FAILURE;
	}
	
	int nombreDeProcessus = argc-2;
	int resultats[nombreDeProcessus];		//Tableau qui stocke les resultats des tous les processus
	
	directeur(resultats,nombreDeProcessus,argv);	//Cree tous les processus qui inscrivent leurs resultats dans le tableau resultats[]
	
	return EXIT_SUCCESS;
}
