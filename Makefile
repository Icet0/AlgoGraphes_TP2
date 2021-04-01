CC = gcc
CCOPTS = -Wall

all: tp3

arbre_naire.o:	arbre_naire.c arbre_naire.h
	${CC} ${CCOPTS} -c arbre_naire.c

graphe.o:	graphe.c graphe.h arbre_naire.h
	${CC} ${CCOPTS} -c graphe.c

main.o:	tp3.c
	${CC} ${CCOPTS} -c tp3.c

tp3:	tp3.o arbre_naire.o graphe.o
	${CC} ${CCOPTS} -o tp3 tp3.o arbre_naire.o graphe.o

clean:
	rm *.o ; rm tp3
