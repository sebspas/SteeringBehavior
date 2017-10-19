8IAR125 - Rendu TP2 : Comportement dâ€™un agent -Steering Behavior-

Groupe de travail :
CORFA SÃ©bastien 	- CORS22119501
CROS Camille 		- CROC02529501
DECHAUX Quentin 	- DECQ24049507

RÃ©ponses aux questions
3) 	Notre calcul de l'agent leader le plus proche est dynamique : Ã  chaque Update(), l'agent-poursuiveur
	vÃ©rifie s'il voit un agent-leader. Si c'est le cas et qu'il ne suivait pas dÃ©jÃ  cet agent-leader, il 
	va se positionner Ã  la fin de la file suivant cet agent.	
	Lorsque l'on ajoute deux leaders dans la fenÃªtre, deux files indiennes se créent. Si un agent-leader coupe
	la file de l'autre agent alors les agents-poursuiveurs se rÃ©organisent en deux files selon l'agent-leader
	qui leur Ã©tait le plus proche grÃ¢ce Ã  notre approche dynamique.

4) Dans les onglets il est possible de mettre le mode manuel ou de l'enlever. On peut alors diriger l'agent de couleur bleu à l'aide des touches W (gauche) et E (droite) du clavier.

5) Les menus ont été changés pour permmettre de modifier le nombre de leaders et de poursuiveurs ainsi que d'activer ou désactiver le mode manuel. Les agents poursuiveurs sont de la couleur de leur leader.

6) Le comportement "Flocking V" a été implémenter de façon dynamique. C'est à dire que les agents poursuiveurs suivent le leader le plus près d'eux.

