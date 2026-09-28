#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Canard.h"

Liste_Canard* Liste_Canard_initialiser_vide(int largeur_aff, int hauteur_aff,
int nivdiff, char * nomfic){
    Liste_Canard *Lcanard = malloc(sizeof(Liste_Canard));
    if(Lcanard==NULL){
        printf("Erreur d'allocation");
        exit(2);
    }
    Lcanard->canard=NULL;
    Lcanard->nb_canards=8*nivdiff;
    Lcanard->x_gauche=0;
    Lcanard->x_droite=largeur_aff;
    Lcanard->y=hauteur_aff;
    Lcanard->pas=1;
    Lcanard->compteur=0;
    FILE *f=fopen(nomfic, "r");
    if(f==NULL){
        perror("Erreur d'allocation");
        exit(2);
    }
    fscanf(f, "%d %d", &Lcanard->largeur_canard, &Lcanard->hauteur_canard);
    Lcanard->representation=malloc((Lcanard->largeur_canard*Lcanard->hauteur_canard+10)*(sizeof(char)));
    if(Lcanard->representation==NULL){
        perror("Erreur d'allocation");
        exit(2);
    }
    fscanf(f,"%s", Lcanard->representation);
    fclose(f);
    return Lcanard;
}

void Canard_desallouer(Liste_Canard** Lcanard){
    if(*Lcanard==NULL)
        return;
    Canard *cour=(*Lcanard)->canard;
    while(cour!=NULL){
        Canard *tmp=cour->suiv;
        free(cour);
        cour=tmp;
    }
    free((*Lcanard)->representation);
    free(*Lcanard);
    *Lcanard=NULL;
}

void ajouter_canard(Liste_Canard* Lcanard){

        Canard *tete=malloc(sizeof(Canard));
        if(tete==NULL){
            perror("Erreur d'allocation");
            exit(2);
        }
        tete->x=rand() % (Lcanard->y/2) + 1;
        tete->dir=rand() % 2;

        if(tete->dir==DROITE)
            tete->y=Lcanard->x_gauche;
        else
            tete->y=Lcanard->x_droite;
        tete->suiv=Lcanard->canard;
        Lcanard->canard=tete;
        Lcanard->compteur++;
}

void Canard_afficher(Liste_Canard *Lcanard, Affichage* A){
    int x, y;
    if(Lcanard==NULL || Lcanard->canard==NULL)
        return;
    Canard *cour=Lcanard->canard;
    while(cour!=NULL){
        for(x=cour->x; x<cour->x+Lcanard->hauteur_canard; x++){
            for(y=cour->y; y<cour->y+Lcanard->largeur_canard; y++){
                if(x>=0 && x<A->H && y>=0 && y<A->L){
                    strcpy(A->tab[x][y], Lcanard->representation );
                }
            }
        }
        cour=cour->suiv;
    }
}

int Canard_action(Liste_Canard *Lcanard){
    int perdu=0;
    if(Lcanard==NULL)
        return -1;
    Canard *cour=Lcanard->canard;
    Canard *prev=NULL;
    while(cour!=NULL){
        Canard *next=cour->suiv;
        if(cour->dir==DROITE){
            if(cour->y<Lcanard->x_droite){
                cour->y+=Lcanard->pas;
                prev=cour;
            }else{
                Canard *tmp=cour;
                if(prev==NULL){
                    Lcanard->canard=next;
                }else{
                    prev->suiv=next;
                }
            free(tmp);
            perdu++;
            }
        }else{
            if(cour->y>Lcanard->x_gauche){
                cour->y-=Lcanard->pas;
                prev=cour;
            }else{
                Canard *tmp=cour;
                if(prev==NULL){
                    Lcanard->canard=next;
                }else{
                    prev->suiv=next;
                }
            free(tmp);
            perdu++;
            }
        }
        cour=next;
    }
    return perdu;
}


