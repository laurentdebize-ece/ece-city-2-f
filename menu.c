#include "menu.h"

bool isInRect(int x, int y, int x1, int y1, int x2, int y2) {
    return (x >= x1 && x <= x2 && y >= y1 && y <= y2);
}

void initCases(Case cases[NB_LIGNES_MAX][NB_COLONNES_MAX]) {
    int i, j;
    for (i = 0; i < NB_LIGNES_MAX; i++) {
        for (j = 0; j < NB_COLONNES_MAX; j++) {
            cases[i][j].largeur = 25;
            cases[i][j].hauteur = 25;
            cases[i][j].x = 625 + j * cases[i][j].largeur;
            cases[i][j].y = 145 + i * cases[i][j].hauteur;
            cases[i][j].couleur = NOIR;
            cases[i][j].occupe = 0;
        }
    }
}

void afficherRessources(Info info, ALLEGRO_FONT *text, ALLEGRO_BITMAP *water, ALLEGRO_BITMAP *argent, ALLEGRO_BITMAP *habitant, ALLEGRO_BITMAP *elec) {
    al_draw_filled_rectangle(0, 0, LARGEUR_PLATEAU, 90, GRIS_FONCE);
    al_draw_filled_rectangle(600, 10, 1706, 86, GRIS_CLAIR);
    al_draw_filled_rectangle(603, 13, 1703, 83, BLANC);
    al_draw_filled_rectangle(606, 16, 1700, 80, GRIS_CLAIR);

    al_draw_scaled_bitmap(argent, 0, 0, al_get_bitmap_width(argent), al_get_bitmap_height(argent), 1450, 17, 60, 60, 0);
    al_draw_scaled_bitmap(elec, 0, 0, al_get_bitmap_width(elec), al_get_bitmap_height(elec), 1200, 17, 60, 60, 0);
    al_draw_scaled_bitmap(water, 0, 0, al_get_bitmap_width(water), al_get_bitmap_height(water), 950, 17, 60, 60, 0);
    al_draw_scaled_bitmap(habitant, 0, 0, al_get_bitmap_width(habitant), al_get_bitmap_height(habitant), 700, 17, 60,
                          60, 0);

    al_draw_textf(text, BLANC, 1520, 35, 0, ": %d", info.argent);
    al_draw_textf(text, BLANC, 1270, 35, 0, ": %d", info.elec);
    al_draw_textf(text, BLANC, 1020, 35, 0, ": %d", info.eau);
    al_draw_textf(text, BLANC, 770, 35, 0, ": %d", info.nbhabitant);
}

void afficherToolBox(ALLEGRO_FONT *text, ALLEGRO_FONT *textBold,ALLEGRO_BITMAP *setting, ALLEGRO_BITMAP *cabane, ALLEGRO_BITMAP *watercastle, ALLEGRO_BITMAP *usine, ALLEGRO_BITMAP *route, ALLEGRO_BITMAP *caserne) {

    al_draw_filled_rectangle(0, 0, 450, HAUTEUR_PLATEAU, GRIS_FONCE);

    al_draw_filled_circle(40, 40, 34, GRIS_CLAIR);
    al_draw_filled_circle(40, 40, 32, BLANC);
    al_draw_filled_circle(40, 40, 30, GRIS_CLAIR);
    al_draw_scaled_bitmap(setting, 0, 0, al_get_bitmap_width(setting), al_get_bitmap_height(setting), 15, 15, 50, 50,
                          0);

    al_draw_filled_circle(120, 200, 90, GRIS_CLAIR);
    al_draw_filled_circle(120, 200, 88, BLANC);
    al_draw_filled_circle(120, 200, 86, GRIS_CLAIR);

    al_draw_filled_circle(330, 200, 90, GRIS_CLAIR);
    al_draw_filled_circle(330, 200, 88, BLANC);
    al_draw_filled_circle(330, 200, 86, GRIS_CLAIR);

    al_draw_filled_circle(120, 400, 90, GRIS_CLAIR);
    al_draw_filled_circle(120, 400, 88, BLANC);
    al_draw_filled_circle(120, 400, 86, GRIS_CLAIR);

    al_draw_filled_circle(330, 400, 90, GRIS_CLAIR);
    al_draw_filled_circle(330, 400, 88, BLANC);
    al_draw_filled_circle(330, 400, 86, GRIS_CLAIR);

    al_draw_filled_circle(225, 600, 90, GRIS_CLAIR);
    al_draw_filled_circle(225, 600, 88, BLANC);
    al_draw_filled_circle(225, 600, 86, GRIS_CLAIR);

    al_draw_scaled_bitmap(route, 0, 0, al_get_bitmap_width(route), al_get_bitmap_height(route), 50, 125, 125, 125, 0);
    al_draw_scaled_bitmap(cabane, 0, 0, al_get_bitmap_width(cabane), al_get_bitmap_height(cabane), 240, 115, 160, 160,
                          0);
    al_draw_scaled_bitmap(watercastle, 0, 0, al_get_bitmap_width(watercastle), al_get_bitmap_height(watercastle), 25,
                          290, 190, 300, 0);
    al_draw_scaled_bitmap(usine, 0, 0, al_get_bitmap_width(usine), al_get_bitmap_height(usine), 260, 320, 135, 135, 0);
    al_draw_scaled_bitmap(caserne, 0, 0, al_get_bitmap_width(caserne), al_get_bitmap_height(caserne), 160, 520, 135,
                          135, 0);


    al_draw_filled_rounded_rectangle(50, 740, 400, 820, 10, 10, VERT);
    al_draw_filled_rounded_rectangle(53, 743, 397, 817, 10, 10, NOIR);
    al_draw_filled_rounded_rectangle(56, 746, 394, 814, 10, 10, VERT);
    al_draw_text(textBold, NOIR, 135, 757, 0, "Niveau 0");

    al_draw_filled_rounded_rectangle(50, 840, 400, 920, 10, 10, BLEU);
    al_draw_filled_rounded_rectangle(53, 843, 397, 917, 10, 10, NOIR);
    al_draw_filled_rounded_rectangle(56, 846, 394, 914, 10, 10, BLEU);
    al_draw_text(textBold, NOIR, 135, 857, 0, "Niveau -1");

    al_draw_filled_rounded_rectangle(50, 940, 400, 1020, 10, 10, JAUNE);
    al_draw_filled_rounded_rectangle(53, 943, 397, 1017, 10, 10, NOIR);
    al_draw_filled_rounded_rectangle(56, 946, 394, 1014, 10, 10, JAUNE);
    al_draw_text(textBold, NOIR, 135, 957, 0, "Niveau -2");
}

void dessinerCases(Case cases[NB_LIGNES_MAX][NB_COLONNES_MAX]) {
    int i, j;
    for (i = 0; i < NB_LIGNES_MAX; i++) {
        for (j = 0; j < NB_COLONNES_MAX; j++) {
            al_draw_rectangle(cases[i][j].x, cases[i][j].y, cases[i][j].x + cases[i][j].largeur,
                              cases[i][j].y + +cases[i][j].hauteur, cases[i][j].couleur, 1);
        }
    }
    al_flip_display();
}

void raffraichir(Case cases[NB_LIGNES_MAX][NB_COLONNES_MAX]) {
    al_clear_to_color(BLANC);
    //plateau(fplateau);
    initCases(cases);
    dessinerCases(cases);
    al_flip_display();
}

void menud(ALLEGRO_BITMAP *fond) {
    al_draw_bitmap(fond, 0, 0, 0);
    al_flip_display();
}

void plateau(ALLEGRO_BITMAP *fplateau) {
    al_draw_bitmap(fplateau, 0, 0, 0);
    al_flip_display();
}
