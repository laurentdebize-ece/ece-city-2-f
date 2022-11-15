#ifndef ECE_CITY_2_F_MENU_H
#define ECE_CITY_2_F_MENU_H
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdlib.h>

#define NB_LIGNES_MAX 35
#define NB_COLONNES_MAX 45
#define HAUTEUR 25
#define LARGEUR 25
#define HAUTEUR_PLATEAU 1080
#define LARGEUR_PLATEAU 1920
#define GRIS_FONCE al_map_rgb(25, 25, 25)
#define GRIS_CLAIR al_map_rgb(50, 50, 50)
#define BLANC al_map_rgb(255, 255, 255)
#define NOIR al_map_rgb(0,0,0)
#define VERT al_map_rgb(50,175,0)
#define BLEU al_map_rgb(0,75,255)
#define JAUNE al_map_rgb(228,234,0)
#define GRIS_TRANSPARENT al_map_rgba(50, 50, 50, 50)

typedef struct {
    int argent;
    int elec;
    int eau;
    int nbhabitant;
} Info;

typedef struct {
    int x, y, largeur, hauteur;
    int occupe;
    ALLEGRO_COLOR couleur;
} Case;

bool isInRect(int x, int y, int x1, int y1, int x2, int y2);
void initCases(Case cases[NB_LIGNES_MAX][NB_COLONNES_MAX]);
void afficherRessources(Info info, ALLEGRO_FONT *text, ALLEGRO_BITMAP *water, ALLEGRO_BITMAP *argent, ALLEGRO_BITMAP *habitant, ALLEGRO_BITMAP *elec);
void afficherToolBox(ALLEGRO_FONT *text, ALLEGRO_FONT *textBold,ALLEGRO_BITMAP *setting, ALLEGRO_BITMAP *cabane, ALLEGRO_BITMAP *watercastle, ALLEGRO_BITMAP *usine, ALLEGRO_BITMAP *route, ALLEGRO_BITMAP *caserne);
void dessinerCases(Case cases[NB_LIGNES_MAX][NB_COLONNES_MAX]);
void raffraichir(Case cases[NB_LIGNES_MAX][NB_COLONNES_MAX]);
void menud(ALLEGRO_BITMAP *fond);
void plateau(ALLEGRO_BITMAP *fplateau);



#endif //ECE_CITY_2_F_MENU_H
