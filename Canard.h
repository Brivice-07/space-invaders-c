#ifndef CANARD_H
#define CANARD_H

#include "Affichage.h"

typedef enum{
    GAUCHE,
    DROITE
}Direction;

typedef struct Canard{
    int x;
    int y;
    Direction dir;
    struct Canard *suiv;
}Canard;

typedef struct{
    int hauteur_canard;
    int largeur_canard;
    char *representation;
    int x_gauche;
    int x_droite;
    int y;
    int pas;
    Canard *canard;
    int nb_canards;
    int compteur;
}Liste_Canard;

Liste_Canard* Liste_Canard_initialiser_vide(int largeur_aff, int hauteur_aff,
int nivdiff, char * nomfic);

void Canard_desallouer(Liste_Canard** Lcanard);

void ajouter_canard(Liste_Canard* Lcanard);

void Canard_afficher(Liste_Canard *Lcanard, Affichage* A);

int Canard_action(Liste_Canard *Lcanard);

#endif
