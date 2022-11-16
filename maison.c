#include "maison.h"

void dessinerMaisons(Case cases[NB_LIGNES_MAX][NB_COLONNES_MAX], ALLEGRO_FONT *text, ALLEGRO_FONT *textBold,
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
    al_draw_filled_circle(330, 200, 90, GRIS_TRANSPARENT);
    while (!fin) {
        al_get_mouse_state(&mouseState);
        al_wait_for_event(queue, &event);
        switch (event.type) {
            case ALLEGRO_EVENT_MOUSE_AXES : {
                for (int i = 0; i < NB_LIGNES_MAX; ++i) {
                    for (int j = 0; j < NB_COLONNES_MAX; ++j) {
                        if (isInRect(event.mouse.x, event.mouse.y, cases[i][j].x, cases[i][j].y,
                                     cases[i][j].x + HAUTEUR, cases[i][j].y + LARGEUR)) {
                            if (cases[i][j].occupe == 0 && mouseState.buttons & 1) {
                                al_draw_scaled_bitmap(cabane, 0, 0, al_get_bitmap_width(cabane),
                                                      al_get_bitmap_height(cabane),
                                                      cases[i][j].x - LARGEUR,
                                                      cases[i][j].y - 2 * HAUTEUR, 75, 75, 0);
                            }
                        }
                    }
                }
                break;
            }
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP : {
                if (isInRect(event.mouse.x, event.mouse.y, 263, 133, 397, 267)) {
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