**Projet "Réduction" :** programme de calcul multi-processus et multi-threads via des appels systèmes.  
  
---------------------------------------
 
*Modifier le Makefile :*  

	Variable CMD = "commande ou opération à effectuer"  
	Variable FILES = "liste des fichiers utilisés"  
		
*La liste des fichiers se déclare de la manière suivante pour respecter la hiérarchie des répertoires :*  

	../data/nomFic1 ../data/nomFic2 etc...  

-------------------------------

**Lancement application :**

- Compilation  

		~ProgSystem/Projet/src$ make

- Compilation + exécution
	
		~ProgSystem/Projet/src$ make run
	
- Nettoyage des fichiers objet
	
		~ProgSystem/Projet/src$ make clean
	
- Nettoyage intégral
	
		~ProgSystem/Projet/src$ make mrproper

