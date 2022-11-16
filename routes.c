#include "routes.h"

void dessinerRoutes(Case cases[NB_LIGNES_MAX][NB_COLONNES_MAX], ALLEGRO_FONT *text, ALLEGRO_FONT *textBold,
                    ALLEGRO_BITMAP *setting, ALLEGRO_BITMAP *cabane, ALLEGRO_BITMAP *watercastle, ALLEGRO_BITMAP *usine,
                    ALLEGRO_BITMAP *route, ALLEGRO_BITMAP *caserne) {
    assert (al_init());
    assert(al_init_primitives_addon());
    assert(al_install_mouse());
    ALLEGRO_EVENT_QUEUE *queue = NULL;
    ALLEGRO_EVENT event;
    ALLEGRO_MOUSE_STATE mouseState;
    queue = al_create_event_queue();
    al_register_event_source(queue, al_get_mouse_event_source());
    printf("a");
    bool fin = false;
    int preCaseX = -100;
    int preCaseY = -100;
    int caseXActu = -100;
    int caseYActu = -100;
    al_draw_filled_circle(120, 200, 90, GRIS_TRANSPARENT);
    while (!fin) {
        al_get_mouse_state(&mouseState);
        al_wait_for_event(queue, &event);
        switch (event.type) {
            case ALLEGRO_EVENT_MOUSE_AXES : {
                for (int i = 0; i < NB_LIGNES_MAX; ++i) {
                    for (int j = 0; j < NB_COLONNES_MAX; ++j) {
                        if (isInRect(event.mouse.x, event.mouse.y, cases[i][j].x, cases[i][j].y,
                                     cases[i][j].x + HAUTEUR, cases[i][j].y + LARGEUR)) {
                            caseXActu = cases[i][j].x;
                            caseYActu = cases[i][j].y;
                            if (cases[i][j].occupe == 0) {
                                al_draw_filled_rectangle(caseXActu, caseYActu,
                                                         caseXActu + HAUTEUR,
                                                         caseYActu + LARGEUR, NOIR);
                                if (mouseState.buttons & 1){
                                    al_draw_filled_rectangle(caseXActu, caseYActu,
                                                             caseXActu + HAUTEUR,
                                                             caseYActu + LARGEUR, NOIR);
                                }
                                else if (preCaseX != cases[i][j].x || preCaseY != cases[i][j].y) {
                                    al_draw_filled_rectangle(preCaseX, preCaseY,
                                                             preCaseX + HAUTEUR - 1,
                                                             preCaseY + LARGEUR - 1, BLANC);
                                    preCaseX = cases[i][j].x;
                                    preCaseY = cases[i][j].y;
                                }
                            }
                        }
                    }
                }
                if (isInRect(event.mouse.x, event.mouse.y, 625, 145, 1750, 1020) == false) {
                    al_draw_filled_rectangle(preCaseX, preCaseY, preCaseX + HAUTEUR - 1,
                                             preCaseY + LARGEUR - 1, BLANC);
                }
                break;
            }
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP : {
                if (isInRect(event.mouse.x, event.mouse.y, 53, 133, 197, 267)) {
                    afficherToolBox(text, textBold, setting, cabane,
                                    watercastle, usine, route, caserne);
                    fin = true;
                }
                break;
            }
        }
        al_flip_display();
    }
}


/*if (isInRect(event.mouse.x, event.mouse.y, 56, 746, 400, 820)) {
                        plateau(fplateau);
                        dessinerCases(cases);
                        afficherToolBox(text, textBold, eau, argent, habitant, elec, setting, cabane, watercastle,
                                        usine, route,
                                        caserne, info);
                    }
                    if (isInRect(event.mouse.x, event.mouse.y, 56, 846, 400, 920)) {
                        al_clear_to_color(GRIS_CLAIR);
                        dessinerCases(cases);
                        afficherToolBox(text, textBold, eau, argent, habitant, elec, setting, cabane, watercastle,
                                        usine, route,
                                        caserne, info);
                    }
                    if (isInRect(event.mouse.x, event.mouse.y, 56, 946, 400, 1020)) {
                        al_clear_to_color(GRIS_FONCE);
                        dessinerCases(cases);
                        afficherToolBox(text, textBold, eau, argent, habitant, elec, setting, cabane, watercastle,
                                        usine, route,
                                        caserne, info);
                    }*/