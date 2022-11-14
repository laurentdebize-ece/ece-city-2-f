#include "routes.h"

int routeRecursif(Case cases[NB_LIGNES_MAX][NB_COLONNES_MAX], int x, int y) {
    assert (al_init());
    assert(al_init_primitives_addon());
    assert(al_install_mouse());
    ALLEGRO_EVENT_QUEUE *queue = NULL;
    ALLEGRO_EVENT event;
    queue = al_create_event_queue();
    al_register_event_source(queue, al_get_mouse_event_source());

    bool fin = false;
    int diffX, diffY = 0;
    int newX, newY = -100;
    while (!fin) {
        al_wait_for_event(queue, &event);
        switch (event.type) {
            case ALLEGRO_EVENT_MOUSE_AXES : {
                diffX = x - event.mouse.x;
                diffY = y - event.mouse.y;
                if (diffX >= 0) {
                    al_draw_filled_rectangle(x + LARGEUR, y, x + 2 * LARGEUR, y + HAUTEUR, NOIR);
                    newX = x + LARGEUR;
                    newY = y;
                }
                break;
            }
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP : {
                fin = true;
            }
        }
        al_flip_display();
    }
    return routeRecursif(cases, newX, newY);
}