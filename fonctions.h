//
// Created by Paul Busetta on 21/11/2022.
//

#ifndef ECE_CITY_2_F_FONCTION_H
#define ECE_CITY_2_F_FONCTION_H

#include <stdio.h>
#include <stdlib.h>

struct Arc
{
    int sommet; // numero de sommet d'un arc adjacent au sommet initial
    int valeur;
    struct Arc* arc_suivant;
    int distance; // permet de déterminer le poids d'une arrête
};

typedef struct Arc* pArc;

struct Sommet{
    struct Arc* arc;
    int valeur;
    int couleur;
    int pred;
    int distance; //Distance entre un sommet et le sommet initial, sommet0.
    int numeroDeComposanteConnexe; // Pour ne pas prendre les chemins dont on a deja une CC.
    int sommetDepart;
    int sommetArrive;
    int pasDejaSelectionnee;
    int sens;
    int capacite;

};

typedef struct Sommet* pSommet;
typedef struct Sommet* pArete;


typedef struct Graphe1
{
    int taille;
    int orientation;
    int ordre;
    pSommet * pSommet;
    pArete* pArete;
} Graphe1;

typedef struct Graphe2{
    int taille;
    int orientation;
    int ordre;
    pArete* pArete;
    pSommet* pSommet;
} Graphe2;

typedef struct Graphe{
    int taille;
    int orientation;
    int ordre;
    pSommet* pSommet;
    pArete* pArete;
    int** capaciteMax;
    int** fluxActuel;
} Graphe3;

// creer le graphe
Graphe1* CreerGraphe(int ordre);

Graphe1 * lire_graphe(char * nomFichier);

pSommet* CreerArete(pSommet* sommet,int s1,int s2);

void afficher_successeurs(pSommet * sommet, int num);

void graphe_afficher(Graphe1* graphe);



typedef struct Arc* pArc;
typedef struct Sommet* pSommet;

Graphe1* CreerGraphe(int ordre);

Graphe1 * lire_graphe(char * nomFichier);

pSommet* CreerArete(pSommet* sommet,int s1,int s2);

void afficher_successeurs(pSommet * sommet, int num);

void graphe_afficher(Graphe1* graphe);

typedef int typage;

struct _cellule {
    typage element;
    struct _cellule *suivant;
};

typedef struct _cellule* Cellule;

struct _file {
    int longueur;
    Cellule tete;
    Cellule queue;
};

typedef struct _file* File;

#define fileEstVide(F) ((F)->longueur == 0)

File fileVide();

int longueur(File F);

void enfiler(File F, typage element);

typage tete(File F);

void decapiter(File F);

typage defiler(File F);

void afficherFile(File F);

void BFS(Graphe1 *g, int sommet0);

void afficher_successeurs(pSommet *sommet, int num);

void graphe_afficher(Graphe1 *graphe);

void Dijkstra(Graphe1 *g, int sommet0);

void Kruskal(Graphe2 *g);

void Prim(Graphe1 *g, int sommetDeDepart);

void FordFulkerson(Graphe3 *g);

#endif //ECE_CITY_2_F_FONCTION_H
