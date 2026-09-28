#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Affichage.h"

/* Alloue et initialise une grille */
Affichage * Affichage_initialiser(int L, int H){
  int x, y;
  Affichage *A;
  A = malloc(sizeof(Affichage));
  A->L=L; A->H=H;
  A->tab=malloc(H*sizeof(char **));
  for(x=0;x<H;x++){
    A->tab[x]=malloc(L*sizeof(char *));
    for (y=0;y<L;y++)
       A->tab[x][y]=malloc(7*sizeof(char)); // Une case peut faire 6 caractères ASCII pour les séquences d'échappement
  }
  return A;
}

/* Desallocation de la grille */
void Affichage_desallouer(Affichage **A){
  int x,y;
  for (x=0;x<(*A)->H;x++){
    for (y=0;y<(*A)->L;y++)
       free((*A)->tab[x][y]);    
    free((*A)->tab[x]);
     }
  free((*A)->tab);
  free(*A);
  *A=NULL;
}


/* Remplit une grille de vide */
void Affichage_vider(Affichage *A){
  int x,y;
  for (x=0; x<A->H; x++)
    for (y=0; y<A->L; y++){
       strcpy(A->tab[x][y], " "); /* met une case vide */
    }
}

void Affichage_cadre(Affichage *A){
  int x,y;
   
  /* Cadre */
  for (x=0;x<A->H;x++){
      strcpy(A->tab[x][0],"\33[42m ");
      strcpy(A->tab[x][A->L-1],"\33[42m ");
  }
  for (y=0;y<A->L;y++){
      strcpy(A->tab[0][y],"\33[42m ");
      strcpy(A->tab[A->H-1][y],"\33[42m ");
  }

}


/* Affiche une grille dans le terminal */
void Affichage_dessiner(Affichage *A){
  int x, y;
  
  printf("\33[2J"); /* Efface tout l'ecran */
  printf("\33[H");  /* Deplace le curseur en position (0,0) */ 
  
  for (x=0;x<A->H;x++){
    for (y=0;y<A->L;y++)  /* Affiche les cases de la grille */
      printf("%s\033[00m", A->tab[x][y]);          
    printf("\33[1E");     /* Retour à la ligne */
 }

  printf("\033[00m"); /* Declare le fond noir pour la suite */
  printf("\33[1E");
}


