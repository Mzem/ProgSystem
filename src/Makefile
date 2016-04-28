CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lpthread
EXEC = reduction

#utiliser : min, max, sum, avg, odd.
CMD = sum
FILES = fic1.txt ../data/fic2.txt

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

all: $(EXEC)
	
run: $(EXEC)
		./$(EXEC) $(CMD) $(FILES)

reduction: $(OBJ)
			$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

main.o:	directeur.h  
directeur.o: directeur.h
chef.o: chef.h
fonctions.o: fonctions.h donnees.h

%.o: %.c
		$(CC) -c $(CFLAGS) -o $@ $<

.PHONY: clean mrproper

clean:
	@rm *.o
	
mrproper: clean
	@rm $(EXEC)
	@rm resultats.txt
