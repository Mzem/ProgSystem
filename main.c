#include "chef.h"
#include "fonctions.h"
#include <stdio.h> 
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>


int main(int argc, char* argv[]) 
{
	int n=argc-2;//nombre de fichiers
	int resultat[n];//les resultats retournés par les processus chefs
	int resultat_final;//le resultat obtenu a partir de resultat[n]
	int indice_operation;//0:min 1:max 2:avg 3:sum 4:odd 5:inconnue
	if(argc < 3) //pas d'operation ou pas de fichier
		{
			printf("le nombre d'arguments est insuffisant\n");
			return 0 ;
		}
	indice_operation=recherche_operation(argv[1]);
	if ( indice_operation == 5 )
		{
			printf("le fonction demandée est inconnue :) \n");
			return 0 ;
		}
	//calcul l'operation de n elements de resultat[]
	resultat_final = fonction ( indice_operation , resultat , n );
	printf("le resultat final est %d\n",resultat_final);
	return 0 ;
}
