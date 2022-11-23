#include "routes.h"

void dessinerRoutes(int *dessin, Case cases[NB_LIGNES_MAX][NB_COLONNES_MAX], Info* info, ALLEGRO_FONT *text,
                    ALLEGRO_FONT *textBold,
                    ALLEGRO_BITMAP *setting, ALLEGRO_BITMAP *cabane, ALLEGRO_BITMAP *watercastle, ALLEGRO_BITMAP *usine, ALLEGRO_BITMAP *caserne,
                    ALLEGRO_BITMAP *routeOE, ALLEGRO_BITMAP *routeNS, ALLEGRO_BITMAP *routeTE, ALLEGRO_BITMAP *routeTN, ALLEGRO_BITMAP *routeTO, ALLEGRO_BITMAP *routeTS, ALLEGRO_BITMAP *routeX, ALLEGRO_BITMAP *virageNE,
                    ALLEGRO_BITMAP *virageON, ALLEGRO_BITMAP *virageSE, ALLEGRO_BITMAP *virageSO, ALLEGRO_BITMAP *eau, ALLEGRO_BITMAP *argent,
                    ALLEGRO_BITMAP *habitant, ALLEGRO_BITMAP *elec, ALLEGRO_BITMAP *route) {
    assert (al_init());
    assert(al_init_primitives_addon());
    assert(al_install_mouse());
    ALLEGRO_EVENT_QUEUE *queue = NULL;
    ALLEGRO_EVENT event;
    al_draw_circle(120, 200, 92, ROUGE, 2);
    queue = al_create_event_queue();
    al_register_event_source(queue, al_get_mouse_event_source());
    al_wait_for_event(queue, &event);
    if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
        for (int i = 0; i < NB_LIGNES_MAX; ++i) {
            for (int j = 0; j < NB_COLONNES_MAX; ++j) {
                if (isInRect(event.mouse.x, event.mouse.y, cases[i][j].x + 1, cases[i][j].y + 1,
                             cases[i][j].x + HAUTEUR - 1, cases[i][j].y + LARGEUR - 1)) {
                    if (cases[i][j].occupe == 0) {
                        if (cases[i-1][j].occupe == 0 && cases[i+1][j].occupe == 0 && cases[i][j-1].occupe == 0 && cases[i][j+1].occupe == 0){
                            al_draw_bitmap(routeOE, cases[i][j].x, cases[i][j].y, 0);
                            cases[i][j].occupe = 10;
                        }


                        if ((cases[i - 1][j].occupe == 11 && cases[i + 1][j].occupe == 0) && (cases[i][j-1].occupe == 0 && cases[i][j+1].occupe == 0)) {
                            al_draw_bitmap(routeNS, cases[i][j].x, cases[i][j].y, 0);
                            cases[i][j].occupe = 11;
                        }
                        if ((cases[i - 1][j].occupe == 0 && cases[i + 1][j].occupe == 11) && (cases[i][j-1].occupe == 0 && cases[i][j+1].occupe == 0)) {
                            al_draw_bitmap(routeNS, cases[i][j].x, cases[i][j].y, 0);
                            cases[i][j].occupe = 11;
                        }
                        if ((cases[i - 1][j].occupe == 10 && cases[i + 1][j].occupe == 0) && (cases[i][j-1].occupe == 0 && cases[i][j+1].occupe == 0)) {
                            al_draw_bitmap(routeNS, cases[i][j].x, cases[i][j].y, 0);
                            al_draw_bitmap(routeNS, cases[i - 1][j].x, cases[i - 1][j].y, 0);
                            cases[i][j].occupe = 11;
                            cases[i - 1][j].occupe = 11;
                        }
                        if ((cases[i - 1][j].occupe == 0 && cases[i + 1][j].occupe == 10) && (cases[i][j-1].occupe == 0 && cases[i][j+1].occupe == 0)) {
                            al_draw_bitmap(routeNS, cases[i][j].x, cases[i][j].y, 0);
                            al_draw_bitmap(routeNS, cases[i + 1][j].x, cases[i + 1][j].y, 0);
                            cases[i][j].occupe = 11;
                            cases[i + 1][j].occupe = 11;
                        }
                        if ((cases[i - 1][j].occupe == 11 && cases[i + 1][j].occupe == 10) && (cases[i][j-1].occupe == 0 && cases[i][j+1].occupe == 0)) {
                            al_draw_bitmap(routeNS, cases[i][j].x, cases[i][j].y, 0);
                            al_draw_bitmap(routeNS, cases[i + 1][j].x, cases[i + 1][j].y, 0);
                            cases[i][j].occupe = 11;
                            cases[i + 1][j].occupe = 11;
                        }
                        if ((cases[i - 1][j].occupe == 10 && cases[i + 1][j].occupe == 10) && (cases[i][j-1].occupe == 0 && cases[i][j+1].occupe == 0)) {
                            al_draw_bitmap(routeNS, cases[i][j].x, cases[i][j].y, 0);
                            al_draw_bitmap(routeNS, cases[i-1][j].x, cases[i-1][j].y, 0);
                            al_draw_bitmap(routeNS, cases[i+1][j].x, cases[i+1][j].y, 0);
                            cases[i][j].occupe = 11;
                            cases[i-1][j].occupe = 11;
                            cases[i+1][j].occupe = 11;
                        }
                        if ((cases[i - 1][j].occupe == 10 && cases[i + 1][j].occupe == 11) && (cases[i][j-1].occupe == 0 && cases[i][j+1].occupe == 0) && cases[i+1][j-1].occupe == 0 && cases[i+1][j+1].occupe == 0 && cases[i+1][j].occupe == 0) {
                            al_draw_bitmap(routeNS, cases[i][j].x, cases[i][j].y, 0);
                            al_draw_bitmap(routeNS, cases[i-1][j].x, cases[i+1][j].y, 0);
                            cases[i][j].occupe = 11;
                            cases[i-1][j].occupe = 11;
                        }
                        if ((cases[i - 1][j].occupe == 0 && cases[i + 1][j].occupe == 0) && (cases[i][j-1].occupe == 10 && cases[i][j+1].occupe == 0)) {
                            al_draw_bitmap(routeOE, cases[i][j].x, cases[i][j].y, 0);
                            cases[i][j].occupe = 10;
                        }
                        if ((cases[i - 1][j].occupe == 0 && cases[i + 1][j].occupe == 0) && (cases[i][j-1].occupe == 10 && cases[i][j+1].occupe == 10)) {
                            al_draw_bitmap(routeOE, cases[i][j].x, cases[i][j].y, 0);
                            cases[i][j].occupe = 10;
                        }
                        if ((cases[i - 1][j].occupe == 0 && cases[i + 1][j].occupe == 0) && (cases[i][j-1].occupe == 0 && cases[i][j+1].occupe == 10)) {
                            al_draw_bitmap(routeOE, cases[i][j].x, cases[i][j].y, 0);
                            cases[i][j].occupe = 10;
                        }

                        if ((cases[i - 1][j].occupe == 10 && cases[i + 1][j].occupe == 0) && (cases[i][j-1].occupe == 10 && cases[i][j+1].occupe == 10)) {
                            al_draw_bitmap(routeTN, cases[i][j].x, cases[i][j].y, 0);
                            al_draw_bitmap(routeNS, cases[i-1][j].x, cases[i-1][j].y, 0);
                            cases[i][j].occupe = 16;
                            cases[i-1][j].occupe = 11;
                        }

                        if ((cases[i + 1][j].occupe == 10 && (cases[i + 1][j+1].occupe == 10 || cases[i+1][j-1].occupe == 10)) && (cases[i][j-1].occupe == 0 && cases[i][j+1].occupe == 0)) {
                            al_draw_bitmap(routeNS, cases[i][j].x, cases[i][j].y, 0);
                            al_draw_bitmap(routeTN, cases[i+1][j].x, cases[i+1][j].y, 0);
                            cases[i][j].occupe = 11;
                            cases[i+1][j].occupe = 16;
                        }





                        // route de côté placée si la route d'avant et d'après sur l'axe x est déjà placée
                        if ((cases[i][j - 1].occupe == 1 || cases[i][j + 1].occupe == 1) && cases[i - 1][j].occupe == 0 && cases[i + 1][j].occupe == 0) {
                            al_draw_bitmap(routeOE, cases[i][j].x, cases[i][j].y, 0);
                            // revoir code bitmap axe h et w
                            cases[i][j].occupe = 1;
                        }
                        // route droite (de haut) placée si la route d'avant et d'après sur l'axe y est déjà placée
                        if (cases[i][j - 1].occupe == 1 && cases[i][j + 1].occupe == 0 && cases[i - 1][j].occupe == 1 &&
                            cases[i + 1][j].occupe == 0) {
                            al_draw_bitmap(virageON, cases[i][j].x, cases[i][j].y, 0);
                            cases[i][j].occupe = 1;
                        }
                        // route virage vers le bas si sur axe x on a la case d'avant occupée et case d'après vide, idem pour axe y


                        if (cases[i][j - 1].occupe == 0 && cases[i + 1][j].occupe == 0 && cases[i - 1][j].occupe == 1 &&
                            cases[i][j + 1].occupe == 1) {
                            al_draw_bitmap(virageNE, cases[i][j].x, cases[i][j].y, 0);
                            // revoir code bitmap axe h et w
                            cases[i][j].occupe = 1;
                        }
                        // route virage vers le haut si sur axe x on a la case d'avant libre et case d'après occupée, inverse pour axe y
                        if (cases[i][j + 1].occupe == 1 && cases[i][j - 1].occupe == 0 && cases[i + 1][j].occupe == 1 &&
                            cases[i - 1][j].occupe == 0) {
                            al_draw_bitmap(virageSO, cases[i][j].x, cases[i][j].y, 0);
                            cases[i][j].occupe = 1;
                        }
                        if (cases[i][j+1].occupe == 0 && cases[i][j - 1].occupe == 1 && cases[i + 1][j].occupe == 1 &&
                            cases[i - 1][j].occupe == 0) {
                            al_draw_bitmap(virageSE, cases[i][j].x, cases[i][j].y, 0);
                            cases[i][j].occupe = 1;
                        }

                        if (cases[i][j - 1].occupe == 1 && cases[i][j + 1].occupe == 1 && cases[i + 1][j].occupe == 1 &&
                            cases[i - 1][j].occupe == 1) {
                            al_draw_bitmap(routeX, cases[i][j].x, cases[i][j].y, 0);
                            cases[i][j].occupe = 1;
                        }
                        // si toutes cases autour est occupée alors faire croisement 4
                        if (cases[i][j - 1].occupe == 1 && cases[i][j + 1].occupe == 0 && cases[i + 1][j].occupe == 1 &&
                            cases[i - 1][j].occupe == 1) {
                            al_draw_bitmap(routeTO, cases[i][j].x, cases[i][j].y, 0);
                            cases[i][j].occupe = 1;
                        }
                        // croisements vers le bas si route à droite à gauche et en bas occupées
                        if (cases[i][j - 1].occupe == 1 && cases[i][j + 1].occupe == 1 && cases[i + 1][j].occupe == 0 &&
                            cases[i - 1][j].occupe == 1) {
                            al_draw_bitmap(routeTN, cases[i][j].x, cases[i][j].y, 0);
                            cases[i][j].occupe = 1;
                        }
                        if (cases[i][j - 1].occupe == 0 && cases[i][j + 1].occupe == 1 && cases[i + 1][j].occupe == 1 &&
                            cases[i - 1][j].occupe == 1) {
                            al_draw_bitmap(routeTE, cases[i][j].x, cases[i][j].y, 0);
                            cases[i][j].occupe = 1;
                        }
                        if (cases[i][j - 1].occupe == 1 && cases[i][j + 1].occupe == 1 && cases[i + 1][j].occupe == 1 &&
                            cases[i - 1][j].occupe == 0) {
                            al_draw_bitmap(routeTS, cases[i][j].x, cases[i][j].y, 0);
                            cases[i][j].occupe = 1;
                        }
                    }
                    // première route placée (route droite, après ça change en fonction des cases occupées)
                    // route de côté placée si la route d'avant ou d'après sur l'axe x est déjà placée

                    // croisements vers le haut si route à droite à gauche et en haut occupées                 }
                }
            }
            if (isInRect(event.mouse.x, event.mouse.y, 53, 133, 197, 267)) {
                afficherRessources(*info, text, eau, argent, habitant, elec);
                afficherToolBox(text, textBold, setting, cabane,
                                watercastle, usine, route, caserne);
                *dessin = -1;
            }
        }
    }
}


