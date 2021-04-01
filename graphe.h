#ifndef GRAPHE_H
#define GRAPHE_H

#include "arbre_naire.h"
#define N 8

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++ GENERALITE +++++++++++++++++++++++++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

typedef struct
{
    int valeur ;
    int infini ; // Si 0 valeur, infini si different de 0
} pds ; 

void matrice_identite(int ligne, int colonne, int Id[ligne][colonne]) ;
void copie_matrice(int ligne, int colonne, int Mat[ligne][colonne], int Cop[ligne][colonne]) ;


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++ TP1 +++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// ------------------ PARTIE 1 ------------------

// QUESTION 1 - Generation d'un graphe alétoire (oriente et possiblement reflexif)
void generation_graphe_1(int s, int M[][s], float p) ;

// QUESTION 2 - Affichage de la matrice d'adjacence
void afficher_matrice(int s, int M[][s]) ;

// QUESTION 2 - Affichage du graphe sous forme de liste
void afficher_liste(int s, int M[][s]) ;

// QUESTION 2 - Affichage du degré de chaque sommet
void afficher_degre(int s, int M[][s]) ;

// QUESTION 3 - Generation d'un graphe alétoire non oriente et irreflexif
void generation_graphe_3(int s, int M[][s], float p) ;

// QUESTION 4
void produit_matrice(int s, int M[][s], int T[][s], int New[][s]) ;

// QUESTION 4
void puissance_matrice(int s, int M[][s], int p, int New[][s]) ;

// QUESTION 5
void afficher_poids(int s, pds P[][s]) ;

// QUESTION 5 - Initialise la matrice Poids lorsque tous les poids des chemins sont a 1
void initialiser_poids(int s, int Adj[][s], pds Poids[][s]) ;

// QUESTION 5
void floyd_warshall(int s, int Adj[][s], pds Poids[][s]) ;

// QUESTION 6
void copie_poids(int s, pds P[][s], int Poids[][s], int Inf[][s]) ;

// QUESTION 6
void test_graphe_G() ;


// ------------------ PARTIE 2 ------------------

// QUESTION 1 - Annexe - Parcours en profondeur
void mouille_voisin_prof(int s, int Adj[][s], int Sec[], int origine) ;

// QUESTION 1 - Annexe - Parcours en largeur
// le sommet initial doit deja etre mouille
void mouille_voisin_larg(int s, int Adj[][s], int Sec[], int origine, int *nb_sec) ;

// QUESTION 1
int vague(int s, int Adj[][s]) ;



// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++ TP2 +++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// ------------------ PARTIE 1 ------------------

void remise_a_zero(int max, int Tab[max]) ;

// Affiche un tableau d'une seule ligne
void printf_tab_ligne(int max, int Tab[max]) ;

// QUESTION 2
int algorithme_glouton(int s, int Adj[][s], int Cou[]) ;

int K5(int s, int Adj[][s]) ;




// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++ TP3 +++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// ------------------ PARTIE 1 ------------------
narbre arbre_vague(int s, int Adj[][s]) ;

// QUESTION 3
int algorithme_Prim(int s, int Adj[][s], pds Poids[][s], int Pred[s], int origine) ;

// QUESTION 3
void affiche_ARM(int s, int A[]) ;


#endif
