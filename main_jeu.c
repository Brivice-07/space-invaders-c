#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<ncurses.h>

#include"Flechette.h"
#include"Canard.h"
#include"Canon.h"
#include"Affichage.h"

// Liste des évènements possibles
enum evenement {CONTINUE, ECHAP, VICTOIRE, DEFAITE};
    // CONTINUE: le jeu debute ou continue
    // ECHAP: la touche ESC a été utilisée
    // (on peut en ajouter d'autres (victoire etc)

/* Coeur du jeu contenant la boucle événementielle */
void Jeu_Tir(int tailleL, int tailleH, int nivdiff);
//Interaction flechette canard
void Interaction_flechette_canard(Liste_Flechette *Lflech, Liste_Canard *Lcanard, int *score);

/***************************************/


int main(int argv, char **argc){

  if (argv!=4){
     printf("Usage: %s <largeur> <hauteur> <niveau de difficulté>\n",argc[0]);
     exit(2);
  }
  srand(time(NULL));

  Jeu_Tir(atoi(argc[1]), atoi(argc[2]), atoi(argc[3]));

  
  return EXIT_SUCCESS;
}


/***************************************/
//BOucle d'interaction

  void Interaction_flechette_canard(Liste_Flechette *Lflech, Liste_Canard *Lcanard, int *score){
   if(Lflech==NULL || Lcanard==NULL){
      return;
   }
   Flechette *tete=Lflech->flechette;
   Flechette *prev_flech=NULL;
   Canard *can=Lcanard->canard;
   Canard *prev_can=NULL;
   while(tete!=NULL){
      Flechette *next_flech=tete->suiv;
      int collision=0;
      while(can!=NULL){
         Canard *next_can=can->suiv;
         if(can->x<=tete->x && tete->x<=can->x+Lcanard->hauteur_canard && can->y<=tete->y && tete->y<=can->y+Lcanard->largeur_canard){
            if(prev_can == NULL)
               Lcanard->canard = next_can;
            else
               prev_can->suiv = next_can;
            free(can);
            (*score)++;
            if(prev_flech == NULL)
               Lflech->flechette = next_flech;
            else
               prev_flech->suiv = next_flech;
            free(tete);
            collision=1;
            break;
         }
         prev_can=can;
         can=next_can;
      }
      prev_can=NULL;
      can=Lcanard->canard;
      if(!collision)
         prev_flech=tete;
      tete=next_flech;
   }
}

void Jeu_Tir(int tailleL, int tailleH, int nivdiff){
   char *nomfic="canard.txt";
   int score=0;
   int vies=5;
   Liste_Flechette *Lflech=Liste_Flechette_initialiser_vide(tailleH, nivdiff);
   Liste_Canard* Lcanard=Liste_Canard_initialiser_vide(tailleL, tailleH,
   nivdiff, nomfic);
  int ch;   /* Récupération de la saisie clavier, valeur # pour fin de jeu */
  enum evenement res; /* Retour des évènements  */

  /* Initialisation de ncurses et du clavier(4*/
  initscr();
  raw();
  keypad(stdscr, TRUE);
  noecho();
  halfdelay(1);  /* Temps d'exécution max de getch à 1/10ème de seconde */
  
  /* Initialisation des éléments du jeu */
  
  res= CONTINUE;
  
  Affichage *A=Affichage_initialiser(tailleL, tailleH);  

  Canon *C = Canon_initialiser(0, tailleL, tailleH);
  enum action_canon actC;

  
 
  /* Boucle événementielle du jeu */
  do{
  
    ch = getch(); /* Si aucune touche utilisée, getch renvoie -1 */   

    printf("Pour jouer: utiliser les flèches, SPACE pour tirer (ESC pour Sortir)\33[1E\33[1E");
    fflush(stdout);  /* Force l'affichage complet	 */
    static int tick=0;
    tick++;
    if(tick % 20==0){
       ajouter_canard(Lcanard);

   }

    if ( ch!=-1 ){ /* Si une touche a été appuyée */

     switch(ch) {  
        case 27:  /* Code ASCII de la touche ESC-Echap */
           res=ECHAP;
           break;                  
        case KEY_LEFT: 
           actC = Gauche_canon;
           break; 
        case KEY_RIGHT: 
           actC = Droite_canon;
           break;
        case KEY_UP:
           actC = Haut_canon;
           break;
        case KEY_DOWN:
           actC = Bas_canon;
           break;
        case 32:  /* Code ASCII de la touche ESPACE */
           actC = Tir;
           int centre=C->ypos + C->largeur / 2;
            ajouter_flechette(Lflech, centre, C->xpos);
           break;        
        default:
           break;           
       }
               
       if (res!=ECHAP){
	 // Zone des actions dirigeant un élément
          Canon_action(C, actC);
       }
           
     }
     
     // Zone des actions d'éléments agissant automatiquement
     // Comme les fléchettes et les canards
     vies-=Canard_action(Lcanard);
     Flechette_action(Lflech);
     Interaction_flechette_canard(Lflech, Lcanard, &score);
     if(score>=Lcanard->nb_canards){
        res=VICTOIRE;
      }
     if(vies<=0){
        res=DEFAITE;
   }

      Affichage_vider(A);
      Affichage_cadre(A);
      Canon_afficher(C, A);
      Canard_afficher(Lcanard, A);
      Flechette_afficher(Lflech, A);
      // Autre affichage
      Affichage_dessiner(A);
      printf("Score: %d / %d | Vies : %d\33[1E\n", score, Lcanard->nb_canards, vies);

  } while (res== CONTINUE);
  
  if(res==VICTOIRE)
     printf("\nBRAVO VOUS AVEZ ELIMINE TOUS LES CANARDS!!! \33[1E\n");
   if(res==DEFAITE)
      printf("\nGAME OVER!!! Vous avez perdu \33[1E\n");
     
  if (res==ECHAP)
      printf("\n\nVous avez taper ESC pour sortir. \33[1E\n");

  printf("\33[1EAppuyez sur une touche pour sortir\33[1E\n");          
  do{
      ch = getch();
  }while(ch==-1);
  

  endwin(); /* Doit obligatoirement etre mis en fin de programme pour remettre le terminal en etat */  
  
  Affichage_desallouer(&A);  
  Canon_desallouer(&C);
  Flechette_desallouer(&Lflech);
  Canard_desallouer(&Lcanard);
  
 }
 
 
 




