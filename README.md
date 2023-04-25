# In104project

Welcome !

Intro : ce projet vise à développer des programmes C (avec interface graphique) permettant de détecter des notes de piano

Plan : I/ Présentation du projet II/ Les trois méthodes de détection de notes étudiées III/ Utilisation actuelle des scripts

I. Présentation du projet

II.	Les trois méthodes de détection de notes étudiées

a)	Minimisation de l’écart quadratique 
Une première méthode (tout à fait naïve) a consisté à enregistrer la plupart des notes de piano sous forme de fichiers .wav à l’aide du logiciel musescore. Le programme a consisté à calculer les transformées de Fourier de chacune de ces notes, les stocker dans un tableau, puis décider de la note jouée dans le fichier test par minimisation de l’écart quadratique moyen.
Les résultats ne sont pas convaincants pour cette méthode.
Les fichiers source correspondants sont :
•	Morceau_methode1.c
•	Morceau_methode2.c

b)	Recherche de « l’ARGMAX » (en prenant en compte les harmoniques)

Cette méthode a été codée dans les fichiers sources :
•	Morceau_methode3.c
•	Morceau_methode4.c
•	Morceau_methode5.c
Le programme le plus performant étant morceau_methode5.c 
Les résultats de morceau_methode5.c commencent à être satisfaisants.
c)	Coder un réseau de neurones

J’ai codé un neurone ainsi qu’un réseau de neurones à deux couches. Le résultat est loin d’être satisfaisant, probablement à cause du peu de données lors de la phase d’apprentissage.
neur2.c et neur3.c ne sont pas sur github car non performants. 

III/ Utilisation actuelle des scripts

En bas de chaque script se trouve une ligne de compilation (commençant par gcc ...) à mettre dans le shell. Celle-ci compile le programme choisi. Ensuite, il n'y a plus qu'à exécuter en faisant ./a.out 


