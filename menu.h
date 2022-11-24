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
#define BLEU al_map_rgb(181,236,248)
#define JAUNE al_map_rgb(246,248,181)
#define ROUGE al_map_rgb(255,0,0)
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
    int niveau;
} Case;

typedef struct {
    int occupe, niveau;
} preCase;



bool accesConstructionUsineChateau(Case cases[NB_LIGNES_MAX][NB_COLONNES_MAX], int i, int j);
bool accesConstructionMaison(Case cases[NB_LIGNES_MAX][NB_COLONNES_MAX], int i, int j);
bool isInRect(int x, int y, int x1, int y1, int x2, int y2);
void initCases(Case cases[NB_LIGNES_MAX][NB_COLONNES_MAX]);
void initPreCases(preCase preCases[NB_LIGNES_MAX][NB_COLONNES_MAX]);
void initRessources(Info info);
void afficherRessources(Info info, ALLEGRO_FONT *text, ALLEGRO_BITMAP *water, ALLEGRO_BITMAP *argent, ALLEGRO_BITMAP *habitant, ALLEGRO_BITMAP *elec);
void afficherToolBox(ALLEGRO_FONT *text, ALLEGRO_FONT *textBold,ALLEGRO_BITMAP *setting, ALLEGRO_BITMAP *cabane, ALLEGRO_BITMAP *watercastle, ALLEGRO_BITMAP *usine, ALLEGRO_BITMAP *route, ALLEGRO_BITMAP *caserne);
void dessinerCases(Case cases[NB_LIGNES_MAX][NB_COLONNES_MAX]);
void raffraichir(Case cases[NB_LIGNES_MAX][NB_COLONNES_MAX], Info info, ALLEGRO_BITMAP *fplateau, ALLEGRO_FONT *text,
                 ALLEGRO_FONT *textBold,ALLEGRO_BITMAP *setting,ALLEGRO_BITMAP *cabane, ALLEGRO_BITMAP *watercastle,
                 ALLEGRO_BITMAP *usine, ALLEGRO_BITMAP *route, ALLEGRO_BITMAP *caserne,
                 ALLEGRO_BITMAP *eau, ALLEGRO_BITMAP *argent, ALLEGRO_BITMAP *habitant, ALLEGRO_BITMAP *elec);
void menud(ALLEGRO_BITMAP *fond);
void plateau(ALLEGRO_BITMAP *fplateau);
void dessinerBat(Case cases[NB_LIGNES_MAX][NB_COLONNES_MAX], ALLEGRO_BITMAP* cabane, ALLEGRO_BITMAP * maison, ALLEGRO_BITMAP* immeuble, ALLEGRO_BITMAP* gratteciel, ALLEGRO_BITMAP* watercastle, ALLEGRO_BITMAP* usine,ALLEGRO_BITMAP *routeOE, ALLEGRO_BITMAP *routeNS, ALLEGRO_BITMAP *routeTE, ALLEGRO_BITMAP *routeTN, ALLEGRO_BITMAP *routeTO, ALLEGRO_BITMAP *routeTS, ALLEGRO_BITMAP *routeX, ALLEGRO_BITMAP *virageNE,
                 ALLEGRO_BITMAP *virageON, ALLEGRO_BITMAP *virageSE, ALLEGRO_BITMAP *virageSO);
void dessinerEau(Case cases[NB_LIGNES_MAX][NB_COLONNES_MAX]);
void dessinerElec(Case cases[NB_LIGNES_MAX][NB_COLONNES_MAX]);




#endif //ECE_CITY_2_F_MENU_H
