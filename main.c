#include "directeur.h"
#include "donnees.h"



int main(int argc, char* argv[]) 
{
	int n=argc-2;//nombre de fichiers
	if(argc < 3) //pas d'operation ou pas de fichier
		{
			printf("le nombre d'arguments est insuffisant\n");
			return 0 ;
		}
	return n ;
}
