all: reduction

run:	reduction
		./reduction

reduction: 	main.o directeur.o chef.o fonctions.o
			gcc -g -Wall main.o chef.o fonctions.o directeur.o -o reduction -lpthread

main.o:	main.c 	directeur.h  
		gcc -c -Wall main.c

directeur.o:	directeur.c directeur.h
				gcc -c -Wall directeur.c

chef.o: 	chef.c 	chef.h
				gcc -c -Wall chef.c

fonctions.o:	fonctions.c fonctions.h donnees.h
				gcc -c -Wall fonctions.c

clean:
	rm *.o
	rm reduction
