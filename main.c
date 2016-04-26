#include "directeur.h"


int main(int argc, char* argv[]) 
{
	if(argc < 3) //pas d'operation ou pas de fichier
	{
		fprintf(stderr,"Erreur : arguments manquants\n");
		return EXIT_FAILURE;
	}
	
	double resultat;
	int nombreDeProcessus = argc-2;
	
	//envoi de argv + 1 dans directeur (supprime le nom du fichier)
	resultat = directeur(nombreDeProcessus, argv+1);
	printf("LE RESULTAT GLOBAL EST %f\n", resultat);
	
	return EXIT_SUCCESS;
}
