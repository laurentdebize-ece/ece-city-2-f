#include "maison.h"

void dessinerMaisons(int *dessin, Case cases[NB_LIGNES_MAX][NB_COLONNES_MAX], Info* info, ALLEGRO_FONT *text,
                     ALLEGRO_FONT *textBold,
                     ALLEGRO_BITMAP *setting, ALLEGRO_BITMAP *cabane, ALLEGRO_BITMAP *watercastle,
                     ALLEGRO_BITMAP *usine,
                     ALLEGRO_BITMAP *route, ALLEGRO_BITMAP *caserne, ALLEGRO_BITMAP *eau, ALLEGRO_BITMAP *argent,
                     ALLEGRO_BITMAP *habitant, ALLEGRO_BITMAP *elec) {
    assert (al_init());
    assert(al_init_primitives_addon());
    assert(al_install_mouse());
    ALLEGRO_EVENT_QUEUE *queue = NULL;
    int nbMaisonsPosees = 1;
    ALLEGRO_EVENT event;
    al_draw_circle(330, 200, 92, ROUGE, 2);
    queue = al_create_event_queue();
    al_register_event_source(queue, al_get_mouse_event_source());
    al_wait_for_event(queue, &event);
    switch (event.type) {
        case ALLEGRO_EVENT_MOUSE_BUTTON_UP : {
            for (int i = 0; i < NB_LIGNES_MAX; ++i) {
                for (int j = 0; j < NB_COLONNES_MAX; ++j) {
                    if (isInRect(event.mouse.x, event.mouse.y, cases[i][j].x + 1, cases[i][j].y + 1,
                                 cases[i][j].x + HAUTEUR - 1, cases[i][j].y + LARGEUR - 1)) {
                        if (accesConstructionMaison(cases, i, j) && info->argent >= nbMaisonsPosees*1000) {
                            al_draw_scaled_bitmap(cabane, 0, 0, al_get_bitmap_width(cabane),
                                                  al_get_bitmap_height(cabane),
                                                  cases[i][j].x - LARGEUR,
                                                  cases[i][j].y - 2 * HAUTEUR, 75, 75, 0);
                            cases[i][j - 1].occupe = 9;
                            cases[i - 1][j - 1].occupe = 9;
                            cases[i - 2][j - 1].occupe = 9;

                            cases[i][j].occupe = 2;
                            cases[i - 1][j].occupe = 9;
                            cases[i - 2][j].occupe = 9;

                            cases[i][j + 1].occupe = 9;
                            cases[i - 1][j + 1].occupe = 9;
                            cases[i - 2][j + 1].occupe = 9;

                            info->argent -= 1000;
                            info->nbhabitant += 10;
                            nbMaisonsPosees += 1;
                        }
                    }
                }
            }
            if (isInRect(event.mouse.x, event.mouse.y, 263, 133, 397, 267)) {
                afficherRessources(*info, text, eau, argent, habitant, elec);
                afficherToolBox(text, textBold, setting, cabane,
                                watercastle, usine, route, caserne);
                *dessin = -1;
            }
            break;
        }
    }
}