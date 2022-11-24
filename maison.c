#include "maison.h"

void dessinerMaisons(int *dessin, Case cases[NB_LIGNES_MAX][NB_COLONNES_MAX], Info *info, ALLEGRO_FONT *text,
                     ALLEGRO_FONT *textBold,
                     ALLEGRO_BITMAP *setting, ALLEGRO_BITMAP *cabane, ALLEGRO_BITMAP *watercastle,
                     ALLEGRO_BITMAP *usine,
                     ALLEGRO_BITMAP *route, ALLEGRO_BITMAP *caserne, ALLEGRO_BITMAP *eau, ALLEGRO_BITMAP *argent,
                     ALLEGRO_BITMAP *habitant, ALLEGRO_BITMAP *elec) {
    assert (al_init());
    assert(al_init_primitives_addon());
    assert(al_install_mouse());
    ALLEGRO_MOUSE_STATE mouseState;
    al_get_mouse_state(&mouseState);
    int x = al_get_mouse_state_axis(&mouseState, 0);
    int y = al_get_mouse_state_axis(&mouseState, 1);
    int nbMaisonsPosees = 1;
    al_draw_circle(330, 200, 92, ROUGE, 2);

    if (al_mouse_button_down(&mouseState, 1) == true) {
        for (int i = 0; i < NB_LIGNES_MAX; ++i) {
            for (int j = 0; j < NB_COLONNES_MAX; ++j) {
                if (isInRect(x, y, cases[i][j].x + 1, cases[i][j].y + 1,
                             cases[i][j].x + HAUTEUR - 1, cases[i][j].y + LARGEUR - 1)) {
                    if (accesConstructionMaison(cases, i, j) && info->argent >= nbMaisonsPosees * 1000) {
                        cases[i][j - 1].occupe = 9;
                        cases[i - 1][j - 1].occupe = 9;
                        cases[i - 2][j - 1].occupe = 9;

                        cases[i][j].occupe = 2;
                        cases[i - 1][j].occupe = 9;
                        cases[i - 2][j].occupe = 9;

                        cases[i][j + 1].occupe = 9;
                        cases[i - 1][j + 1].occupe = 9;
                        cases[i - 2][j + 1].occupe = 9;
                        cases[i][j].niveau = 1;
                        info->argent -= 1000;
                        info->nbhabitant += 10;
                        nbMaisonsPosees += 1;
                    }
                }
            }
        }
        if (isInRect(x, y, 263, 133, 397, 267)) {
            afficherRessources(*info, text, eau, argent, habitant, elec);
            afficherToolBox(text, textBold, setting, cabane,
                            watercastle, usine, route, caserne);
            *dessin = -1;
        }
    }
}