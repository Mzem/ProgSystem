Au préalable, il faut modifier le Makefile du dossier src:
	_ Variable CMD = "commande souhaitée"
	_ Variable FILES = "Liste des fichiers utilisés"
	_Les fichiers seront placés dans le dossier data
	_La liste des fichiers se déclarent de la manière suivante pour respecter les dossiers :
					../data/nomFic1 ../data/nomFic2 etc...

Compilation :
	make
Compilation + exécution :
	make run
Nettoyage des fichiers objets:
	make clean
Nettoyage intégral:
	make mrproper
