#ifndef ECE_CITY_2_F_MAISON_H
#define ECE_CITY_2_F_MAISON_H
#include "menu.h"

void dessinerMaisons(Case cases[NB_LIGNES_MAX][NB_COLONNES_MAX], ALLEGRO_FONT *text, ALLEGRO_FONT *textBold,
                    ALLEGRO_BITMAP *setting, ALLEGRO_BITMAP *cabane, ALLEGRO_BITMAP *watercastle, ALLEGRO_BITMAP *usine,
                    ALLEGRO_BITMAP *route, ALLEGRO_BITMAP *caserne);

#endif //ECE_CITY_2_F_MAISON_H