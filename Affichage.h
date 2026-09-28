#ifndef __AFFICHAGE__
#define __AFFICHAGE__

#include <stdlib.h>
#include <stdio.h>


/* Structure necessaire aux fonctions d affichage*/
typedef struct{  
  int L, H;     /* Largeur, Hauteur de l'affichage */
  char *** tab; /* Tableau à deux dimensions de chaînes de caractères ASCII */
} Affichage;


Affichage * Affichage_initialiser(int L, int H);   /* Alloue et initialise */
void Affichage_desallouer(Affichage **A);           
void Affichage_cadre(Affichage *A);                /* Place un cadre autour de l'Affichage */
void Affichage_vider(Affichage *A);                /* Remplit l'Affichage de case noire */
void Affichage_dessiner(Affichage *A);             /* Affiche le tableau à l'écran */


#endif
