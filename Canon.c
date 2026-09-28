#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "Canon.h"

Canon* Canon_initialiser(int pos_min, int pos_max, int hauteur_aff){
   Canon *C= malloc(sizeof(Canon));
   C->hauteur=2;
   C->largeur=11;
   C->x_min = 3;
   C->x_max = hauteur_aff - C->hauteur - 1;
   C->ypos = (pos_min + pos_max) / 2;
   C->xpos = C->x_max;
   C->ypos_old = C->ypos;
   C->xpos_old = C->xpos;
   C->pos_min=pos_min+3; 
   C->pos_max=pos_max-3;
   C->pas=5;
   return C;
}

void Canon_desallouer(Canon** C){
  free(*C);
  *C=NULL;
}


void Canon_action(Canon *C, enum action_canon actC){
  C->xpos_old= C->xpos;
  C->ypos_old= C->ypos; 

  switch (actC){
    case Gauche_canon:
      C->ypos-=C->pas;
      break;
    case Droite_canon:
      C->ypos+=C->pas;
      break;
    case Haut_canon:
      C->xpos -= C->pas;
      break;
    case Bas_canon:
      C->xpos += C->pas;
      break;
    case Tir:
      // Lance une fléchette
      break;       
  }

  if ((C->ypos<C->pos_min)||(C->ypos>C->pos_max-C->largeur)){
   C->ypos=C->ypos_old;
   C->ypos=C->ypos_old;
  }

}

void Canon_afficher(Canon *C, Affichage* A){ 
  int x,y;
  for(x=C->xpos; x<C->xpos+C->hauteur; x++)
    for (y=C->ypos; y<C->ypos+C->largeur; y++)
      strcpy(A->tab[x][y],"\33[44m ");
  int centre = C->ypos + C->largeur / 2;
  for(x = C->xpos - 2; x < C->xpos; x++){
    strcpy(A->tab[x][centre - 1], "\33[44m ");
    strcpy(A->tab[x][centre],     "\33[44m ");
    strcpy(A->tab[x][centre + 1], "\33[44m ");
}
}



