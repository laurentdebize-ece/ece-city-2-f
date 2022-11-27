#include "TDG.h"

Graphe *creerGraphe(int ordre) {
    Graphe *NewGraphe = malloc(sizeof(Graphe));
    NewGraphe->pSommet = malloc(sizeof(pSommet) * ordre);

    for (int i = 0; i < ordre; ++i) {
        NewGraphe->pSommet[i] = malloc(sizeof(pSommet) * ordre);
        NewGraphe->pSommet[i]->arete = NULL;
    }
    return NewGraphe;
}

pSommet *creerArete(pSommet *sommet, int s1, int s2) {
    if (sommet[s1]->arete == NULL) {
        pArete newArete = malloc(sizeof(struct Arete));
        newArete->sommet = s2;
        newArete->arete_suivante = NULL;
        sommet[s1]->arete = newArete;
        return sommet;
    } else {
        pArete temp = sommet[s1]->arete;
        while (temp->arete_suivante != NULL) {
            temp = temp->arete_suivante;
        }
        pArete newArete = malloc(sizeof(struct Arete));
        newArete->sommet = s2;
        newArete->arete_suivante = NULL;

        if (temp->sommet > s2) {
            newArete->arete_suivante = temp->arete_suivante;
            newArete->sommet = temp->sommet;
            temp->sommet = s2;
            temp->arete_suivante = newArete;
            return sommet;
        }
        temp->arete_suivante = newArete;
        return sommet;
    }
}

int adjacent(Case cases[NB_LIGNES_MAX][NB_COLONNES_MAX], int i, int j) {
    if (cases[i][j].sommetAdjN != 0) {
        return cases[i - 1][j].sommet;
    } else if (cases[i][j].sommetAdjS != 0) {
        return cases[i + 1][j].sommet;
    } else if (cases[i][j].sommetAdjO != 0) {
        return cases[i][j - 1].sommet;
    } else if (cases[i][j].sommetAdjE != 0) {
        return cases[i][j + 1].sommet;
    } else {
        return 0;
    }
}

void creerFichierArete(Case cases[NB_LIGNES_MAX][NB_COLONNES_MAX], int nbRoute) {
    FILE *fichier = NULL;
    fichier = fopen("../graphe_route.txt", "r+");
    int taille = 0;
    if (fichier != NULL) {
        if (nbRoute != 0) {
            for (int i = 0; i < NB_LIGNES_MAX; ++i) {
                for (int j = 0; j < NB_COLONNES_MAX; ++j) {
                    if (cases[i][j].routeTDG == 1 && cases[i][j].decouvert == false) {
                        if (cases[i][j].sommetAdjN != 0) {
                            fprintf(fichier, "%d %d ", cases[i][j].sommet, cases[i - 1][j].sommet);
                            fprintf(fichier, "\n");
                            taille ++;
                        } if (cases[i][j].sommetAdjS != 0) {
                            fprintf(fichier, "%d %d ", cases[i][j].sommet, cases[i + 1][j].sommet);
                            fprintf(fichier, "\n");
                            taille ++;
                        } if (cases[i][j].sommetAdjO != 0) {
                            fprintf(fichier, "%d %d ", cases[i][j].sommet, cases[i][j - 1].sommet);
                            fprintf(fichier, "\n");
                            taille ++;
                        } if (cases[i][j].sommetAdjE != 0) {
                            fprintf(fichier, "%d %d ", cases[i][j].sommet, cases[i][j + 1].sommet);
                            fprintf(fichier, "\n");
                            taille ++;
                        }
                        cases[i][j].decouvert = true;
                        fprintf(fichier, "\n");
                    }
                }
            }
        }
    } else {
        printf("Impossible d'ouvrir le fichier txt");
    }
}

int creerTableauRouteAdjacentes(Case cases[NB_LIGNES_MAX][NB_COLONNES_MAX]) {
    int nbRoute = 0;
    for (int i = 0; i < NB_LIGNES_MAX; ++i) {
        for (int j = 0; j < NB_COLONNES_MAX; ++j) {
            if (cases[i][j].occupe >= 10 && cases[i][j].occupe <= 20) {
                cases[i][j].routeTDG = 1;
                nbRoute++;
                cases[i][j].sommet = nbRoute;
                for (int k = 0; k < nbRoute; ++k) {
                    if (cases[i - 1][j].routeTDG == 1) {
                        cases[i][j].sommetAdjN = cases[i - 1][j].sommet;
                    }
                    if (cases[i + 1][j].routeTDG == 1) {
                        cases[i][j].sommetAdjS = cases[i + 1][j].sommet;
                    }
                    if (cases[i][j - 1].routeTDG == 1) {
                        cases[i][j].sommetAdjO = cases[i][j - 1].sommet;
                    }
                    if (cases[i][j + 1].routeTDG == 1) {
                        cases[i][j].sommetAdjE = cases[i][j + 1].sommet;
                    }
                }
            }
        }
    }
    return nbRoute;
}
