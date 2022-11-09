#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdlib.h>
#include <allegro5/allegro_native_dialog.h>
#include <time.h>
#include <allegro5\allegro_acodec.h>
#include <allegro5\allegro_audio.h>

#define NB_LIGNES_MAX 35
#define NB_COLONNES_MAX 45
#define HAUTEUR 20
#define LARGEUR 20
#define HAUTEUR_PLATEAU 1080
#define LARGEUR_PLATEAU 1920


typedef struct {
    int x, y, largeur, hauteur;
    ALLEGRO_COLOR couleur;
} Case;

typedef struct{
    int argent;
    int elec;
    int eau;
    int nbhabitant;
}Info;

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

void afficherDate(){
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_FONT *text2;
    ALLEGRO_EVENT_QUEUE *queue;
    ALLEGRO_EVENT event;
    assert(al_init());
    assert(al_install_keyboard());
    al_init_font_addon();
    assert(al_init_ttf_addon());
    assert(al_init_image_addon());
    queue = al_create_event_queue();
    bool temps = false;
    int l = 0;
    int k = 0;
    int y = 2022;
    timer = al_create_timer(1.0 / 10.0);
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_timer_event_source(timer));
    while (!temps) {
        al_wait_for_event(queue, &event);
        switch (event.type) {
            case ALLEGRO_EVENT_TIMER: {
                l = l +1;
                if(l == 150){
                    l = 0;
                    k = k + 1;
                    if(k == 11){
                        k = 0;
                    }
                }





            }
        }

    }
}

void afficherToolBox(ALLEGRO_FONT* text, ALLEGRO_BITMAP* water, ALLEGRO_BITMAP* argent, ALLEGRO_BITMAP * habitant, ALLEGRO_BITMAP* elec, Info info){
    al_draw_scaled_bitmap(argent, 0, 0, al_get_bitmap_width(argent), al_get_bitmap_height(argent), 1000, 30, 40, 40, 0);
    al_draw_scaled_bitmap(elec, 0, 0, al_get_bitmap_width(elec), al_get_bitmap_height(elec), 800, 30, 40, 40, 0);
    al_draw_scaled_bitmap(habitant, 0, 0, al_get_bitmap_width(habitant), al_get_bitmap_height(habitant), 600, 30, 40, 40, 0);
    al_draw_scaled_bitmap(water, 0, 0, al_get_bitmap_width(water), al_get_bitmap_height(water), 400, 30, 40, 40, 0);

    al_draw_textf(text, al_map_rgb(255,255,255), 800, 40, 0,": %d",info.argent);
}


void dessinerCases(Case cases[NB_LIGNES_MAX][NB_COLONNES_MAX]) {
    int i, j;
    for (i = 0; i < NB_LIGNES_MAX; i++) {
        for (j = 0; j < NB_COLONNES_MAX; j++) {
            al_draw_rectangle(cases[i][j].x+100, cases[i][j].y +150, cases[i][j].x + cases[i][j].largeur+100,
                              cases[i][j].y+150 + cases[i][j].hauteur, cases[i][j].couleur, 1);
        }
    }
    al_flip_display();
}

bool isInRect(int x, int y, int x1, int y1, int x2, int y2) {
    return (x >= x1 && x <= x2 && y >= y1 && y <= y2);
}

void menud(ALLEGRO_BITMAP *fond) {
    fond = al_load_bitmap("../VF_Fond.png");
    al_draw_bitmap(fond, 0, 0, 0);
    al_flip_display();
}

void plateau(ALLEGRO_BITMAP *fplateau){
    fplateau = al_load_bitmap("../fond_jeu.jpg");
    al_draw_bitmap(fplateau,0,0,0);
    al_draw_filled_rectangle(0, 0, LARGEUR_PLATEAU, 90, al_map_rgb(50, 50, 50));
    al_flip_display();
}

int main() {
    assert (al_init());
    assert(al_init_primitives_addon());
    assert(al_init_image_addon());
    assert(al_install_mouse());
    al_init_font_addon();
    al_init_ttf_addon();
    assert(al_init_ttf_addon());
    if(!al_init_ttf_addon())
        printf("al_init_ttf_addon()");
    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_EVENT event;
    ALLEGRO_BITMAP *fond, *argent, *elec, *habitant, *eau = NULL;
    ALLEGRO_BITMAP *fplateau = NULL;
    ALLEGRO_FONT *text;
    argent = al_load_bitmap("../argent.png");
    if(!argent){printf("erreur load argent");}
    elec = al_load_bitmap("../Electricite.png");
    habitant = al_load_bitmap("../people.png");
    eau = al_load_bitmap("../water.png");
    text = al_load_ttf_font("../calibri.ttf", 30, 0);
    if(!text){
        printf("erreur");
    }
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
    al_set_window_position(display, 0, 0);
    Case cases[NB_LIGNES_MAX][NB_COLONNES_MAX];
    Info info;
    info.argent = 500000;
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
                case ALLEGRO_EVENT_MOUSE_BUTTON_UP : {
                    if (isInRect(event.mouse.x, event.mouse.y, 207, 809, 800, 960)) {
                        menu = true;
                        mode = 0;
                    }

                    if (isInRect(event.mouse.x, event.mouse.y, 1111, 809, 1705, 960)) {
                        menu = true;
                        mode = 1;
                    }
                    break;
                }
            }
        }
        plateau(fplateau);
        initCases(cases);
        dessinerCases(cases);
        afficherToolBox(text, eau, argent, habitant, elec, info);
        while (!jeu) {
            al_wait_for_event(queue, &event);
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