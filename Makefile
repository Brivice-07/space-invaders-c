all: main_jeu

Affichage.o: Affichage.c Affichage.h 
	gcc -c -Wall Affichage.c

Canon.o: Canon.c Canon.h Affichage.h
	gcc -c -Wall Canon.c

Flechette.o: Flechette.c Flechette.h Affichage.h
	gcc -c -Wall Flechette.c

Canard.o: Canard.c Canard.h Affichage.h
	gcc -c -Wall Canard.c

main_jeu.o: main_jeu.c Affichage.h Canard.h Canon.h Flechette.h
	gcc -c -Wall main_jeu.c

main_jeu: main_jeu.o Affichage.o Canon.o Canard.o Flechette.o
	gcc -g -fsanitize=address -o main_jeu main_jeu.c Affichage.c Canon.c Canard.c Flechette.c -lncurses

clean:
	rm -fr *~ *.o main_jeu
