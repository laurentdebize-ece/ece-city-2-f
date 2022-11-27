#ifndef ECE_CITY_2_F_TDG_H
#define ECE_CITY_2_F_TDG_H
#include "menu.h"

int creerTableauRouteAdjacentes(Case cases[NB_LIGNES_MAX][NB_COLONNES_MAX]);
int adjacent(Case cases[NB_LIGNES_MAX][NB_COLONNES_MAX], int i, int j);
void creerFichierArete(Case cases[NB_LIGNES_MAX][NB_COLONNES_MAX], int nbRoute);




#endif //ECE_CITY_2_F_TDG_H
