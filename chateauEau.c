#include "chateauEau.h"


void dessinerChateauEau(Case cases[NB_LIGNES_MAX][NB_COLONNES_MAX], ALLEGRO_FONT *text, ALLEGRO_FONT *textBold,
                        ALLEGRO_BITMAP *setting, ALLEGRO_BITMAP *cabane, ALLEGRO_BITMAP *watercastle, ALLEGRO_BITMAP *usine,
                        ALLEGRO_BITMAP *route, ALLEGRO_BITMAP *caserne){
    assert (al_init());
    assert(al_init_primitives_addon());
    assert(al_install_mouse());
    ALLEGRO_EVENT_QUEUE *queue = NULL;
    ALLEGRO_EVENT event;
    queue = al_create_event_queue();
    al_register_event_source(queue, al_get_mouse_event_source());
    bool fin = false;
    al_draw_filled_circle(120, 400, 90, GRIS_TRANSPARENT);
    while (!fin) {
        al_wait_for_event(queue, &event);
        switch (event.type) {
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP : {
                for (int i = 0; i < NB_LIGNES_MAX; ++i) {
                    for (int j = 0; j < NB_COLONNES_MAX; ++j) {
                        if (isInRect(event.mouse.x, event.mouse.y, cases[i][j].x, cases[i][j].y,
                                     cases[i][j].x + HAUTEUR, cases[i][j].y + LARGEUR)) {
                            if (cases[i][j].occupe == 0){
                                al_draw_scaled_bitmap(watercastle, 0, 0, al_get_bitmap_width(watercastle),
                                                      al_get_bitmap_height(watercastle),
                                                      cases[i][j].x - 2 * LARGEUR,
                                                      cases[i][j].y - 6 * HAUTEUR, 100, 150, 0);
                                cases[i-6][j-2].occupe = 1;
                                cases[i-6][j-1].occupe = 1;
                                cases[i-6][j].occupe = 1;
                                cases[i-6][j+1].occupe = 1;

                                cases[i-5][j-2].occupe = 1;
                                cases[i-5][j-1].occupe = 1;
                                cases[i-5][j].occupe = 1;
                                cases[i-5][j+1].occupe = 1;

                                cases[i-4][j-2].occupe = 1;
                                cases[i-4][j-1].occupe = 1;
                                cases[i-4][j].occupe = 1;
                                cases[i-4][j+1].occupe = 1;

                                cases[i-3][j-2].occupe = 1;
                                cases[i-3][j-1].occupe = 1;
                                cases[i-3][j].occupe = 1;
                                cases[i-3][j+1].occupe = 1;

                                cases[i-2][j-2].occupe = 1;
                                cases[i-2][j-1].occupe = 1;
                                cases[i-2][j].occupe = 1;
                                cases[i-2][j+1].occupe = 1;

                                cases[i-1][j-2].occupe = 1;
                                cases[i-1][j-1].occupe = 1;
                                cases[i-1][j].occupe = 1;
                                cases[i-1][j+1].occupe = 1;
                            }
                        }
                    }
                }
                if (isInRect(event.mouse.x, event.mouse.y, 53, 333, 187, 467)) {
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