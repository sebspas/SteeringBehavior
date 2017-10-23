8IAR125 - Rendu TP2 : Comportement d’un agent -Steering Behavior-

Groupe de travail :
CORFA Sébastien 	- CORS22119501
CROS Camille 		- CROC02529501
DECHAUX Quentin 	- DECQ24049507

/!\ Par défaut les murs sont actifs pour permettre de mieux voir les formations. Le mode de calcul est en 
WeightedSum, si celui-ci est changé le comportement des agents devient trop chaotique pour distinguer les formations.

Réponses aux questions
3) 	Notre calcul de l'agent leader le plus proche est dynamique : à chaque Update(), l'agent-poursuiveur
	vérifie s'il voit un agent-leader. Si c'est le cas et qu'il ne suivait pas déjà cet agent-leader, il 
	va se positionner à la fin de la file suivant cet agent.	
	Lorsque l'on ajoute deux leaders dans la fenêtre, deux files indiennes se créent. Si un agent-leader coupe
	la file de l'autre agent alors les agents-poursuiveurs se réorganisent en deux files selon l'agent-leader
	qui leur était le plus proche grâce à notre approche dynamique.

4) 	Dans les onglets, il est possible de mettre le mode manuel ou de l'enlever. On peut alors diriger l'agent de couleur 
	bleu à l'aide des touches W (gauche/west) et E (droite/east) du clavier. Par défaut le leader avance en ligne droite.

5) 	Les menus ont été changés pour permmettre de modifier le nombre de leaders et de poursuiveurs ainsi que d'activer ou 
	désactiver le mode manuel. Les agents poursuiveurs sont de la couleur de leur leader.

6) 	Le comportement "Flocking V" a été implémenté de façon dynamique : c'est-à-dire que les agents poursuiveurs suivent 
	le leader le plus près d'eux. Dans le cas où un agent poursuiveur change de leader, les positions des agents le
	suivant sont automatiquement recalculées.