#include "routes.h"

bool testInf(Case cases[NB_LIGNES_MAX][NB_COLONNES_MAX], int i, int j, int occupe){
    return (cases[i][j].occupe <= occupe);
}

bool testEgale(Case cases[NB_LIGNES_MAX][NB_COLONNES_MAX], int i, int j, int occupe){
    return (cases[i][j].occupe == occupe);
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
                    if (testInf(cases, i, j, 9)) {
                        ///ROUTES NS
                        if (testInf(cases, i - 1, j, 9) && testInf(cases, i + 1, j, 9) && testInf(cases, i, j - 1, 9) &&
                            testInf(cases, i, j + 1, 9)){
                            cases[i][j].occupe = 10;
                            info->argent -= 10;
                        }
                        if (testEgale(cases, i - 1, j, 11) && testInf(cases, i + 1, j, 9) && (testInf(cases, i, j - 1, 9) &&
                                                                                              testInf(cases, i, j + 1, 9)) &&
                            (testInf(cases, i - 1, j - 1, 9) && testInf(cases, i - 1, j + 1, 9))) {
                            cases[i][j].occupe = 11;
                            info->argent -= 10;
                        }
                        if (testInf(cases, i - 1, j, 9) && testEgale(cases, i + 1, j, 11) && (testInf(cases, i, j - 1, 9) &&
                                                                                              testInf(cases, i, j + 1, 9)) &&
                            (testInf(cases, i + 1, j - 1, 9) && testInf(cases, i + 1, j + 1, 9))) {
                            cases[i][j].occupe = 11;
                            info->argent -= 10;
                        }
                        if (testEgale(cases, i - 1, j, 10) && testInf(cases, i + 1, j, 9) && (testInf(cases, i, j - 1, 9) &&
                                                                                              testInf(cases, i, j + 1, 9)) &&
                            (testInf(cases, i - 1, j - 1, 9) && testInf(cases, i - 1, j + 1, 9))) {
                            cases[i][j].occupe = 11;
                            cases[i-1][j].occupe = 11;
                            info->argent -= 10;
                        }
                        if (testInf(cases, i - 1, j, 9) && testEgale(cases, i + 1, j, 10) && (testInf(cases, i, j - 1, 9) &&
                                                                                              testInf(cases, i, j + 1, 9)) &&
                            (testInf(cases, i + 1, j - 1, 9) && testInf(cases, i + 1, j + 1, 9))) {
                            cases[i][j].occupe = 11;
                            cases[i+1][j].occupe = 11;
                            info->argent -= 10;
                        }
                        if (testEgale(cases, i - 1, j, 11) && testEgale(cases, i + 1, j, 11) && (testInf(cases, i, j - 1, 9) &&
                            testInf(cases, i, j + 1, 9)) && testInf(cases, i + 1, j + 1, 9) && testInf(cases, i - 1, j + 1, 9)) {
                            cases[i][j].occupe = 11;
                        }
                        ///ROUTES OE
                        if (testInf(cases, i - 1, j, 9) && testInf(cases, i + 1, j, 9) && (testEgale(cases, i, j - 1,
                                                                                                     10) &&
                                                                                           testInf(cases, i, j + 1, 9)) &&
                            testInf(cases, i - 1, j - 1, 9) && testInf(cases, i + 1, j - 1, 9)) {
                            cases[i][j].occupe = 10;
                            info->argent -= 10;
                        }
                        if (testInf(cases, i - 1, j, 9) && testInf(cases, i + 1, j, 9) && (testInf(cases, i, j - 1, 9) &&
                                testEgale(cases, i, j + 1, 10)) &&
                            testInf(cases, i + 1, j + 1, 9) && testInf(cases, i - 1, j + 1, 9)) {
                            cases[i][j].occupe = 10;
                            info->argent -= 10;
                        }
                        if (testInf(cases, i - 1, j, 9) && testInf(cases, i + 1, j, 9) && (testEgale(cases, i, j - 1,
                                                                                                     11) &&
                                                                                           testInf(cases, i, j + 1, 9)) &&
                            (testInf(cases, i - 1, j - 1, 9) && testInf(cases, i + 1, j - 1, 9))) {
                            cases[i][j].occupe = 10;
                            cases[i][j-1].occupe = 10;
                            info->argent -= 10;
                        }
                        if (testInf(cases, i - 1, j, 9) && testInf(cases, i + 1, j, 9) && (testInf(cases, i, j - 1, 9) &&
                                testEgale(cases, i, j + 1, 11)) && testInf(cases, i + 1, j + 1, 9) && testInf(cases, i - 1, j + 1, 9)) {
                            cases[i][j].occupe = 10;
                            cases[i][j+1].occupe = 10;
                            info->argent -= 10;
                        }
                        if (testInf(cases, i - 1, j, 9) && testInf(cases, i + 1, j, 9) && (testEgale(cases, i, j - 1, 10) &&
                            testEgale(cases, i, j + 1, 10)) && testInf(cases, i + 1, j + 1, 9) && testInf(cases, i - 1, j + 1, 9)) {
                            cases[i][j].occupe = 10;
                        }

                        ///VIRAGES EO
                        if (testEgale(cases, i - 1, j, 10) && testInf(cases, i + 1, j, 9) && (testInf(cases, i, j - 1, 9) &&
                                                                                              testInf(cases, i, j + 1, 9)) &&
                            (testEgale(cases, i - 1, j - 1, 10) && (testInf(cases, i + 1, j - 1, 9)))) {
                            cases[i][j].occupe = 11;
                            cases[i-1][j].occupe = 15;
                            info->argent -= 10;
                        }
                        if (testInf(cases, i - 1, j, 9) && testEgale(cases, i + 1, j, 10) && (testInf(cases, i, j - 1, 9) &&
                                                                                              testInf(cases, i, j + 1, 9)) &&
                            testInf(cases, i - 1, j - 1, 9) && (testEgale(cases, i + 1, j - 1, 10))) {
                            cases[i][j].occupe = 11;
                            cases[i+1][j].occupe = 12;
                            info->argent -= 10;
                        }
                        if (testEgale(cases, i - 1, j, 10) && testInf(cases, i + 1, j, 9) && (testInf(cases, i, j - 1, 9) &&
                                                                                              testInf(cases, i, j + 1, 9)) &&
                            (testInf(cases, i - 1, j - 1, 9) && testEgale(cases, i - 1, j + 1, 10))) {
                            cases[i][j].occupe = 11;
                            cases[i-1][j].occupe = 14;
                            info->argent -= 10;
                        }
                        if (testInf(cases, i - 1, j, 9) && testEgale(cases, i + 1, j, 10) && (testInf(cases, i, j - 1, 9) &&
                                                                                              testInf(cases, i, j + 1, 9)) &&
                            (testInf(cases, i + 1, j - 1, 9) && testEgale(cases, i + 1, j + 1, 10))) {
                            cases[i][j].occupe = 11;
                            cases[i+1][j].occupe = 13;
                            info->argent -= 10;
                        }

                        ///VIRAGES NS
                        if (testInf(cases, i - 1, j, 9) && testInf(cases, i + 1, j, 9) && (testEgale(cases, i, j - 1,
                                                                                                     11) &&
                                                                                           testInf(cases, i, j + 1, 9)) &&
                            (testEgale(cases, i - 1, j - 1, 11) && (testInf(cases, i + 1, j - 1, 9)))) {
                            cases[i][j].occupe = 10;
                            cases[i][j-1].occupe = 13;
                            info->argent -= 10;
                        }
                        if (testInf(cases, i - 1, j, 9) && testInf(cases, i + 1, j, 9) && (testInf(cases, i, j - 1, 9) &&
                                testEgale(cases, i, j + 1, 11)) &&
                            testEgale(cases, i - 1, j + 1, 11) && testInf(cases, i + 1, j + 1, 9)) {
                            cases[i][j].occupe = 10;
                            cases[i][j+1].occupe = 12;
                            info->argent -= 10;
                        }
                        if (testInf(cases, i - 1, j, 9) && testInf(cases, i + 1, j, 9) && (testEgale(cases, i, j - 1,
                                                                                                     11) &&
                                                                                           testInf(cases, i, j + 1, 9)) &&
                            (testInf(cases, i - 1, j - 1, 9) && (testEgale(cases, i + 1, j - 1, 11)))) {
                            cases[i][j].occupe = 10;
                            cases[i][j-1].occupe = 14;
                            info->argent -= 10;
                        }
                        if (testInf(cases, i - 1, j, 9) && testInf(cases, i + 1, j, 9) && (testInf(cases, i, j - 1, 9) &&
                                testEgale(cases, i, j + 1, 11)) &&
                            testInf(cases, i - 1, j + 1, 9) && testEgale(cases, i + 1, j + 1, 11)) {
                            cases[i][j].occupe = 10;
                            cases[i][j+1].occupe = 15;
                            info->argent -= 10;
                        }

                        ///ROUTES T
                        if (testEgale(cases, i - 1, j, 10) && testInf(cases, i + 1, j, 9) && (testInf(cases, i, j - 1, 9) &&
                                                                                              testInf(cases, i, j + 1, 9)) &&
                            (testEgale(cases, i - 1, j - 1, 10) && testEgale(cases, i - 1, j + 1, 10) && (testInf(cases, i + 1, j - 1,
                                                                                                                  9) &&
                                                                                                          testInf(cases, i + 1, j + 1, 9)))) {
                            cases[i][j].occupe = 11;
                            cases[i-1][j].occupe = 18;
                            info->argent -= 10;
                        }
                        if (testInf(cases, i - 1, j, 9) && testInf(cases, i + 1, j, 9) && (testEgale(cases, i, j - 1,
                                                                                                     11) &&
                                                                                           testInf(cases, i, j + 1, 9)) &&
                                testEgale(cases, i - 1, j - 1, 11) && testInf(cases, i - 1, j + 1, 9) && (testEgale(cases, i + 1,
                                                                                                        j - 1, 11) &&
                                                                                                      testInf(cases, i + 1, j + 1, 9))) {
                            cases[i][j].occupe = 10;
                            cases[i][j-1].occupe = 19;
                            info->argent -= 10;
                        }
                        if (testInf(cases, i - 1, j, 9) && testEgale(cases, i + 1, j, 10) && (testInf(cases, i, j - 1, 9) &&
                                                                                              testInf(cases, i, j + 1, 9)) &&
                            (testInf(cases, i - 1, j - 1, 9) && testInf(cases, i - 1, j + 1, 9) && (testEgale(cases,
                                                                                                              i + 1,
                                                                                                              j - 1, 10) &&
                                                                                                    testEgale(cases, i + 1, j + 1, 10)))) {
                            cases[i][j].occupe = 11;
                            cases[i][j-1].occupe = 16;
                            info->argent -= 10;
                        }
                        if (testInf(cases, i - 1, j, 9) && testInf(cases, i + 1, j, 9) && (testInf(cases, i, j - 1, 9) &&
                                testEgale(cases, i, j + 1, 11)) &&
                            testInf(cases, i - 1, j - 1, 9) && testEgale(cases, i - 1, j + 1, 11) && (testInf(cases, i + 1,
                                                                                                        j - 1, 9) &&
                                                                                                      testEgale(cases, i + 1, j + 1, 11))) {
                            cases[i][j].occupe = 10;
                            cases[i][j+1].occupe = 17;
                            info->argent -= 10;
                        }

                        ///ROUTE X
                        if (testEgale(cases, i - 1, j, 10) && testEgale(cases, i + 1, j, 10) && (testEgale(cases, i, j - 1, 10) &&
                                                                                                 testEgale(cases, i, j + 1, 10)) &&
                            testInf(cases, i - 1, j - 1, 9) && testInf(cases, i - 1, j + 1, 9) && (testInf(cases, i + 1,
                                                                                                           j - 1, 9) &&
                                                                                                   testInf(cases, i + 1, j + 1, 9))) {
                            cases[i][j].occupe = 20;
                            cases[i-1][j].occupe = 11;
                            cases[i+1][j].occupe = 11;
                            info->argent -= 10;
                        }
                        if (testEgale(cases, i - 1, j, 10) && testEgale(cases, i + 1, j, 10) && (testEgale(cases, i, j - 1, 11) &&
                                                                                                 testEgale(cases, i, j + 1, 11)) &&
                            testEgale(cases, i - 1, j - 1, 14) && testEgale(cases, i - 1, j + 1, 15) && (testEgale(cases, i + 1, j - 1,
                                                                                                                   13) &&
                                                                                                         testEgale(cases, i + 1, j + 1, 12))) {
                            cases[i][j].occupe = 20;
                            cases[i-1][j].occupe = 18;
                            cases[i+1][j].occupe = 16;
                            cases[i][j-1].occupe = 19;
                            cases[i][j+1].occupe = 17;
                            info->argent -= 10;
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


