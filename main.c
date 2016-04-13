#include "donnees.h"
#include "directeur.h"


int main(int argc, char* argv[]) 
{
	if(argc < 3) //pas d'operation ou pas de fichier
	{
		fprintf(stderr,"Erreur : le fils n'a pas quitte\n");
		return EXIT_FAILURE;
	}
	
	int resultats[N];	//Tableau qui stocke les resultats des N processus
	
	directeur(resultats,argv);	//Cree les N processus qui inscrivent leurs resultats dans le tableau resultats[]
	
	return EXIT_SUCCESS;
}
