#include "menu.h"
#include "routes.h"
#include "maison.h"
#include "chateauEau.h"
#include "usine.h"
#include "TDG.h"


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
    ALLEGRO_BITMAP *argent, *elec, *habitant, *eau, *setting, *cabane, *maison, *immeuble, *gratteciel, *watercastle, *usine, *route, *caserne, *clock = NULL;
    ALLEGRO_BITMAP *fond, *fplateau = NULL;
    ALLEGRO_FONT *text, *textBold;
    ALLEGRO_BITMAP *routeNS, *routeOE, *routeTE, *routeTN, *routeTO, *routeTS, *routeX, *virageNE, *virageON, *virageSE, *virageSO;


    ///routes
    routeNS = al_load_bitmap("../Routes/routeNS.png");
    routeOE = al_load_bitmap("../Routes/routeOE.png");
    routeTE = al_load_bitmap("../Routes/routeTE.png");
    routeTO = al_load_bitmap("../Routes/routeTO.png");
    routeTS = al_load_bitmap("../Routes/routeTS.png");
    routeTN = al_load_bitmap("../Routes/routeTN.png");
    routeX = al_load_bitmap("../Routes/routeX.png");
    virageNE = al_load_bitmap("../Routes/virageNE.png");
    virageON = al_load_bitmap("../Routes/virageON.png");
    virageSE = al_load_bitmap("../Routes/virageSE.png");
    virageSO = al_load_bitmap("../Routes/virageSO.png");
    ///initialisation bitmaps
    argent = al_load_bitmap("../Images/argent.png");
    elec = al_load_bitmap("../Images/Electricite.png");
    habitant = al_load_bitmap("../Images/people.png");
    eau = al_load_bitmap("../Images/water.png");
    setting = al_load_bitmap("../Images/settings.png");
    fplateau = al_load_bitmap("../Images/fond_jeu.jpg");
    fond = al_load_bitmap("../Images/VF_Fond.png");
    cabane = al_load_bitmap("../Images/cabana.png");
    maison = al_load_bitmap("../Images/maison.png");
    immeuble = al_load_bitmap("../Images/immeuble.png");
    gratteciel = al_load_bitmap("../Images/gratteciel.png");
    watercastle = al_load_bitmap("../Images/watercastle.png");
    usine = al_load_bitmap("../Images/usine.png");
    route = al_load_bitmap("../Images/route.png");
    caserne = al_load_bitmap("../Images/caserne.png");
    clock = al_load_bitmap("../Images/clock.png");

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
    bool envoiRoute = false;
    bool finCabane = false;

    int dessin = -1;
    int jour = 0;
    int mois = 12;
    int annee = 2022;

    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());

    al_set_window_title(display, "ECE City");
    al_set_window_position(display, -3, 0);
    Info info;
    info.argent = 500000;
    info.nbhabitant = 0;
    info.elec = 0;
    info.eau = 0;
    Case cases[NB_LIGNES_MAX][NB_COLONNES_MAX];
    preCase preCases[NB_LIGNES_MAX][NB_COLONNES_MAX];
    initCases(cases);
    initPreCases(preCases);
    menud(fond);
    while (!fin) {//boucle principal du jeu
        al_wait_for_event(queue, &event);
        while (!menu) {//boucle du menu
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
                        mode = 0;//mode capitaliste
                    }

                    if (isInRect(event.mouse.x, event.mouse.y, 1111, 809, 1705, 960)) {
                        menu = true;
                        mode = 1;//mode communiste
                    }
                    break;
                }
            }
        }
        ///on affiche tous les elements du jeu
        plateau(fplateau);
        dessinerCases(cases);
        afficherRessources(info, text, eau, argent, habitant, elec);
        afficherToolBox(text, textBold, setting, cabane, watercastle, usine, route, caserne);
        al_draw_rounded_rectangle(48, 738, 402, 822, 10, 10, ROUGE, 2);
        al_flip_display();
        while (!jeu) {
            al_wait_for_event(queue, &event);
            switch (event.type) {
                case ALLEGRO_EVENT_MOUSE_BUTTON_UP : {///on gere l'affichage de la toolbox et des niveaux
                    if (isInRect(event.mouse.x, event.mouse.y, 53, 133, 187, 267)) {
                        dessin = 1;
                    }
                    if (isInRect(event.mouse.x, event.mouse.y, 263, 133, 397, 267)) {
                        dessin = 2;
                    }
                    if (isInRect(event.mouse.x, event.mouse.y, 53, 333, 187, 467)) {
                        dessin = 3;
                    }
                    if (isInRect(event.mouse.x, event.mouse.y, 263, 333, 397, 467)) {
                        dessin = 4;
                    }
                    if (isInRect(event.mouse.x, event.mouse.y, 56, 746, 400, 820)) {
                        raffraichir(cases, info, fplateau, text, textBold, setting, cabane, watercastle, usine, route,
                                    caserne, eau, argent, habitant, elec);
                        al_draw_rounded_rectangle(48, 738, 402, 822, 10, 10, ROUGE, 2);
                        dessinerBat(cases, cabane, maison, immeuble, gratteciel, watercastle, usine, routeOE, routeNS,
                                    routeTE,
                                    routeTN, routeTO, routeTS, routeX, virageNE, virageON, virageSE, virageSO);
                    }
                    if (isInRect(event.mouse.x, event.mouse.y, 56, 846, 400, 920)) {
                        raffraichir(cases, info, fplateau, text, textBold, setting, cabane, watercastle, usine, route,
                                    caserne, eau, argent, habitant, elec);
                        al_draw_rounded_rectangle(48, 838, 402, 922, 10, 10, ROUGE, 2);
                        dessinerEau(cases, watercastle);
                    }
                    if (isInRect(event.mouse.x, event.mouse.y, 56, 946, 400, 1020)) {
                        raffraichir(cases, info, fplateau, text, textBold, setting, cabane, watercastle, usine, route,
                                    caserne, eau, argent, habitant, elec);
                        al_draw_rounded_rectangle(48, 938, 402, 1022, 10, 10, ROUGE, 2);
                        dessinerElec(cases, usine);
                    }
                    break;
                }
                case ALLEGRO_EVENT_TIMER: {
                    switch (dessin) {///en fonction de ce qu'on a choisi dans la toolbox
                        case 1 : {
                            dessinerRoutes(&dessin, cases, &info, text, textBold, setting,
                                           cabane, watercastle, usine, caserne, eau, argent, habitant, elec, route);
                            break;
                        }
                        case 2 : {
                            dessinerMaisons(&dessin, cases, &info, text, textBold, setting, cabane, watercastle, usine,
                                            route, caserne, eau, argent, habitant, elec);
                            break;
                        }
                        case 3 : {
                            dessinerChateauEau(&dessin, cases, &info, text, textBold, setting, cabane, watercastle,
                                               usine, route, caserne, eau, argent, habitant, elec);
                            break;
                        }
                        case 4 : {
                            dessinerUsines(&dessin, cases, &info, text, textBold, setting, cabane, watercastle, usine,
                                           route, caserne, eau, argent, habitant, elec);
                        }
                    }
                    if(mode == 0){///mode capitaliste
                        for (int i = 0; i < NB_LIGNES_MAX; ++i) {
                            for (int j = 0; j < NB_COLONNES_MAX; ++j) {
                                if (preCases[i][j].occupe != cases[i][j].occupe ||
                                    preCases[i][j].niveau != cases[i][j].niveau) {
                                    dessinerBat(cases, cabane, maison, immeuble, gratteciel, watercastle, usine,
                                                routeOE,
                                                routeNS, routeTE,
                                                routeTN, routeTO, routeTS, routeX, virageNE, virageON, virageSE,
                                                virageSO);
                                    int ordre = creerTableauRouteAdjacentes(cases);
                                    creerFichierArete(cases, ordre);
                                }
                                preCases[i][j].occupe = cases[i][j].occupe;
                                preCases[i][j].niveau = cases[i][j].niveau;
                            }
                        }
                        for (int i = 0; i < NB_LIGNES_MAX; ++i) {///permet d'ameliorer les batiments en fonction de leur cycle et d'enlever les ressources correspondant
                            for (int j = 0; j < NB_COLONNES_MAX; ++j) {
                                if (cases[i][j].occupe == 2 && cases[i][j].niveau <= 4) {
                                    cases[i][j].temps = cases[i][j].temps + 1;
                                    if (cases[i][j].temps == 900) {///niveau 1 vers 2
                                        cases[i][j].niveau = cases[i][j].niveau + 1;
                                        info.argent -= 1000;
                                        info.nbhabitant += 200;
                                        info.elec -= 50;
                                        info.eau -= 50;
                                        plateau(fplateau);
                                        dessinerCases(cases);
                                        afficherRessources(info, text, eau, argent, habitant, elec);
                                        afficherToolBox(text, textBold, setting, cabane, watercastle, usine, route,
                                                        caserne);
                                    }
                                    if (cases[i][j].temps == 1800) {///niveau 2 vers 3
                                        cases[i][j].niveau = cases[i][j].niveau + 1;
                                        info.argent -= 2000;
                                        info.nbhabitant += 400;
                                        info.elec -= 150;
                                        info.eau -= 150;
                                        plateau(fplateau);
                                        dessinerCases(cases);
                                        afficherRessources(info, text, eau, argent, habitant, elec);
                                        afficherToolBox(text, textBold, setting, cabane, watercastle, usine, route,
                                                        caserne);
                                    }
                                    if (cases[i][j].temps == 2700) {///niveau 3 vers 4
                                        cases[i][j].niveau = cases[i][j].niveau + 1;
                                        info.argent -= 3000;
                                        info.nbhabitant += 600;
                                        info.elec -= 300;
                                        info.eau -= 300;
                                        plateau(fplateau);
                                        dessinerCases(cases);
                                        afficherRessources(info, text, eau, argent, habitant, elec);
                                        afficherToolBox(text, textBold, setting, cabane, watercastle, usine, route,
                                                        caserne);
                                    }

                                }
                            }
                        }
                    }

                    if(mode == 1){///mode communiste
                        for (int i = 0; i < NB_LIGNES_MAX; ++i) {
                            for (int j = 0; j < NB_COLONNES_MAX; ++j) {
                                if (preCases[i][j].occupe != cases[i][j].occupe ||
                                    preCases[i][j].niveau != cases[i][j].niveau) {
                                    dessinerBat(cases, cabane, maison, immeuble, gratteciel, watercastle, usine, routeOE,
                                                routeNS, routeTE,
                                                routeTN, routeTO, routeTS, routeX, virageNE, virageON, virageSE, virageSO);
                                }
                                preCases[i][j].occupe = cases[i][j].occupe;
                                preCases[i][j].niveau = cases[i][j].niveau;
                            }
                        }
                        for (int i = 0; i < NB_LIGNES_MAX; ++i) {
                            for (int j = 0; j < NB_COLONNES_MAX; ++j) {
                                if (cases[i][j].occupe == 2 && cases[i][j].niveau <= 4) {
                                    cases[i][j].temps = cases[i][j].temps + 1;
                                    if (cases[i][j].temps == 900 && info.elec -50 >= 0 && info.eau - 50 >= 0) {///pareil qu'en mode capitaliste mais on verifie si il y a suffisament de ressources avant d'am??liorer le batiment
                                        cases[i][j].niveau = cases[i][j].niveau + 1;
                                        info.argent -= 1000;
                                        info.nbhabitant += 200;
                                        info.elec -= 50;
                                        info.eau -= 50;
                                        plateau(fplateau);
                                        dessinerCases(cases);
                                        afficherRessources(info, text, eau, argent, habitant, elec);
                                        afficherToolBox(text, textBold, setting, cabane, watercastle, usine, route,
                                                        caserne);
                                    }
                                    if (cases[i][j].temps == 1800 && info.elec - 150 >= 0 && info.eau - 150 >= 0) {
                                        cases[i][j].niveau = cases[i][j].niveau + 1;
                                        info.argent -= 2000;
                                        info.nbhabitant += 400;
                                        info.elec -= 150;
                                        info.eau -= 150;
                                        plateau(fplateau);
                                        dessinerCases(cases);
                                        afficherRessources(info, text, eau, argent, habitant, elec);
                                        afficherToolBox(text, textBold, setting, cabane, watercastle, usine, route,
                                                        caserne);
                                    }
                                    if (cases[i][j].temps == 2700 && info.elec - 300 >= 0 && info.eau - 300 >= 0) {
                                        cases[i][j].niveau = cases[i][j].niveau + 1;
                                        info.argent -= 3000;
                                        info.nbhabitant += 600;
                                        info.elec -= 300;
                                        info.eau -= 300;
                                        plateau(fplateau);
                                        dessinerCases(cases);
                                        afficherRessources(info, text, eau, argent, habitant, elec);
                                        afficherToolBox(text, textBold, setting, cabane, watercastle, usine, route,
                                                        caserne);
                                    }

                                }
                            }
                        }
                    }
                    jour = jour + 1;
                    if (jour == 900) {///permet de compter le temps
                        jour = 0;
                        mois = mois + 1;
                        info.argent += 10 * info.nbhabitant;

                    }
                    if (mois == 13) {
                        mois = 1;
                        annee = annee + 1;
                    }
                    al_draw_filled_rectangle(200, 20, 400, 80, GRIS_FONCE);

                    al_draw_scaled_bitmap(clock, 0, 0, al_get_bitmap_width(clock),
                                          al_get_bitmap_height(clock), 180, 18, 60, 60, 0);
                    al_draw_textf(text, BLANC, 250, 30, 0, ": %d/%d", mois, annee);///affichage du temps

                    break;
                }

                case ALLEGRO_EVENT_DISPLAY_CLOSE: {
                    jeu = true;
                    fin = true;
                    break;
                }
            }
            al_flush_event_queue(queue);
            al_flip_display();
        }
        al_destroy_display(display);
        al_destroy_event_queue(queue);
        al_destroy_timer(timer);
    }
}