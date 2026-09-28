#ifndef _CANON_H_
#define _CANON_H_

#include"Affichage.h"

enum action_canon {Gauche_canon, Droite_canon,Haut_canon, Bas_canon, Tir};

typedef struct{
  int largeur, hauteur;   /* Taille du rectangle de la base du canon */
  int pos_min, pos_max;   /* Position min (à gauche) et max (à droite) */
  int x_min, x_max;
  int xpos, ypos;         /* Case supérieure gauche de la position du Canon */ 
  int pas;                /* Nombre de cases de déplacement d'un Canon à chaque appui */
  int xpos_old, ypos_old;           /* Position précédente du Canon */
} Canon;

Canon* Canon_initialiser(int pos_min, int pos_max, int hauteur_aff);
void Canon_desallouer(Canon** C);
void Canon_action(Canon *C, enum action_canon actC);
void Canon_afficher(Canon *C, Affichage* A);


#endif 


