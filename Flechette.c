#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Flechette.h"

Liste_Flechette * Liste_Flechette_initialiser_vide(int hauteur_aff, int nivdiff){

    Liste_Flechette *Lflech = malloc(sizeof(Liste_Flechette));
    if(Lflech==NULL){
        printf("Erreur d'allocation");
        exit(2);
    }
    Lflech->largeur=1;
    Lflech->hauteur=2;
    Lflech->y_depart=0;
    Lflech->y_max=hauteur_aff;

    Lflech->representation="\33[43m^";

    Lflech->flechette=NULL;

    return Lflech;
}

void Flechette_desallouer(Liste_Flechette** Lflech){
    if(*Lflech==NULL)
        return;
    Flechette *cour=(*Lflech)->flechette;
    while(cour!=NULL){
        Flechette *tmp=cour->suiv;
        free(cour);
        cour=tmp;
    }
    free(*Lflech);
    *Lflech=NULL;
}

void ajouter_flechette(Liste_Flechette* Lflech, int y, int x){
    if(1){
        Flechette *flech=malloc(sizeof(Flechette));
        if(flech==NULL){
            perror("Erreur d'allocation");
            exit(2);
        }
        flech->y=y;
        flech->x=x;
        flech->suiv=NULL;

        flech->suiv=Lflech->flechette;
        Lflech->flechette=flech;
    }

}

void Flechette_afficher(Liste_Flechette *Lflech, Affichage* A){
    int y;
    if(Lflech==NULL || Lflech->flechette==NULL)
        return;
    Flechette *cour=Lflech->flechette;
    while(cour!=NULL){
        for(y=cour->x; y<cour->x+Lflech->hauteur; y++){
            if(y>=0 && y<A->H && cour->y>=0 && cour->y <A->L){
                strcpy(A->tab[y][cour->y], Lflech->representation);
            }
        }
        cour=cour->suiv;
    }
}

void Flechette_action(Liste_Flechette *Lflech){
    if(Lflech==NULL || Lflech->flechette==NULL)
        return;
    Flechette *cour=Lflech->flechette;
    Flechette *prev=NULL;
    while(cour!=NULL){
        Flechette *next=cour->suiv;
        cour->x--;
        if(cour->x<=0){
            if(prev==NULL){
                Lflech->flechette=next;
            }else{
                prev->suiv=next;
            }
            free(cour);
        }else{
            prev=cour;
        }
        cour=next;
    }

}
