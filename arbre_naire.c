#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "arbre_naire.h"

// Type abstrait de données

narbre n_creer_arbre_vide (void)
{
  return NULL ;
}

narbre n_creer_arbre(NElt e, narbre *fils, int n)
{
  narbre rslt = (narbre)malloc(sizeof(nnoeud)) ;
  rslt->elt = e ;
  rslt->frere = NULL ;

  int i = 0 ;
  // On cherche le premier fils non vide
  while(i<n && n_est_arbre_vide(fils[i]))
    i++ ;

  if(i==n)
    rslt->premier_fils = NULL ;
  else
    rslt->premier_fils = fils[i] ;

  // On ajoute les frères suivants
  for(i=i+1 ; i<n ; i++)
  {
    if(!n_est_arbre_vide(fils[i]))
    {
      narbre curr = rslt->premier_fils ;

      while(!n_est_arbre_vide(curr->frere))
        curr = curr->frere ;

      curr->frere = fils[i] ;
    }
  }

  return rslt ;
}

narbre n_fils_i(narbre a, int i)
{
  narbre currfils = a->premier_fils ;
  int cpt = 0 ;

  while(!n_est_arbre_vide(currfils) && cpt<0)
  {
    currfils = currfils->frere ;
    cpt++ ;
  }

  return currfils ;
}


NElt n_racine(narbre a)
{
  assert(!n_est_arbre_vide(a)) ;
  return a->elt ;
}

bool n_est_arbre_vide(narbre a)
{
  return (a == NULL) ;
}

// Fonctions outils

narbre n_creer_feuille(NElt e)
{
  return n_creer_arbre(e, NULL, 0) ;
}

bool n_est_feuille(narbre a)
{
  if (n_est_arbre_vide(a))
    return 0 ;
  return (n_est_arbre_vide(a->premier_fils)) ;
}

void n_print_arbre_aux(narbre a)
{
  narbre tmp ;
  if (n_est_arbre_vide(a))
    printf(".") ;
  else
  {
    printf("%c (", a->elt) ;
    tmp = a->premier_fils ;
    while(!n_est_arbre_vide(tmp))
    {
      n_print_arbre_aux(tmp) ;
      printf(" - ") ;
      tmp = tmp->frere ;
    }
    printf(")") ;
  }
}

void n_print_arbre_elysa(narbre a, int prof)
{
  if(!n_est_arbre_vide(a))
  {

    for (int i=0; i < prof; i++)
    {
        if(i!=prof-1)
            fputs("|    ", stdout);

        else
            fputs("|___ ", stdout);
    }


    printf("%d\n",a->elt) ;

    if(!n_est_arbre_vide(a->premier_fils))
        n_print_arbre_elysa(a->premier_fils, prof+1) ;
    if(!n_est_arbre_vide(a->frere))
      n_print_arbre_elysa(a->frere, prof) ;
  }
}

void n_print_arbre(narbre a) // Notation préfixe
{
  n_print_arbre_elysa(a,0);
  printf("\n") ;
}

void n_free_noeud(narbre a)
{
  free(a) ;
}

void n_free_arbre(narbre a)
{
  narbre tmp, tmp2 ;
  if(!n_est_arbre_vide(a))
  {
    tmp = a->premier_fils ;
    while (!n_est_arbre_vide(tmp))
    {
      tmp2 = tmp->frere ;
      n_free_arbre(tmp) ;
      tmp = tmp2 ;
    }
    free(a) ;
  }
}
