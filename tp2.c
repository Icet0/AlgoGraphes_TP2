#include "stdio.h"

#include "graphe.h"



int main(void)
{
    // Par défaut tous les sommets du graphe dont sans couleur, sauf le sommet 0
    int Couleur[N] ;
    int Adj[N][N] ;
    int nb_couleur ;

    // QUESTION 2
    /*remise_a_zero(N, Couleur) ;
    Couleur[0] = 1 ;

    generation_graphe_3(N, Adj, 0.5) ;
    afficher_matrice(N, Adj) ;

    nb_couleur = algorithme_glouton(N, Adj, Couleur) ;
    printf_tab_ligne(N, Couleur) ;
    printf("Il y a %d couleurs\n",nb_couleur) ;*/

    // QUESTION 3
    /*
        Un graphe planaire est un graphe qui a la particularite de pouvoir
        se representer sur un plan sans qu'aucune arete ou arc ne se croise
    */

    // QUESTION 4
    /*
        Oui, le graphe en annexe du TP1 est planaire
        cf. verso du sujet du TP2
    */

    // QUESTION 5
    generation_graphe_3(N, Adj, 0.35) ;
    afficher_matrice(N, Adj) ;
    if(K5(N, Adj)==1)
      printf("Le graphe est K5\n") ;
    else
        printf("Le graphe n'est pas K5\n") ;

}
