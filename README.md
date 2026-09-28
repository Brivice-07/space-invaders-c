Titre: Déplacement du canon
Auteur: Pierre Fouilhoux

Affiche un écran de jeux et permet le déplacement d'un canon dans la fenêtre d'un terminal en utilisant un affichage ASCII

Installation: Utiliser la commance make pour utiliser le Makefile

Usage: Lancer ./main_jeu <largeur> <hauteur> <niveau de difficulté>
  <largeur> largeur de l'écran de jeu (au moins 20)
  <hauteur> hauteur de l'écran de jeu (au moins 20)
  <niveau de difficulté> permet de régler la difficulté du jeu (1 niveau le plus bas)

Important: pour jouer sur un grand écran, par ex (200, 100), il faut agrandir la fenêtre du terminal et réduire la police du terminal (CTRL-)


Ce programme consiste à faire afficher sur une partie du terminal une zone délimitée par un rectangle, appelé écran de jeu, ainsi qu'un canon en bas de l'écran.
Le canon peut être déplacé à gauche et à droite en utilisant les flèches du clavier.
Quand le canon arrive sur le bord de l'écran, il ne peut continuer dans cette direction.

Le niveau de difficulté est ici inutilisé.

Fin du jeu: touche ESC

