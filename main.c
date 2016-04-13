#include "directeur.h"

int main(int argc, char* argv[]) 
{
	int n=argc-2;//nombre de fichiers
	if(argc < 3) //pas d'operation ou pas de fichier
	{
		fprintf(stderr, "le nombre d'arguments est insuffisant\n");
		exit(EXIT_FAILURE);
	}
	
	if(!fork())
	{
		//directeur( arguments eventuels ); fonction principale de malek
	}
	else
	{
		wait(NULL); //argument éventuel pour traitement de l'erreur
	}
	
	return 0;
}
