#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 4

typedef struct
{
    int valeur ; // Poids d'une arete
    int infini ; // 0 prendre en compte la valeur, 1 considerer le poids comme infini
} pds ;

// Initilise la matrice d'adjacence de la matrice identite
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

// Copie la matrice Mat dans la matrice Cops
void copie_matrice(int ligne, int colonne, int Mat[ligne][colonne], int Cop[ligne][colonne])
{
    int i, j ;

    for(i=0 ; i<ligne ; i++)
        for(j=0 ; j<colonne ; j++)
            Cop[i][j] = Mat[i][j] ;
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++++++++++++++++++++++++ PARTIE 1 ++++++++++++++++++++++++++++++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// --- QUESTION 1 ---
// BUT : Generer un graphe alétoire (oriente et possiblement reflexif)
// PARAMATRES : 
//		s le nombre de sommets
//		M la matrice d'adjacence
//		p la densite voulue
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

// --- QUESTION 3 ---
// BUT : Generer un graphe alétoire non oriente et irreflexif
// PARAMATRES : 
//		s le nombre de sommets
//		M la matrice d'adjacence
//		p la densite voulue
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
          }while(M[i][j]==1) ;

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

// --- QUESTION 2 ---
// BUT : Afficher une matrice d'adjacence
// PARAMATRES : 
//		s le nombre de sommets
//		M la matrice d'adjacence
void afficher_matrice(int s, int M[][s])
{
    int i, j ;

    for(i=0 ; i<s ; i++)
    {
        for(j=0 ; j<s ; j++)
        {
            printf("%d  ", M[i][j]) ;
        }
        printf("\n") ;
    }
    printf("\n\n") ;
}

// --- QUESTION 2 ---
// BUT : Afficher les aretes d'un graphe sous forme de listes
// PARAMATRES : 
//		s le nombre de sommets
//		M la matrice d'adjacence
void afficher_liste(int s, int M[][s])
{
    int i, j ;

    for(i=0 ; i<s ; i++)
        for(j=0 ; j<s ; j++)
            if(j>i && M[i][j] == 1)
                printf("%d ----- %d\n", i+1, j+1) ;

    printf("\n\n") ;
}

// --- QUESTION 2 ---
// BUT : Afficher le degre de tous les sommets du graphes
// PARAMATRES : 
//		s le nombre de sommets
//		M la matrice d'adjacence
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

// --- QUESTION 2 ---
// BUT : Realiser le produit de deux matrices carrees
// PARAMATRES : 
//		s le nombre de sommets
//		M une matrice
//		T une matrice
//		New matrice vide qui contiendra le resultat de M*T
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


// --- QUESTION 4 ---
// BUT : Calculer M a la puissance p
// PARAMATRES : 
//		s le nombre de sommets
//		M une matrice
//		p la puissance voulue
//		New matrice vide qui contiendra le resultat de M^p
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

// --- QUESTION 5 ---
// BUT : Afficher d'une matrice poids
// PARAMATRES : 
//		s le nombre de sommets
//		P un tableau de type pds
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

// --- QUESTION 5 ---
// BUT : Initialiser la matrice Poids quand le poids de tous les chemins est a 1
// PARAMATRES : 
//		s le nombre de sommets
//		Adj une matrice d'adjacence
//		Poids le tableau de pds qui sera rempli au cours de cette procedure
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


// --- QUESTION 5 ---
// BUT : Trouver le plus court chemin entre deux sommets (Algorithme de Floyd-Warshall)
// PARAMATRES : 
//		s le nombre de sommet
//		Adj une matrice d'adjacence
//		Poids le tableau de pds qui sera rempli au cours de cette procedure
void floyd_warshall(int s, int Adj[][s], pds Poids[][s])
{
    int i, j, k ;
    pds min, chemin1, chemin2 ;

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

// --- QUESTION 6 ---
// BUT : Fusionner deux matrices int dans une matrice pds
// PARAMATRES : 
//		s le nombre de sommet
//		P contiendra la matrice de Poids final
//		Poids contient les poids de chaque chemin
//		Inf indique si les chemmins sont infinis ou non
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


// --- QUESTION 6 ---
// BUT : Tester le graphe G avec les procedures des questions precedentes
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



// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++++++++++++++++++++++++ PARTIE 2 ++++++++++++++++++++++++++++++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// --- QUESTION 1 ---
// BUT : Considerer un sommet et mouiller ses voisins (Parcours en profondeur)
// PARAMETRES :
//		s le nombre de sommet
//		Adj la matrice d'adjacence
//		Sec contient si un sommet est sec (1) ou non (0)
//		origine le sommet considere
void mouille_voisin_prof(int s, int Adj[][s], int Sec[], int origine)
{
    int i ;

    // On mouille le sommet à l'origine
    Sec[origine] = 0 ;

    for(i=0 ; i<s ; i++)
        if(Adj[i][origine]==1 && Sec[i]!=0)
            mouille_voisin_prof(s,Adj,Sec,i) ;
}

// --- QUESTION 1 ---
// BUT : Considerer un sommet et mouiller ses voisins (Parcours en largeurs)
// PARAMETRES :
//		s le nombre de sommet
//		Adj la matrice d'adjacence
//		Sec contient si un sommet est sec (1) ou non (0)
//		origine le sommet considere
// 		nb_sec le nombre de sommets secss
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

// --- QUESTION 1 ---
// BUT : Considerer un sommet et mouiller ses voisins (Parcours en largeurs)
// PARAMETRES :
//		s le nombre de sommet
//		Adj la matrice d'adjacence
// SORTIE :
//		1 si le graphe est connexe, 0 sinon
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
    connexe = 1 ; // On suppose le graphe connexe
    while(i<s && Sec[i]==0)
    {
        i++ ;
        if(Sec[i]==1) // Si un sommet est encore sec
            connexe = 0 ; // Le graphe n'est pas connexe
    }

    return connexe ;
}



int main(void)
{
    int Mat[N][N], New[N][N] ;
    pds Poids[N][N] ;

    // ------------------ PARTIE 1 ------------------
    // generation_graphe_3(N, Mat, 0.5) ;
    // afficher_matrice(N, Mat) ;
    // afficher_liste(N, Mat) ;
    // afficher_degre(N, Mat) ;
    // produit_matrice(N, Mat, Mat, New) ;
    // puissance_matrice(N, Mat, 8, New) ;
    // afficher_matrice(N, New) ;
    // initialiser_poids(N, Mat, Poids) ;
    // floyd_warshall(N, Mat, Poids) ;
    // afficher_poids(N, Poids) ;
    //test_graphe_G() ;

    // ------------------ PARTIE 2 ------------------

    // QUESTION 1 - Test de la vague
    generation_graphe_3(N, Mat, 1) ;
    afficher_matrice(N, Mat) ;
    printf("le graphe est %d\n",vague(N,Mat)) ;

    return 0 ;
}
