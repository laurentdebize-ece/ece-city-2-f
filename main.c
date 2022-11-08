#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include<allegro5/allegro_primitives.h>
#include<allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include <stdlib.h>
#include <time.h>
#include <allegro5\allegro_acodec.h>
#include <allegro5\allegro_audio.h>

#define NB_LIGNES_MAX 35
#define NB_COLONNES_MAX 45
#define HAUTEUR 20
#define LARGEUR 20
#define HAUTEUR_PLATEAU 950
#define LARGEUR_PLATEAU 1024


typedef struct {
    int x, y, largeur, hauteur;
    ALLEGRO_COLOR couleur;
} Case;

void initCases(Case cases[NB_LIGNES_MAX][NB_COLONNES_MAX]) {
    int i, j;
    for (i = 0; i < NB_LIGNES_MAX; i++) {
        for (j = 0; j < NB_COLONNES_MAX; j++) {
            cases[i][j].largeur = 20;
            cases[i][j].hauteur = 20;
            cases[i][j].x = 20 + j * cases[i][j].largeur;
            cases[i][j].y = 20 + i * cases[i][j].hauteur;
            cases[i][j].couleur = al_map_rgb(255, 255, 255);
        }
    }
}

void dessinerCases(Case cases[NB_LIGNES_MAX][NB_COLONNES_MAX]) {
    int i, j;
    for (i = 0; i < NB_LIGNES_MAX; i++) {
        for (j = 0; j < NB_COLONNES_MAX; j++) {
            al_draw_rectangle(cases[i][j].x, cases[i][j].y, cases[i][j].x + cases[i][j].largeur,
                              cases[i][j].y + cases[i][j].hauteur, cases[i][j].couleur, 1);
        }
    }
}

bool isInRect(int x, int y, int x1, int y1, int x2, int y2) {
    return (x >= x1 && x <= x2 && y >= y1 && y <= y2);
}

void menud(ALLEGRO_BITMAP *fond) {
    fond = al_load_bitmap("../VF Fond - Copie.png");
    al_draw_bitmap(fond, 0, 0, 0);
    al_flip_display();
}

int main() {
    assert (al_init());
    assert(al_init_primitives_addon());
    assert(al_init_image_addon());
    assert(al_install_mouse());
    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_EVENT event;
    ALLEGRO_BITMAP *fond = NULL;
    queue = al_create_event_queue();
    assert(queue != NULL);
    int mode;
    timer = al_create_timer(1.0 / 60.0);
    assert(timer != NULL);
    bool fin = false;
    bool menu = false;
    bool jeu = false;
    display = al_create_display(LARGEUR_PLATEAU, HAUTEUR_PLATEAU);
    assert(display != NULL);
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());
    al_set_window_title(display, "ECE City");
    al_set_window_position(display, 10, 10);
    Case cases[NB_LIGNES_MAX][NB_COLONNES_MAX];
    menud(fond);
    while (!fin) {
        al_wait_for_event(queue, &event);
        while (!menu) {
            al_wait_for_event(queue, &event);
            switch (event.type) {
                case ALLEGRO_EVENT_DISPLAY_CLOSE: {
                    fin = true;
                    break;
                }
                case ALLEGRO_EVENT_DISPLAY_RESIZE: {
                    al_flip_display();
                    break;
                }
                case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN : {
                    if (isInRect(event.mouse.x, event.mouse.y, 97, 687, 435, 791)) {
                        menu = true;
                        mode = 0;
                    }

                    if (isInRect(event.mouse.x, event.mouse.y, 597, 679, 931, 800)) {
                        menu = true;
                        mode = 1;
                    }
                    break;
                }
            }
        }
        while (!jeu) {
            al_wait_for_event(queue, &event);
            al_clear_to_color(al_map_rgb(0,0,0));
            initCases(cases);
            dessinerCases(cases);
            al_flip_display();
            switch (event.type) {
                case ALLEGRO_EVENT_DISPLAY_CLOSE: {
                    jeu = true;
                    break;
                }
                case ALLEGRO_EVENT_DISPLAY_RESIZE: {
                    al_flip_display();
                    break;
                }
            }
        }
        al_destroy_display(display);
        al_destroy_event_queue(queue);
        al_destroy_timer(timer);
    }
}
