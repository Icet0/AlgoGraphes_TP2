#include "stdio.h"

#include "graphe.h"
#include "arbre_naire.h"

int main(void)
{
    /*int Adj[N][N] ;
    pds Poids[N][N] ;
    narbre A ;*/

    int ARM[N] ;

    int G[8][8] = {{0, 0, 1, 0, 0, 1, 0, 0},
                   {0, 0, 0, 0, 0, 0, 1, 1},
                   {1, 0, 0, 1, 1, 1, 0, 1},
                   {0, 0, 1, 0, 0, 0, 1, 0},
                   {0, 0, 1, 0, 0, 0, 0, 0},
                   {1, 0, 1, 0, 0, 0, 1, 1},
                   {0, 1, 0, 1, 0, 1, 0, 0},
                   {0, 1, 1, 0, 0, 1, 0, 0}} ;

    pds P[8][8];

    int Poids[8][8] = {{ 0,  0, 36,  0,  0, 19,  0,  0},
                       { 0,  0,  0,  0,  0,  0, 50, 43},
                       {36,  0,  0, 56, 55, 31,  0, 36},
                       { 0,  0, 56,  0,  0,  0, 15,  0},
                       { 0,  0, 55,  0,  0,  0,  0,  0},
                       {19,  0, 31,  0,  0,  0, 37, 52},
                       { 0, 50,  0, 15,  0, 37,  0,  0},
                       { 0, 43, 36,  0,  0, 52,  0,  0}} ;

    int Inf[8][8] = {{1, 1, 0, 1, 1, 0, 1, 1},
                     {1, 1, 1, 1, 1, 1, 0, 0},
                     {0, 1, 1, 0, 0, 0, 1, 0},
                     {1, 1, 0, 1, 1, 1, 0, 1},
                     {1, 1, 0, 1, 1, 1, 1, 1},
                     {0, 1, 0, 1, 1, 1, 0, 0},
                     {1, 0, 1, 0, 1, 0, 1, 1},
                     {1, 0, 0, 1, 1, 0, 1, 1}} ;

    copie_poids(8, P, Poids, Inf) ;

    // QUESTION 1
    /*
        Un arbre de recouvrement est un arbre inclus dans un graphe G et qui
        connecte tous les sommet du graphe G.
        Un arbre de recouvrement minimal est un arbre de recouvrement dont la
        somme des poids des arêtes est minimale (cad de poids inferieur ou egal
        a celui de tous les autres arbres de recouvrement du graphe).
    */

    // QUESTION 2
    /*
        La façon la plus efficace pour représenter des arbres me semble être les
        listes chainees.
    */

    // QUESTION 3
    /*generation_graphe_3(N, Adj, 1) ;
    afficher_matrice(N,Adj) ;

    A = arbre_vague(N, Adj) ;
    printf("affichage arbre\n") ;

    n_print_arbre(A) ;

    initialiser_poids(N, Adj, Poids) ;
    afficher_poids(N, Poids) ;
    algorithme_Prim(N, Adj, Poids) ;*/

    afficher_poids(N, P) ;
    algorithme_Prim(N, G, P, ARM, 0) ;
    affiche_ARM(N, ARM) ;

    //n_free_arbre(A) ;

    return 0 ;
}
