#ifndef FLECHETTE_H
#define FLECHETTE_H

#include "Affichage.h"

typedef struct Flechette{
    int y;//position horizontale
    int x;//position verticale
    struct Flechette *suiv;//pointeur vers flechette suivante
}Flechette;

typedef struct{
    int largeur;//largeur flechette
    int hauteur;//hauteur flechette
    char *representation;//representation flechette

    int y_depart;//position de depart des flechettes
    int y_max;//position maxima·le où elles disparaissent

    Flechette *flechette;//1re flechette

}Liste_Flechette;

Liste_Flechette * Liste_Flechette_initialiser_vide(int hauteur_aff, int nivdiff);

void Flechette_desallouer(Liste_Flechette** Lflech);

void ajouter_flechette(Liste_Flechette* Lflech, int y, int x);

void Flechette_afficher(Liste_Flechette *Lflech, Affichage* A);

void Flechette_action(Liste_Flechette *Lflech);
#endif
