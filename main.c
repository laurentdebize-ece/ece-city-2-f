#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdlib.h>

#define NB_LIGNES_MAX 35
#define NB_COLONNES_MAX 45
#define HAUTEUR 25
#define LARGEUR 25
#define HAUTEUR_PLATEAU 1080
#define LARGEUR_PLATEAU 1920
#define GRIS_FONCE al_map_rgb(25, 25, 25)
#define GRIS_CLAIR al_map_rgb(50, 50, 50)
#define BLANC al_map_rgb(255, 255, 255)
#define NOIR al_map_rgb(0,0,0)
#define VERT al_map_rgb(50,175,0)
#define BLEU al_map_rgb(0,75,255)
#define JAUNE al_map_rgb(228,234,0)
#define GRIS_TRANSPARENT al_map_rgba(50, 50, 50, 50)


typedef struct {
    int x, y, largeur, hauteur;
    ALLEGRO_COLOR couleur;
} Case;

typedef struct {
    int argent;
    int elec;
    int eau;
    int nbhabitant;
} Info;

void initCases(Case cases[NB_LIGNES_MAX][NB_COLONNES_MAX]) {
    int i, j;
    for (i = 0; i < NB_LIGNES_MAX; i++) {
        for (j = 0; j < NB_COLONNES_MAX; j++) {
            cases[i][j].largeur = 25;
            cases[i][j].hauteur = 25;
            cases[i][j].x = 25 + j * cases[i][j].largeur;
            cases[i][j].y = 25 + i * cases[i][j].hauteur;
            cases[i][j].couleur = NOIR;
        }
    }
}

void afficherDate() {
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
                l = l + 1;
                if (l == 150) {
                    l = 0;
                    k = k + 1;
                    if (k == 11) {
                        k = 0;
                    }
                }
            }
        }

    }
}

void afficherToolBox(ALLEGRO_FONT *text, ALLEGRO_FONT *textBold, ALLEGRO_BITMAP *water, ALLEGRO_BITMAP *argent,
                     ALLEGRO_BITMAP *habitant, ALLEGRO_BITMAP *elec,
                     ALLEGRO_BITMAP *setting, ALLEGRO_BITMAP *cabane, ALLEGRO_BITMAP *watercastle,
                     ALLEGRO_BITMAP *usine,
                     ALLEGRO_BITMAP *route, ALLEGRO_BITMAP *caserne, Info info) {
    al_draw_filled_rectangle(0, 0, LARGEUR_PLATEAU, 90, GRIS_FONCE);
    al_draw_filled_rectangle(600, 10, 1706, 86, GRIS_CLAIR);
    al_draw_filled_rectangle(603, 13, 1703, 83, BLANC);
    al_draw_filled_rectangle(606, 16, 1700, 80, GRIS_CLAIR);

    al_draw_filled_rectangle(0, 0, 450, HAUTEUR_PLATEAU, GRIS_FONCE);

    al_draw_scaled_bitmap(argent, 0, 0, al_get_bitmap_width(argent), al_get_bitmap_height(argent), 1450, 17, 60, 60, 0);
    al_draw_scaled_bitmap(elec, 0, 0, al_get_bitmap_width(elec), al_get_bitmap_height(elec), 1200, 17, 60, 60, 0);
    al_draw_scaled_bitmap(water, 0, 0, al_get_bitmap_width(water), al_get_bitmap_height(water), 950, 17, 60, 60, 0);
    al_draw_scaled_bitmap(habitant, 0, 0, al_get_bitmap_width(habitant), al_get_bitmap_height(habitant), 700, 17, 60,
                          60, 0);

    al_draw_textf(text, BLANC, 1520, 35, 0, ": %d", info.argent);
    al_draw_textf(text, BLANC, 1270, 35, 0, ": %d", info.elec);
    al_draw_textf(text, BLANC, 1020, 35, 0, ": %d", info.eau);
    al_draw_textf(text, BLANC, 770, 35, 0, ": %d", info.nbhabitant);

    al_draw_filled_circle(40, 40, 34, GRIS_CLAIR);
    al_draw_filled_circle(40, 40, 32, BLANC);
    al_draw_filled_circle(40, 40, 30, GRIS_CLAIR);
    al_draw_scaled_bitmap(setting, 0, 0, al_get_bitmap_width(setting), al_get_bitmap_height(setting), 15, 15, 50, 50,
                          0);

    al_draw_filled_circle(120, 200, 90, GRIS_CLAIR);
    al_draw_filled_circle(120, 200, 88, BLANC);
    al_draw_filled_circle(120, 200, 86, GRIS_CLAIR);

    al_draw_filled_circle(330, 200, 90, GRIS_CLAIR);
    al_draw_filled_circle(330, 200, 88, BLANC);
    al_draw_filled_circle(330, 200, 86, GRIS_CLAIR);

    al_draw_filled_circle(120, 400, 90, GRIS_CLAIR);
    al_draw_filled_circle(120, 400, 88, BLANC);
    al_draw_filled_circle(120, 400, 86, GRIS_CLAIR);

    al_draw_filled_circle(330, 400, 90, GRIS_CLAIR);
    al_draw_filled_circle(330, 400, 88, BLANC);
    al_draw_filled_circle(330, 400, 86, GRIS_CLAIR);

    al_draw_filled_circle(225, 600, 90, GRIS_CLAIR);
    al_draw_filled_circle(225, 600, 88, BLANC);
    al_draw_filled_circle(225, 600, 86, GRIS_CLAIR);


    al_draw_scaled_bitmap(route, 0, 0, al_get_bitmap_width(route), al_get_bitmap_height(route), 50, 125, 125, 125, 0);
    al_draw_scaled_bitmap(cabane, 0, 0, al_get_bitmap_width(cabane), al_get_bitmap_height(cabane), 240, 115, 160, 160,
                          0);
    al_draw_scaled_bitmap(watercastle, 0, 0, al_get_bitmap_width(watercastle), al_get_bitmap_height(watercastle), 25,
                          290, 200, 200, 0);
    al_draw_scaled_bitmap(usine, 0, 0, al_get_bitmap_width(usine), al_get_bitmap_height(usine), 260, 320, 135, 135, 0);
    al_draw_scaled_bitmap(caserne, 0, 0, al_get_bitmap_width(caserne), al_get_bitmap_height(caserne), 160, 520, 135,
                          135, 0);


    al_draw_filled_rounded_rectangle(50, 740, 400, 820, 10, 10, VERT);
    al_draw_filled_rounded_rectangle(53, 743, 397, 817, 10, 10, NOIR);
    al_draw_filled_rounded_rectangle(56, 746, 394, 814, 10, 10, VERT);
    al_draw_text(textBold, NOIR, 135, 757, 0, "Niveau 0");

    al_draw_filled_rounded_rectangle(50, 840, 400, 920, 10, 10, BLEU);
    al_draw_filled_rounded_rectangle(53, 843, 397, 917, 10, 10, NOIR);
    al_draw_filled_rounded_rectangle(56, 846, 394, 914, 10, 10, BLEU);
    al_draw_text(textBold, NOIR, 135, 857, 0, "Niveau -1");

    al_draw_filled_rounded_rectangle(50, 940, 400, 1020, 10, 10, JAUNE);
    al_draw_filled_rounded_rectangle(53, 943, 397, 1017, 10, 10, NOIR);
    al_draw_filled_rounded_rectangle(56, 946, 394, 1014, 10, 10, JAUNE);
    al_draw_text(textBold, NOIR, 135, 957, 0, "Niveau -2");
}

void raffraichir() {

}


bool isInRect(int x, int y, int x1, int y1, int x2, int y2) {
    return (x >= x1 && x <= x2 && y >= y1 && y <= y2);
}

/*void dessinerRoutes(Case cases[NB_LIGNES_MAX][NB_COLONNES_MAX]) {
    assert (al_init());
    assert(al_install_mouse());
    assert(al_init_primitives_addon());
    ALLEGRO_EVENT_QUEUE *queue = NULL;
    ALLEGRO_EVENT event;
    bool fin = false;
    queue = al_create_event_queue();
    assert(queue != NULL);
    al_register_event_source(queue, al_get_mouse_event_source());
    al_draw_filled_circle(120, 200, 90, GRIS_TRANSPARENT);
    while (!fin) {
        al_wait_for_event(queue, &event);
        switch (event.type) {
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP : {
                for (int i = 0; i < NB_LIGNES_MAX; ++i) {
                    for (int j = 0; j < NB_COLONNES_MAX; ++j) {
                        if (isInRect(event.mouse.x, event.mouse.y, cases[i][j].x, cases[i][j].y,
                                     cases[i][j].x + HAUTEUR, cases[i][j].y + LARGEUR)) {
                            al_draw_filled_rectangle(cases[i][j].x, cases[i][j].y, cases[i][j].x + HAUTEUR,
                                                     cases[i][j].y + LARGEUR, NOIR);
                        }
                        if (isInRect(event.mouse.x, event.mouse.y, 53, 133, 197, 267)){
                            fin = true;
                        }
                    }
                }
            } break;
        }
    }
}*/

void dessinerCases(Case cases[NB_LIGNES_MAX][NB_COLONNES_MAX]) {
    int i, j;
    for (i = 0; i < NB_LIGNES_MAX; i++) {
        for (j = 0; j < NB_COLONNES_MAX; j++) {
            al_draw_rectangle(cases[i][j].x + 600, cases[i][j].y + 120, cases[i][j].x + cases[i][j].largeur + 600,
                              cases[i][j].y + 120 + cases[i][j].hauteur, cases[i][j].couleur, 1);
        }
    }
    al_flip_display();
}


void menud(ALLEGRO_BITMAP *fond) {
    al_draw_bitmap(fond, 0, 0, 0);
    al_flip_display();
}

void plateau(ALLEGRO_BITMAP *fplateau) {
    al_draw_bitmap(fplateau, 0, 0, 0);
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
    if (!al_init_ttf_addon())
        printf("al_init_ttf_addon()");

    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_EVENT event;
    ALLEGRO_BITMAP *argent, *elec, *habitant, *eau, *setting, *cabane, *watercastle, *usine, *route, *caserne = NULL;
    ALLEGRO_BITMAP *fond, *fplateau = NULL;
    ALLEGRO_FONT *text, *textBold;

    argent = al_load_bitmap("../Images/argent.png");
    elec = al_load_bitmap("../Images/Electricite.png");
    habitant = al_load_bitmap("../Images/people.png");
    eau = al_load_bitmap("../Images/water.png");
    setting = al_load_bitmap("../Images/settings.png");
    fplateau = al_load_bitmap("../Images/fond_jeu.jpg");
    fond = al_load_bitmap("../Images/VF_Fond.png");
    cabane = al_load_bitmap("../Images/cabana.png");
    watercastle = al_load_bitmap("../Images/watercastle.png");
    usine = al_load_bitmap("../Images/usine.png");
    route = al_load_bitmap("../Images/route.png");
    caserne = al_load_bitmap("../Images/caserne.png");

    text = al_load_ttf_font("../Fonts/calibri.ttf", 30, 0);
    if (!text) {
        printf("erreur");
    }
    textBold = al_load_ttf_font("../Fonts/calibrib.ttf", 50, 0);

    queue = al_create_event_queue();
    assert(queue != NULL);
    timer = al_create_timer(1.0 / 60.0);
    al_start_timer(timer);
    assert(timer != NULL);
    display = al_create_display(LARGEUR_PLATEAU, HAUTEUR_PLATEAU);
    assert(display != NULL);

    int mode;
    bool fin = false;
    bool menu = false;
    bool jeu = false;
    int l = 0;
    int k = 1;
    int y = 2022;
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
        al_clear_to_color(BLANC);
        plateau(fplateau);
        initCases(cases);
        dessinerCases(cases);
        afficherToolBox(text, textBold, eau, argent, habitant, elec, setting, cabane, watercastle, usine, route,
                        caserne, info);
        while (!jeu) {
            al_wait_for_event(queue, &event);
            al_flip_display();
            switch (event.type) {
                case ALLEGRO_EVENT_DISPLAY_CLOSE: {
                    jeu = true;
                    break;
                }
                case ALLEGRO_EVENT_MOUSE_BUTTON_UP: {
                    if (isInRect(event.mouse.x, event.mouse.y, 53, 133, 197, 267)) {
                        al_draw_filled_circle(120, 200, 90, GRIS_TRANSPARENT);
                    }
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