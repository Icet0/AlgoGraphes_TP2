#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "graphe.h"


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++ GENERALITE +++++++++++++++++++++++++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void matrice_identite(int ligne, int colonne, int Id[ligne][colonne])
{
    int i, j ;

    for(i=0 ; i<ligne ; i++)
    {
        for(j=0 ; j<colonne ; j++)
        {
            if(i==j)
                Id[i][j] = 1 ;
            else
                Id[i][j] = 0 ;
        }
    }
}

void copie_matrice(int ligne, int colonne, int Mat[ligne][colonne], int Cop[ligne][colonne])
{
    int i, j ;

    for(i=0 ; i<ligne ; i++)
        for(j=0 ; j<colonne ; j++)
            Cop[i][j] = Mat[i][j] ;
}


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++ TP1 +++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// ------------------ PARTIE 1 ------------------

// QUESTION 1 - Generation d'un graphe alétoire (oriente et possiblement reflexif)
void generation_graphe_1(int s, int M[][s], float p)
{
    int arete_max, i, j, k, nb_aretes ;

    srand(time(NULL)) ;
    // Nombre max d'aretes d'un grahe n-complet + aretes reflexives
    nb_aretes = (p * s * s) / 2 ;

    if(p<=0.5)
    {
        for(i=0 ; i<s ; i++)
            for(j=0 ; j<s ; j++)
                M[i][j] = 0 ;

        for(k=0 ; k<nb_aretes ; k++)
        {
          do
          {
              i = rand()%s ;
              j = rand()%s ;
          }while(M[i][j]==1 || M[j][i]==1) ;

          M[i][j] = 1 ;
        }
    }

    else if(p<=1)
    {
        for(i=0 ; i<s ; i++)
            for(j=0 ; j<s ; j++)
            {
                if(i==j)
                    M[i][j] = 0 ;
                else
                    M[i][j] = 1 ;
            }


        arete_max = (s * s) / 2 ;
        for(k=0 ; k<arete_max-nb_aretes ; k++)
        {
            do
            {
                i = rand()%s ;
                j = rand()%s ;
            }while(M[i][j]==0 || M[j][i]==0) ;

            M[i][j] = 0 ;
        }
    }

    else
      exit(1) ;
}

// QUESTION 3 - Generation d'un graphe alétoire non oriente et irreflexif
void generation_graphe_3(int s, int M[][s], float p)
{
    int arete_max, i, j, k, nb_aretes ;

    srand(time(NULL)) ;
    nb_aretes = (p * s * (s-1)) / 2 ;

    if(p<=0.5)
    {
        for(i=0 ; i<s ; i++)
            for(j=0 ; j<s ; j++)
                M[i][j] = 0 ;

        for(k=0 ; k<nb_aretes ; k++)
        {
          do
          {
              i = rand()%s ;
              j = rand()%s ;
          }while(i==j || M[i][j]==1) ;

          M[i][j] = 1 ;
          M[j][i] = 1 ;
        }
    }

    else if(p<=1)
    {
        for(i=0 ; i<s ; i++)
            for(j=0 ; j<s ; j++)
            {
                if(i==j)
                    M[i][j] = 0 ;
                else
                    M[i][j] = 1 ;
            }


        arete_max = (s * (s-1)) / 2 ;
        for(k=0 ; k<arete_max-nb_aretes ; k++)
        {
            do
            {
                i = rand()%s ;
                j = rand()%s ;
            }while(i==j || M[i][j]==0) ;

            M[i][j] = 0 ;
            M[j][i] = 0 ;
        }
    }

    else
      exit(1) ;
}

// QUESTION 2 - Affichage de la matrice d'adjacence
void afficher_matrice(int s, int M[][s])
{
    int i, j ;

    for(i=0 ; i<s ; i++)
    {
        for(j=0 ; j<s ; j++)
        {
                printf("%3d  ", M[i][j]) ;
        }
        printf("\n") ;
    }
    printf("\n\n") ;
}

// QUESTION 2 - Affichage du graphe sous forme de liste
void afficher_liste(int s, int M[][s])
{
    int i, j ;

    for(i=0 ; i<s ; i++)
        for(j=0 ; j<s ; j++)
            if(j>i && M[i][j] == 1)
                printf("%d ----- %d\n", i+1, j+1) ;

    printf("\n\n") ;
}

// QUESTION 2 - Affichage du degré de chaque sommet
void afficher_degre(int s, int M[][s])
{
    int degre, i, j ;

    for(i=0 ; i<s ; i++)
    {
        degre = 0 ;
        for(j=0 ; j<s ; j++)
            if(M[i][j]==1)
                degre++ ;

        printf("Degre sommet %d = %d\n", i+1, degre) ;
    }

    printf("\n\n") ;
}

// QUESTION 4
void produit_matrice(int s, int M[][s], int T[][s], int New[][s])
{
    int coeff, i, j, k ;

    for(i=0 ; i<s ; i++)
    {
        for(j=0 ; j<s ; j++)
        {
            coeff = 0 ;
            for(k=0 ; k<s ; k++)
            {
                coeff = M[i][k] * T[k][j] + coeff ;
            }
            New[i][j] = coeff ;
        }
    }
}


// QUESTION 4
void puissance_matrice(int s, int M[][s], int p, int New[][s])
{
    int i ;
    int tmp[s][s] ;

    if(p==0)
        matrice_identite(s,s,New) ;
    else
    {
        copie_matrice(s, s, M, tmp) ;
        afficher_matrice(N, tmp) ;
        for(i=2 ; i<=p ; i++)
        {
            produit_matrice(s, M, tmp, New) ;
            afficher_matrice(N, New) ;
            copie_matrice(s, s, New, tmp) ;
        }
    }
}

// QUESTION 5
void afficher_poids(int s, pds P[][s])
{
    int i, j ;

    for(i=0 ; i<s ; i++)
    {
        for(j=0 ; j<s ; j++)
        {
            if(P[i][j].infini == 0)
                printf("%3d  ", P[i][j].valeur) ;
            else
                printf("Inf  ") ;
        }
        printf("\n") ;
    }
    printf("\n\n") ;
}

// QUESTION 5 - Initialise la matrice Poids lorsque tous les poids des chemins sont a 1
void initialiser_poids(int s, int Adj[][s], pds Poids[][s])
{
    int i,  j ;

    for(i=0 ; i<s ; i++)
    {
        for(j=0 ; j<s ; j++)
        {
            if(Adj[i][j]==1)
            {
                Poids[i][j].valeur = 1 ;
                Poids[i][j].infini = 0 ;
            }
            else
            {
                Poids[i][j].valeur = 0 ;
                Poids[i][j].infini = 1 ; // Sommet inaccessible à l'etat 0
            }
        }
    }
}


// QUESTION 5
void floyd_warshall(int s, int Adj[][s], pds Poids[][s])
{
    int i, j, k ;
    pds chemin1, chemin2 ;

    printf("----------- Affichage poids initial  \n");
    afficher_poids(s, Poids) ;

    // Floyd-Warshall
    for(k=0 ; k<s ; k++)
    {
        for(i=0 ; i<s ; i++)
        {
            for(j=0 ; j<s ; j++)
            {
                if(i==j)
                {
                    Poids[i][j].valeur = 0 ;
                    Poids[i][j].infini = 0 ;
                }

                else
                {
                    // Trouver le minimum
                    chemin1.valeur = Poids[i][j].valeur ;
                    chemin1.infini = Poids[i][j].infini ;

                    chemin2.valeur = Poids[i][k].valeur + Poids[k][j].valeur ;
                    chemin2.infini = Poids[i][k].infini + Poids[k][j].infini ;

                    // Si ch1 et ch2 sont infinis
                    if(chemin1.infini!=0 && chemin2.infini!=0)
                    {
                        Poids[i][j].infini = 1 ;
                    }
                    // ch1 est infini ou si ch2 <= ch1
                    else if(chemin1.infini != 0 || (chemin2.infini==0 && chemin2.valeur<=chemin1.valeur))
                    {
                        Poids[i][j].valeur = chemin2.valeur ;
                        Poids[i][j].infini = 0 ;
                    }
                    // ch2 est infini ou si ch2 > ch1
                    else if(chemin2.infini != 0 || (chemin1.infini==0 && chemin2.valeur>chemin1.valeur))
                    {
                        Poids[i][j].valeur = chemin1.valeur ;
                        Poids[i][j].infini = 0 ;
                    }
                    // Erreur
                    else
                        exit(2) ;
                }
            }
        }
    }

    printf("----------- Affichage poids final  \n");
    afficher_poids(s, Poids) ;
}

// QUESTION 6
void copie_poids(int s, pds P[][s], int Poids[][s], int Inf[][s])
{
    int i, j ;

    for(i=0 ; i<s ; i++)
    {
        for(j=0 ; j<s ; j++)
        {
            P[i][j].valeur = Poids[i][j] ;
            P[i][j].infini = Inf[i][j] ;
        }
    }
}


// QUESTION 6
void test_graphe_G()
{
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

    floyd_warshall(8, G, P) ;
}

// ------------------ PARTIE 2 ------------------

// QUESTION 1 - Annexe - Parcours en profondeur
void mouille_voisin_prof(int s, int Adj[][s], int Sec[], int origine)
{
    int i ;

    // On mouille le sommet à l'origine
    Sec[origine] = 0 ;

    for(i=0 ; i<s ; i++)
        if(Adj[i][origine]==1 && Sec[i]!=0)
            mouille_voisin_prof(s,Adj,Sec,i) ;
}

// QUESTION 1 - le sommet initial doit deja etre mouille
void mouille_voisin_larg(int s, int Adj[][s], int Sec[], int origine, int *nb_sec)
{
    int i ;

    // On mouille les voisins
    for(i=0 ; i<s ; i++)
        if(Adj[i][origine]==1)
            Sec[i] = 0 ;
            *nb_sec = *nb_sec - 1 ;

    // On mouille les voisins des voisins
    for(i=0 ; i<s ; i++)
        if(Sec[i]==0 && *nb_sec!=0)
            mouille_voisin_larg(s,Adj,Sec,i,nb_sec) ;
}

// QUESTION 1
int vague(int s, int Adj[][s])
{
    int connexe, i, nb_sec ;
    int Sec[s] ;

    // A l'origine tous les sommets sont secs sauf l'origine
    Sec[0] = 0 ;
    nb_sec = s-1 ;
    for(i=1; i<s; i++)
        Sec[i] = 1 ; // On choisit 1 pour sec, 0 pour mouille

    // On lance la vague
    // mouille_voisin_prof(s,Adj,Sec,0) ;
    mouille_voisin_larg(s,Adj,Sec,0,&nb_sec) ;

    // On verifie si on a touche tout le monde
    i = 0 ;
    connexe = 1 ;
    while(i<s && Sec[i]==0)
    {
        i++ ;
        if(Sec[i]==1) // Si un sommet est encore sec
            connexe = 0 ; // Le graphe n'est pas connexe
    }

    return connexe ;
}


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++ TP2 +++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// ------------------ PARTIE 1 ------------------

void remise_a_zero(int max, int Tab[max])
{
    int i ;

    for(i=0 ; i<max ; i++)
        Tab[i] = 0 ;
}


void printf_tab_ligne(int max, int Tab[max])
{
    int i, j ;

    for(i=0 ; i<max ; i++)
        printf("%d   ",Tab[i]) ;

    printf("\n") ;
}

// QUESTION 2
int algorithme_glouton(int s, int Adj[][s], int Cou[])
{
    int couleur, i, j, nb_coul ;
    int Voisins[s] ; // Contient les couleurs utilisees par les Voisins
                     // 1 si la couelur est utilisée 0 si elle ne l'est pas

    for(i=0 ; i<s ; i++)
    {
        remise_a_zero(s, Voisins) ;
        Voisins[Cou[i]-1] = 1 ;

        // Recupération de la couleur des voisins
        for(j=0 ; j<s ; j++)
        {
            if(Adj[i][j]==1)
            {
                couleur = Cou[j] ; // On recupere la couleur du voisins
                Voisins[couleur-1] = 1 ; // On note que la couleur est utilisee
            }
        }

        if(i!=0)
        {
            j=0 ;
            while(j<s && Voisins[j]!=0)
            {
                j++ ;
            }

            Cou[i] = j+1 ;
        }

    }

    nb_coul = 0 ;
    for(i=0 ; i<s ; i++)
        if(Cou[i]>nb_coul)
            nb_coul = Cou[i] ;


    return nb_coul ;
}

// QUESTION 5
void compte_degre(int s, int Adj[][s], int Deg[])
{
    int i, j ;

    for(i=0 ; i<s ; i++)
        Deg[i] = 0 ;

    for(i=0 ; i<s ; i++)
        for(j=0 ; j<s ; j++)
            if(Adj[i][j]==1)
                Deg[i]++ ;
}

//
void realigne_colonne(int s, int V[][s], int Deg[])
{
    int i, k, l ;

    for(i=0 ; i<s ; i++)
    {
        if(Deg[i]!=0)
        {
            k = 0 ;
            while(k<s)
            {
                if(V[k][i]==0)
                {
                    l = k ;
                    while(l<s && V[l][i]==0)
                    {
                        l++ ;
                    }
                    if(l<s)
                    {
                        V[k][i] = V[l][i] ;
                        V[l][i] = 0 ;
                    }

                }
                k++ ;
            }
        }
    }
}



//
int balaye_colonne(int s, int V[][s], int Deg[])
{
    int i, j ;
    int suppression = 0 ;
    int realigne = 0 ;

    i = 0 ;
    while(i<s)
    {
        if(Deg[i]!=0)
        {
            j = 0 ;
            while(j<s)
            {
                if(V[j][i]!=0 && Deg[V[j][i]-1]<4)
                {
                    V[j][i] = 0 ;
                    Deg[i]-- ;
                    suppression = 1 ;
                    realigne = 1 ;
                }

                j++ ;
            }
        }
        i++ ;
        if(suppression==1 && i==s)
        {
            printf("blay interm\n");
            afficher_matrice(s, V) ;
            i = i%s ;
            suppression = 0 ;

            for(j=0 ; j<s ; j++)
                printf("Deg[%d] = %d\n", j, Deg[j]) ;
        }
    }

    if(realigne==1)
    {
        realigne_colonne(s, V, Deg) ;
        printf("realignement colonne\n") ;
        afficher_matrice(s, V) ;
    }


    return suppression ;
}

// QUESTION 5
int supprime_voisins(int s, int V[][s], int Deg[], int origine)
{
    int i, j ;
    int continuer = 0 ;
    int supprimer = 0 ;
    int nb_sommet = 0 ;

    for(i=0 ; i<s ; i++)
        if(Deg[i]!=0)
            nb_sommet++ ;

    i = 0 ;
    while(i<s)
    {
        j = 0 ;
        while(j<s && V[j][i]!=0)
        {
            j++ ;
        }
        Deg[i] = j ; // On compte le degre d'un sommet apres avoir coupe les liaisons
        if(Deg[i]!=0 && Deg[i]<4)
        {
            for(j=0 ; j<s ; j++)
            {
                V[j][i] = 0 ;

            }
            Deg[i] = 0 ;
            nb_sommet-- ;
            if(nb_sommet==0)
                continuer = 0 ;
            else
            {
                continuer = 1 ;
                supprimer = 1 ;
            }

        }
        i++ ;
        if(continuer == 1 && i==s)
        {
            i = i%s ;
            continuer = 0 ;
        }

    }
    printf("suppr\n") ;
    return supprimer ;
}

// QUESTION 5
int K5(int s, int Adj[][s])
{
    int a, b ;
    int i, j, k, nb_deg4sup=0, res=0 ;
    int Deg[s] ; // Contient le degre de chaque sommet
    int Voisins[s][s] ; // Contient les voisins de chaque sommet de degre sup a 4

    // Si le graphe a moins de 5 sommets il ne peut pas etre K5
    if(s>=5)
    {
        compte_degre(s,Adj,Deg) ;

        i=0 ;
        while(i<s && nb_deg4sup<4)
        {
            i++ ;
            if(Deg[i]>=4)
                nb_deg4sup++ ;
        }

        // Si on a au moins 5 sommets de degre >= 5
        if(nb_deg4sup>=4)
        {
            // Mise a zero du tableau Voisins
            for(i=0 ; i<s ; i++)
                for(j=0 ; j<s ; j++)
                    Voisins[i][j] = 0 ;

            // Remplissage du tableau Voisin
            for(i=0 ; i<s ; i++)
            {

                if(Deg[i]>=4)
                {
                    k = 0 ;
                    for(j=0 ; j<s ; j++)
                    {
                        if(Adj[i][j]==1 && Deg[j]>=4)
                        {
                            Voisins[k][i] = j+1 ;
                            k++ ;
                        }
                    }
                }
            }
            afficher_matrice(s, Voisins) ;

            /*a = 1 ;
            b = 1 ;
            do
            {
                if(b==1)
                    a = supprime_voisins(s, Voisins, Deg, 0) ;
                else if(a==1)
                    b = balaye_colonne(s, Voisins, Deg) ;

                afficher_matrice(s, Voisins) ;
            } while(a==1 || b==1) ;*/

            //cherche_voisins(s, Voisins, 0) ;

            a = 1 ;
            b = 0 ;
            do
            {
                if(a==1)
                {
                    b = supprime_voisins(s, Voisins, Deg, 0) ;
                    a = 0 ;
                }
                else if(b==1)
                {
                    a = balaye_colonne(s, Voisins, Deg) ;
                    b = 0 ;
                }

                afficher_matrice(s, Voisins) ;
            } while(a==1 || b==1);





            res = 1 ;
        }
    }


    return res ;
}







// QUESTION 1 - le sommet initial doit deja etre mouille
void arbre_mouille_voisin_larg(narbre A, int s, int Adj[][s], int Sec[], int origine, int *nb_sec)
{
    printf("Ici mouille avec %d\n",origine) ;
    int i, j ;
    int m = 0 ;
    narbre ptr, Mou[s] ;

    // On mouille les voisins
    for(i=0 ; i<s ; i++)
        if(Adj[i][origine]==1 && Sec[i]==1)
        {
            Sec[i] = 0 ;
            *nb_sec = *nb_sec - 1 ;

            Mou[m] = n_creer_feuille(i) ;
            printf("fils de %d = %d\n",origine,i) ;
            m++ ;
        }

    // Remplissage des voisins de origine
    for(i=0 ; i<m ; i++)
    {
        if(i==0)
        {
          A->premier_fils = Mou[i] ;
          ptr = A->premier_fils ;
        }
        else
        {
            ptr->frere = Mou[i] ;
            ptr = ptr->frere ;
        }

        printf("i = %d\n", i) ;
        printf("elt = %d\n",ptr->elt) ;
    }


    n_print_arbre(A) ;
    afficher_matrice(s,Adj) ;



    // On mouille les voisins des voisins
    i = 0 ;
    ptr = A->premier_fils ;
    while(i<m && *nb_sec!=0)
    {
        arbre_mouille_voisin_larg(ptr, s, Adj, Sec, ptr->elt, nb_sec) ;
        ptr = ptr->frere ;
        i++ ;
    }

    return ;
}

// QUESTION 1
narbre arbre_vague(int s, int Adj[][s])
{
    int connexe, i, nb_sec ;
    int Sec[s] ;
    narbre A ;

    // A l'origine tous les sommets sont secs sauf l'origine
    Sec[0] = 2 ;
    nb_sec = s-1 ;
    for(i=1; i<s; i++)
        Sec[i] = 1 ; // On choisit 1 pour sec, 0 pour mouille, 2 pour mouille et visite

    // On lance la vague
    // mouille_voisin_prof(s,Adj,Sec,0) ;
    A = n_creer_feuille(0) ;
    arbre_mouille_voisin_larg(A,s,Adj,Sec,0,&nb_sec) ;

    // On verifie si on a touche tout le monde
    i = 0 ;
    connexe = 1 ;
    while(i<s && Sec[i]==0)
    {
        i++ ;
        if(Sec[i]==1) // Si un sommet est encore sec
            connexe = 0 ; // Le graphe n'est pas connexe
    }

    return A ;
}

int cherche_min_ligne(int s, pds Poids[][s], int ligne, int Sommet[])
{
    int j, j_min, min ;

    j=0 ;
    while(j<s && Poids[ligne][j].infini==1)
    {
        j++ ;
    }

    if(j==s)
    {
        printf("Erreur : Sommet isole => Pas de chemin de poids minimal\n") ;
        exit(1) ;
    }

    // On initialise min à la premiere valeur non infinie de la ligne
    min = Poids[ligne][j].valeur ;
    j_min = j ;
    j++ ;

    while(j<s)
    {
        if(Sommet[j]==0 && Poids[ligne][j].infini!=1 && Poids[ligne][j].valeur<min)
        {
            min = Poids[ligne][j].valeur ;
            j_min = j ;
        }
        j++ ;
    }

    printf("pour la ligne %d le min est %d de poids %d\n ", ligne, j_min, min) ;

    return j_min ; 
}

// Le tableau Poids va etre detruit il faut faire une copie avant
int algorithme_Prim(int s, int Adj[][s], pds Poids[][s], int Pred[s], int origine)
{
    int i, j, k, flag, nb_s ;
    int i_min, j_min, cout = 0, min, premier_i, val_test, j_test ;
    int Sommet[s] ; // Les sommets visites
    int Deg[s] ; 

    compte_degre(s,Adj,Deg) ;

    nb_s = 1 ; // Un sommet visite
    Sommet[origine] = 1 ; // On considere le sommet 0

    // Aucun sommet n'est visite personne n'a de predecesseur
    for(i=0 ; i<s ; i++)
            Pred[i] = -1 ;
    
    while(nb_s!=s)
    {
            printf("som[2]=%d\n",Sommet[2]) ;

        i = 0 ;
        premier_i = -1 ;
        while(i<s && nb_s!=s)
        {
            
            if(Sommet[i]==1)
            {           
                if(premier_i==-1)
                    premier_i = i ;

                if(premier_i==i)
                {
                    i_min = i ; 
                    j_min = cherche_min_ligne(s, Poids, i, Sommet) ;
                    min = Poids[i_min][j_min].valeur ;
                    printf(" def som[2]=%d\n",Sommet[2]) ;
                    printf("i_min et j_min = %d %d\n",i_min, j_min) ;
                }  
                else if(premier_i!=i)
                {
                    

                    j_test = cherche_min_ligne(s, Poids, i, Sommet) ;
                    val_test = Poids[i][j_test].valeur ;
                    printf(" cherche som[2]=%d\n",Sommet[2]) ;
                    printf("i_min et j_test = %d %d\n",i, j_test) ;

                    if(val_test<min && Sommet[j_test]==0)
                    {
                        i_min = i ;
                        j_min = j_test ;
                        min = val_test ;
                        printf("validation i_min et j_test = %d %d\n",i_min, j_min) ;
                    }
                }   
                else 
                {
                    printf("RIEN NE SE PASSE\n") ;
                }  
            }  
            i++ ;
        }

        // On a rajoute j_min au graphe en le liant a i_min
        Pred[j_min] = i_min ;

        // Le sommet j_min est visite
        Sommet[j_min] = 1 ;
        nb_s++ ;
        printf("Le sommet %d est visite\n", j_min) ;
        printf("%d -- %d\n", i_min, j_min) ;

         // On supprime l'arete i_min - j_min
        Poids[i_min][j_min].infini = 1 ;
        Poids[j_min][i_min].infini = 1 ;

        // Donc j_min n'est plus considere comme un voisin de i_min, ils sont lies
        Deg[i_min]-- ; printf("deg %d =%d\n", i_min, Deg[i_min]) ;
        Deg[j_min]-- ; printf("deg %d =%d\n", j_min, Deg[j_min]) ;

        // Si toutes les aretes du sommet ont ete exploitees
        // On ne visitera plus ce sommet durant les prochaines boucles
        if(Deg[i_min]==0) 
            Sommet[i_min] = 2 ; 
        if(Deg[j_min]==0) 
            Sommet[j_min] = 2 ;    

        cout = cout + min ;

        printf("\n\n\n\n") ;
        
    }

    return cout ;
}

// QUESTION 3
void affiche_ARM(int s, int A[])
{
    int i ;

    printf("Fils --- Pere\n") ;
    
    for(i=0 ; i<s ; i++)
    {
        if(A[i]==-1) // C'est l'origine de l'ARM
            printf("%4d ---  //\n",i) ;
        else
            printf("%4d --- %4d\n",i,A[i]) ;
    }
}