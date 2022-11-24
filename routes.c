#include "routes.h"

bool test(Case cases[NB_LIGNES_MAX][NB_COLONNES_MAX], int i, int j, int occupe){
    return (cases[i][j].occupe <= occupe);
}




void dessinerRoutes(int *dessin, Case cases[NB_LIGNES_MAX][NB_COLONNES_MAX], Info *info, ALLEGRO_FONT *text,
                    ALLEGRO_FONT *textBold,
                    ALLEGRO_BITMAP *setting, ALLEGRO_BITMAP *cabane, ALLEGRO_BITMAP *watercastle, ALLEGRO_BITMAP *usine,
                    ALLEGRO_BITMAP *caserne, ALLEGRO_BITMAP *eau, ALLEGRO_BITMAP *argent,
                    ALLEGRO_BITMAP *habitant, ALLEGRO_BITMAP *elec, ALLEGRO_BITMAP *route) {
    assert (al_init());
    assert(al_init_primitives_addon());
    assert(al_install_mouse());
    ALLEGRO_MOUSE_STATE mouseState;
    al_get_mouse_state(&mouseState);
    int x = al_get_mouse_state_axis(&mouseState, 0);
    int y = al_get_mouse_state_axis(&mouseState, 1);

    al_draw_circle(120, 200, 92, ROUGE, 2);

    if (al_mouse_button_down(&mouseState, 1) == true) {
        for (int i = 0; i < NB_LIGNES_MAX; ++i) {
            for (int j = 0; j < NB_COLONNES_MAX; ++j) {
                if (isInRect(x, y, cases[i][j].x + 1, cases[i][j].y + 1,
                             cases[i][j].x + HAUTEUR - 1, cases[i][j].y + LARGEUR - 1)) {
                    if (test(cases, i, j,   9)) {
                        ///ROUTES NS
                        if (test(cases, i-1, j, 9) && test(cases, i+1, j, 9) && test(cases, i, j-1, 9) && test(cases, i, j+1, 9)){
                            cases[i][j].occupe = 10;
                        }
                        if (test(cases, i-1, j, 11) && test(cases, i+1, j, 9) && (test(cases, i, j-1, 9) && test(cases, i, j+1, 9)) &&
                        (test(cases, i-1, j-1, 9) && test(cases, i-1, j+1, 9))) {
                            cases[i][j].occupe = 11;
                        }
                        if (test(cases, i-1, j, 9) && test(cases, i+1, j, 11) && (test(cases, i, j-1, 9) && test(cases, i, j+1, 9)) &&
                            (test(cases, i+1, j-1, 9) && test(cases, i+1, j+1, 9))) {
                            cases[i][j].occupe = 11;
                        }
                        if (test(cases, i-1, j, 10) && test(cases, i+1, j, 9) && (test(cases, i, j-1, 9) && test(cases, i, j+1, 9)) &&
                            (test(cases, i-1, j-1, 9) && test(cases, i-1, j+1, 9))) {
                            cases[i][j].occupe = 11;
                            cases[i-1][j].occupe = 11;
                        }
                        if (test(cases, i-1, j, 9) && test(cases, i+1, j, 10) && (test(cases, i, j-1, 9) && test(cases, i, j+1, 9)) &&
                            (test(cases, i+1, j-1, 9) && test(cases, i+1, j+1, 9))) {
                            cases[i][j].occupe = 11;
                            cases[i+1][j].occupe = 11;
                        }
                        ///ROUTES OE
                        if (test(cases, i-1, j, 9) && test(cases, i+1, j, 9) && (test(cases, i, j-1, 10) && test(cases, i, j+1, 9)) &&
                            test(cases, i-1, j-1, 9) && test(cases, i+1, j-1, 9)) {
                            cases[i][j].occupe = 10;
                        }
                        if (test(cases, i-1, j, 9) && test(cases, i+1, j, 9) && (test(cases, i, j-1, 9) && test(cases, i, j+1, 10)) &&
                            test(cases, i+1, j+1, 9) && test(cases, i-1, j+1, 9)) {
                            cases[i][j].occupe = 10;
                        }
                        if (test(cases, i-1, j, 9) && test(cases, i+1, j, 9) && (test(cases, i, j-1, 11) && test(cases, i, j+1, 9)) &&
                            (test(cases, i-1, j-1, 9) && test(cases, i+1, j-1, 9))) {
                            cases[i][j].occupe = 10;
                            cases[i][j-1].occupe = 10;
                        }
                        if (test(cases, i-1, j, 9) && test(cases, i+1, j, 9) && (test(cases, i, j-1, 9) && test(cases, i, j+1, 11)) &&
                            test(cases, i+1, j+1, 9) && test(cases, i-1, j+1, 9)) {
                            cases[i][j].occupe = 10;
                            cases[i][j+1].occupe = 10;
                        }

                        ///VIRAGES EO
                        if (test(cases, i-1, j, 10) && test(cases, i+1, j, 9) && (test(cases, i, j-1, 9) && test(cases, i, j+1, 9)) &&
                            (test(cases, i-1, j-1, 10) && (test(cases, i+1, j-1, 9)))) {
                            cases[i][j].occupe = 11;
                            cases[i-1][j].occupe = 15;
                        }
                        if (test(cases, i-1, j, 0) && test(cases, i+1, j, 10) && (test(cases, i, j-1, 0) && test(cases, i, j+1, 0)) &&
                            test(cases, i-1, j-1, 0) && (test(cases, i+1, j-1, 10))) {
                            cases[i][j].occupe = 11;
                            cases[i+1][j].occupe = 12;
                        }
                        if (test(cases, i-1, j, 10) && test(cases, i+1, j, 9) && (test(cases, i, j-1, 9) && test(cases, i, j+1, 9)) &&
                            (test(cases, i-1, j-1, 0) && test(cases, i-1, j+1, 10))) {
                            cases[i][j].occupe = 11;
                            cases[i-1][j].occupe = 14;
                        }
                        if (test(cases, i-1, j, 9) && test(cases, i+1, j, 10) && (test(cases, i, j-1, 0) && test(cases, i, j+1, 9)) &&
                            (test(cases, i+1, j-1, 9) && test(cases, i+1, j+1, 10))) {
                            cases[i][j].occupe = 11;
                            cases[i+1][j].occupe = 13;
                        }

                        ///VIRAGES NS
                        if (test(cases, i-1, j, 9) && test(cases, i+1, j, 9) && (test(cases, i, j-1, 11) && test(cases, i, j+1, 9)) &&
                            (test(cases, i-1, j-1, 11) && (test(cases, i+1, j-1, 9)))) {
                            cases[i][j].occupe = 10;
                            cases[i][j-1].occupe = 13;
                        }
                        if (test(cases, i-1, j, 9) && test(cases, i+1, j, 9) && (test(cases, i, j-1, 9) && test(cases, i, j+1, 11)) &&
                           test(cases, i-1, j+1, 11) && test(cases, i+1, j+1, 9)) {
                            cases[i][j].occupe = 10;
                            cases[i][j+1].occupe = 12;
                        }
                        if (test(cases, i-1, j, 9) && test(cases, i+1, j, 9) && (test(cases, i, j-1, 11) && test(cases, i, j+1, 9)) &&
                            (test(cases, i-1, j-1, 9) && (test(cases, i+1, j-1, 11)))) {
                            cases[i][j].occupe = 10;
                            cases[i][j-1].occupe = 14;
                        }
                        if (test(cases, i-1, j, 9) && test(cases, i+1, j, 9) && (test(cases, i, j-1, 9) && test(cases, i, j+1, 11)) &&
                            test(cases, i-1, j+1, 9) && test(cases, i+1, j+1, 11)) {
                            cases[i][j].occupe = 10;
                            cases[i][j+1].occupe = 15;
                        }

                        ///ROUTES T
                        if (test(cases, i-1, j, 10) && test(cases, i+1, j, 9) && (test(cases, i, j-1, 9) && test(cases, i, j+1, 9)) &&
                            (test(cases, i-1, j-1, 10) && test(cases, i-1, j+1, 10) && (test(cases, i+1, j-1, 9) && test(cases, i+1, j+1, 9)))) {
                            cases[i][j].occupe = 11;
                            cases[i-1][j].occupe = 18;
                        }
                        if (test(cases, i-1, j, 9) && test(cases, i+1, j, 9) && (test(cases, i, j-1, 11) && test(cases, i, j+1, 9)) &&
                            test(cases, i-1, j-1, 11) && test(cases, i-1, j+1, 9) && (test(cases, i+1, j-1, 11) && test(cases, i+1, j+1, 9))) {
                            cases[i][j].occupe = 10;
                            cases[i][j-1].occupe = 19;
                        }
                        if (test(cases, i-1, j, 9) && test(cases, i+1, j, 10) && (test(cases, i, j-1, 9) && test(cases, i, j+1, 9)) &&
                            (test(cases, i-1, j-1, 9) && test(cases, i-1, j+1, 9) && (test(cases, i+1, j-1, 10) && test(cases, i+1, j+1, 10)))) {
                            cases[i][j].occupe = 11;
                            cases[i][j-1].occupe = 16;
                        }
                        if (test(cases, i-1, j, 9) && test(cases, i+1, j, 9) && (test(cases, i, j-1, 9) && test(cases, i, j+1, 11)) &&
                            test(cases, i-1, j-1, 9) && test(cases, i-1, j+1, 11) && (test(cases, i+1, j-1, 9) && test(cases, i+1, j+1, 11))) {
                            cases[i][j].occupe = 10;
                            cases[i][j+1].occupe = 17;
                        }

                        ///ROUTE X
                        if (test(cases, i-1, j, 10) && test(cases, i+1, j, 10) && (test(cases, i, j-1, 10) && test(cases, i, j+1, 10)) &&
                            test(cases, i-1, j-1, 9) && test(cases, i-1, j+1, 9) && (test(cases, i+1, j-1, 9) && test(cases, i+1, j+1, 9))) {
                            cases[i][j].occupe = 20;
                            cases[i-1][j].occupe = 11;
                            cases[i+1][j].occupe = 11;
                        }
                        if (test(cases, i-1, j, 10) && test(cases, i+1, j, 10) && (test(cases, i, j-1, 11) && test(cases, i, j+1, 11)) &&
                            test(cases, i-1, j-1, 14) && test(cases, i-1, j+1, 15) && (test(cases, i+1, j-1, 13) && test(cases, i+1, j+1, 12))) {
                            cases[i][j].occupe = 20;
                            cases[i-1][j].occupe = 18;
                            cases[i+1][j].occupe = 16;
                            cases[i][j-1].occupe = 19;
                            cases[i][j+1].occupe = 17;
                        }
                    }
                }
            }
            if (isInRect(x, y, 53, 133, 197, 267)) {
                afficherRessources(*info, text, eau, argent, habitant, elec);
                afficherToolBox(text, textBold, setting, cabane,
                                watercastle, usine, route, caserne);
                *dessin = -1;
            }
        }
    }
}


