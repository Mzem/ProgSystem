Au préalable, il faut modifier le Makefile du dossier src :
	- Variable CMD = "commande/opération à effectuer"
	- Variable FILES = "Liste des fichiers utilisés"
		Les fichiers seront placés dans le dossier data.
		La liste des fichiers se déclare de la manière suivante pour respecter la hiérarchie des répertoires :
					../data/nomFic1 ../data/nomFic2 etc...

Compilation :
	make
Compilation + exécution :
	make run
Nettoyage des fichiers objets :
	make clean
Nettoyage intégral :
	make mrproper

