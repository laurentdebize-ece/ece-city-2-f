#include "routes.h"

void dessinerRoutes(int *dessin, Case cases[NB_LIGNES_MAX][NB_COLONNES_MAX], Info info, ALLEGRO_FONT *text,
                    ALLEGRO_FONT *textBold,
                    ALLEGRO_BITMAP *setting, ALLEGRO_BITMAP *cabane, ALLEGRO_BITMAP *watercastle, ALLEGRO_BITMAP *usine,
                    ALLEGRO_BITMAP *route, ALLEGRO_BITMAP *caserne, ALLEGRO_BITMAP *virageHaut, ALLEGRO_BITMAP *eau,
                    ALLEGRO_BITMAP *argent,
                    ALLEGRO_BITMAP *habitant, ALLEGRO_BITMAP *elec) {
    assert (al_init());
    assert(al_init_primitives_addon());
    al_draw_circle(120, 200, 92, ROUGE, 2);
    assert(al_install_mouse());
    ALLEGRO_EVENT_QUEUE *queue = NULL;
    ALLEGRO_EVENT event;
    ALLEGRO_TIMEOUT *timeout = 0;
    queue = al_create_event_queue();
    al_register_event_source(queue, al_get_mouse_event_source());
    if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
        for (int i = 0; i < NB_LIGNES_MAX; ++i) {
            for (int j = 0; j < NB_COLONNES_MAX; ++j) {
                if (isInRect(event.mouse.x, event.mouse.y, cases[i][j].x + 1, cases[i][j].y + 1,
                             cases[i][j].x + HAUTEUR - 1, cases[i][j].y + LARGEUR - 1)) {
                    if (cases[i][j].occupe == 0) {
                        al_draw_filled_rectangle(cases[i][j].x, cases[i][j].y,
                                                 cases[i][j].x + HAUTEUR,
                                                 cases[i][j].y + LARGEUR, NOIR);
                        cases[i][j].occupe = 1;
                        info.argent -= 10;
                    }
                }
            }
        }
        if (isInRect(event.mouse.x, event.mouse.y, 53, 133, 197, 267)) {
            afficherRessources(info, text, eau, argent, habitant, elec);
            afficherToolBox(text, textBold, setting, cabane,
                            watercastle, usine, route, caserne);
            *dessin = -1;
        }
    }
}


