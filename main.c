#include "menu.h"
#include "routes.h"



bool isInRect(int x, int y, int x1, int y1, int x2, int y2) {
    return (x >= x1 && x <= x2 && y >= y1 && y <= y2);
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


    //routes
    ALLEGRO_BITMAP *routes, *routeDroite, *routeCote, *virageHaut, *virageBas, *croisementTBas, *croisementQuatres;
    routes = al_load_bitmap("../Images/routes.png");
    routeDroite = al_create_sub_bitmap(routes, 118,209,219,320);
    routeCote = al_create_sub_bitmap(routes, 421, 65,325,217);
    virageHaut = al_create_sub_bitmap(routes,69,664,274,329);
    virageBas = al_create_sub_bitmap(routes, 804,729,273,319);
    croisementTBas = al_create_sub_bitmap(routes,421,890,322,322);
    croisementQuatres = al_create_sub_bitmap(routes, 416,344,328,414);

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
    bool finRoute = false;
    bool test = false;
    bool finCabane = false;

    int l = 0;
    int k = 1;
    int y = 2022;
    int preCaseXRoute = -100;
    int preCaseYRoute = -100;
    int caseXActuRoute = -100;
    int caseYActuRoute = -100;

    int preCaseXCabane = -100;
    int preCaseYCabane = -100;
    int caseXActuCabane = -100;
    int caseYActuCabane = -100;

    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());

    al_set_window_title(display, "ECE City");
    al_set_window_position(display, -3, 0);

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
                    menu = true;
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
        //plateau(fplateau);
        initCases(cases);
        dessinerCases(cases);
        afficherRessources(info, text, eau, argent, habitant, elec);
        afficherToolBox(text, textBold, setting, cabane, watercastle, usine, route, caserne);
        al_flip_display();
        while (!jeu) {
            al_wait_for_event(queue, &event);
            switch (event.type) {
                case ALLEGRO_EVENT_MOUSE_BUTTON_UP: {
                    if (isInRect(event.mouse.x, event.mouse.y, 53, 133, 187, 267)) {
                        al_draw_filled_circle(120, 200, 90, GRIS_TRANSPARENT);
                        while (!finRoute) {
                            al_wait_for_event(queue, &event);
                            switch (event.type) {
                                case ALLEGRO_EVENT_MOUSE_AXES : {
                                    for (int i = 0; i < NB_LIGNES_MAX; ++i) {
                                        for (int j = 0; j < NB_COLONNES_MAX; ++j) {
                                            if (isInRect(event.mouse.x, event.mouse.y, cases[i][j].x, cases[i][j].y,
                                                         cases[i][j].x + HAUTEUR, cases[i][j].y + LARGEUR)) {
                                                caseXActuRoute = cases[i][j].x;
                                                caseYActuRoute = cases[i][j].y;
                                                if (cases[i][j].occupe == 0) {
                                                    al_draw_filled_rectangle(caseXActuRoute, caseYActuRoute,
                                                                             caseXActuRoute + HAUTEUR,
                                                                             caseYActuRoute + LARGEUR, NOIR);
                                                    test = true;
                                                    if (preCaseXRoute != cases[i][j].x ||
                                                        preCaseYRoute != cases[i][j].y) {
                                                        al_draw_filled_rectangle(preCaseXRoute, preCaseYRoute,
                                                                                 preCaseXRoute + HAUTEUR - 1,
                                                                                 preCaseYRoute + LARGEUR - 1, BLANC);
                                                        preCaseXRoute = cases[i][j].x;
                                                        preCaseYRoute = cases[i][j].y;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    if (isInRect(event.mouse.x, event.mouse.y, 625, 145, 1750, 1020) == false) {
                                        al_draw_filled_rectangle(preCaseXRoute, preCaseYRoute,
                                                                 preCaseXRoute + HAUTEUR - 1,
                                                                 preCaseYRoute + LARGEUR - 1, BLANC);
                                    }
                                    break;
                                }
                                case ALLEGRO_EVENT_MOUSE_BUTTON_UP: {
                                    if (isInRect(event.mouse.x, event.mouse.y, 53, 133, 197, 267)) {
                                        afficherToolBox(text, textBold, setting, cabane,
                                                        watercastle, usine, route, caserne);
                                        finRoute = true;
                                    }
                                    if (test == true && isInRect(event.mouse.x, event.mouse.y, 625, 145, 1750, 1020)) {
                                        //routeRecursif(cases, caseXActuRoute, caseYActuRoute);
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

                    if (isInRect(event.mouse.x, event.mouse.y, 263, 133, 397, 267)) {
                        al_draw_filled_circle(330, 200, 90, GRIS_TRANSPARENT);
                        while (!finCabane) {
                            al_wait_for_event(queue, &event);
                            switch (event.type) {
                                case ALLEGRO_EVENT_MOUSE_AXES : {
                                    for (int i = 0; i < NB_LIGNES_MAX; ++i) {
                                        for (int j = 0; j < NB_COLONNES_MAX; ++j) {
                                            if (isInRect(event.mouse.x, event.mouse.y, cases[i][j].x, cases[i][j].y,
                                                         cases[i][j].x + HAUTEUR, cases[i][j].y + LARGEUR)) {
                                                caseXActuCabane = cases[i][j].x;
                                                caseYActuCabane = cases[i][j].y;
                                                if (cases[i][j].occupe == 0) {
                                                    al_draw_scaled_bitmap(cabane, 0, 0, al_get_bitmap_width(cabane),
                                                                          al_get_bitmap_height(cabane), cases[i][j].x - LARGEUR,
                                                                          cases[i][j].y - 2*HAUTEUR, 75,75, 0);

                                                    if (preCaseXCabane != cases[i][j].x ||
                                                        preCaseYCabane != cases[i][j].y) {
                                                        preCaseXCabane = cases[i][j].x;
                                                        preCaseYCabane = cases[i][j].y;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    break;
                                }
                                case ALLEGRO_EVENT_MOUSE_BUTTON_UP: {
                                    if (isInRect(event.mouse.x, event.mouse.y, 263, 133, 397, 267)) {
                                        afficherToolBox(text, textBold, setting, cabane,
                                                        watercastle, usine, route, caserne);
                                        finCabane = true;
                                    }
                                    break;
                                }
                            }
                            al_flip_display();
                        }
                        break;
                    }
                    case ALLEGRO_EVENT_DISPLAY_CLOSE: {
                        jeu = true;
                        break;
                    }
                }
            }
        }
        al_destroy_display(display);
        al_destroy_event_queue(queue);
        al_destroy_timer(timer);
    }

}


