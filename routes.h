#ifndef ECE_CITY_2_F_ROUTES_H
#define ECE_CITY_2_F_ROUTES_H
#include "menu.h"

void dessinerRoutes(int *dessin, Case cases[NB_LIGNES_MAX][NB_COLONNES_MAX], Info* info, ALLEGRO_FONT *text,
                    ALLEGRO_FONT *textBold, ALLEGRO_BITMAP *setting, ALLEGRO_BITMAP *cabane,
                    ALLEGRO_BITMAP *watercastle, ALLEGRO_BITMAP *usine, ALLEGRO_BITMAP *caserne,
                    ALLEGRO_BITMAP *routeOE, ALLEGRO_BITMAP *routeNS, ALLEGRO_BITMAP *routeTE,
                    ALLEGRO_BITMAP *routeTN, ALLEGRO_BITMAP *routeTO, ALLEGRO_BITMAP *routeTS,
                    ALLEGRO_BITMAP *routeX, ALLEGRO_BITMAP *virageNE,
                    ALLEGRO_BITMAP *virageON, ALLEGRO_BITMAP *virageSE, ALLEGRO_BITMAP *virageSO,
                    ALLEGRO_BITMAP *eau, ALLEGRO_BITMAP *argent,
                    ALLEGRO_BITMAP *habitant, ALLEGRO_BITMAP *elec, ALLEGRO_BITMAP*route);

#endif //ECE_CITY_2_F_ROUTES_H
