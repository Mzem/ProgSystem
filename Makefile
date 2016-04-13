all: reduction

run:	reduction
		./reduction

reduction: 	main.o chef.o fonctions.o directeur.o
			gcc -g -Wall main.o chef.o fonctions.o directeur.o -o reduction -lpthread

main.o:	main.c 	directeur.h  
		gcc -c -Wall main.c

directeur.o:	directeur.c chef.h
				gcc -c -Wall directeur.c

chef.o: 	chef.c 	fonctions.h 
				gcc -c -Wall chef.c

fonctions.o:	fonctions.c donnees.h
				gcc -c -Wall fonctions.c

clean:
	rm *.o
	rm reduction
