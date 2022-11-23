#ifndef ECE_CITY_2_F_CHATEAUEAU_H
#define ECE_CITY_2_F_CHATEAUEAU_H
#include "menu.h"

void dessinerChateauEau(int *dessin, Case cases[NB_LIGNES_MAX][NB_COLONNES_MAX], Info *info, ALLEGRO_FONT *text, ALLEGRO_FONT *textBold,
                        ALLEGRO_BITMAP *setting, ALLEGRO_BITMAP *cabane, ALLEGRO_BITMAP *watercastle, ALLEGRO_BITMAP *usine,
                        ALLEGRO_BITMAP *route, ALLEGRO_BITMAP *caserne, ALLEGRO_BITMAP *eau, ALLEGRO_BITMAP *argent,
                        ALLEGRO_BITMAP *habitant, ALLEGRO_BITMAP *elec);

#endif //ECE_CITY_2_F_CHATEAUEAU_H
