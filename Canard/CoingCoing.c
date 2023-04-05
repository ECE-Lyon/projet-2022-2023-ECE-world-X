//
// Created by Félix Pignal on 05/04/2023.
//

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <assert.h>
#include "CoingCoing.h"
#define LARGEUR 1200*2
#define HAUTEUR 600*2
#define PX_DEPLACEMENT_RECTANGLE 4
#define BLANC al_map_rgb(128, 197, 222)
#define BTN_GAUCHE 1
#define BTN_DROIT 2

enum {TOUCHE_GAUCHE, TOUCHE_DROITE, TOUCHE_HAUT, TOUCHE_BAS, NB_TOUCHES};
//    0         , 1         , 2       , 3      , 4

typedef struct {
    int x, y, largeur, hauteur;
} Rect;

void dessiner(Rect r) {
    al_clear_to_color(BLANC);
    al_draw_bitmap(al_load_bitmap("/Users/felixpignal/CLionProjects/canard/Duck.png"),r.x,r.y,0);
    al_flip_display();
}

void positionnerRectangle(Rect* r, int lar, int haut) {
    r->largeur = lar;
    r->hauteur = haut;
    r->x = LARGEUR / 2 - r->largeur / 2;
    r->y = HAUTEUR / 2 - r->hauteur / 2;
}

bool pointEstDansZone(int x, int y, int x1, int y1, int x2, int y2) {
    return x >= 0 && x <= LARGEUR && y >= 0 && y < HAUTEUR;
}

bool pointEstDansRect(int x, int y, Rect r) {
    return pointEstDansZone(x, y, r.x, r.y, r.x+r.largeur, r.y+r.hauteur);
}

void repositionnerRectangle(Rect* r) {
    if(r->x < 0) { r->x = 0; }
    if(r->y < 0) { r->y = 0; }
    if(r->x+r->largeur > LARGEUR) { r->x = LARGEUR - r->largeur; }
    if(r->y+r->hauteur > HAUTEUR) { r->y = HAUTEUR - r->hauteur; }
}

int main() {
    ALLEGRO_DISPLAY* fenetre = NULL;
    ALLEGRO_EVENT_QUEUE* fifo = NULL;
    ALLEGRO_TIMER* timer = NULL;
    //ALLEGRO_BITMAP* car = al_load_bitmap("/Users/felixpignal/CLionProjects/canard/cartoon-duck-pixel-design_61878-497.jpg.avif");
    ALLEGRO_EVENT event;

    bool touchesEnfoncees[NB_TOUCHES] = {false};
    Rect rectangle;
    int xSouris, ySouris, offsetX, offsetY;
    bool fini = false, redessiner = false, deplacementSouris = false;

    assert(al_init());
    assert(al_init_primitives_addon());
    assert(al_install_keyboard());
    assert(al_install_mouse());
    assert(al_init_image_addon());

    positionnerRectangle(&rectangle, 80, 50);

    fenetre = al_create_display(LARGEUR, HAUTEUR);
    assert(fenetre);// on verifie que fenetre n'est pas NULL
    al_set_window_title(fenetre, "CoinCoin");

    timer = al_create_timer(1.0/200.0);
    assert(timer);

    fifo = al_create_event_queue();
    assert(fifo);
    al_register_event_source(fifo, al_get_display_event_source(fenetre));
    al_register_event_source(fifo, al_get_keyboard_event_source());
    al_register_event_source(fifo, al_get_mouse_event_source());
    al_register_event_source(fifo, al_get_timer_event_source(timer));

    dessiner(rectangle);

    al_start_timer(timer);
    while(!fini) {
        al_wait_for_event(fifo, &event);
        switch(event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE: {
                fini = true;
                break;
            }
            case ALLEGRO_EVENT_KEY_DOWN: {
                switch(event.keyboard.keycode) {
                    case ALLEGRO_KEY_Q:
                    case ALLEGRO_KEY_LEFT: {
                        touchesEnfoncees[TOUCHE_GAUCHE] = true;
                        break;
                    }
                    case ALLEGRO_KEY_D:
                    case ALLEGRO_KEY_RIGHT: {
                        touchesEnfoncees[TOUCHE_DROITE] = true;
                        break;
                    }
                    case ALLEGRO_KEY_W:
                    case ALLEGRO_KEY_UP: {
                        touchesEnfoncees[TOUCHE_HAUT] = true;
                        break;
                    }
                    case ALLEGRO_KEY_S:
                    case ALLEGRO_KEY_DOWN: {
                        touchesEnfoncees[TOUCHE_BAS] = true;
                        break;
                    }
                }
                break;
            }
            case ALLEGRO_EVENT_KEY_UP: {
                switch(event.keyboard.keycode) {
                    case ALLEGRO_KEY_Q:
                    case ALLEGRO_KEY_LEFT: {
                        touchesEnfoncees[TOUCHE_GAUCHE] = false;
                        break;
                    }
                    case ALLEGRO_KEY_D:
                    case ALLEGRO_KEY_RIGHT: {
                        touchesEnfoncees[TOUCHE_DROITE] = false;
                        break;
                    }
                    case ALLEGRO_KEY_W:
                    case ALLEGRO_KEY_UP: {
                        touchesEnfoncees[TOUCHE_HAUT] = false;
                        break;
                    }
                    case ALLEGRO_KEY_S:
                    case ALLEGRO_KEY_DOWN: {
                        touchesEnfoncees[TOUCHE_BAS] = false;
                        break;
                    }
                }
                break;
            }
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: {
                // on vient d'enfoncer un bouton de la souris, lequel ?*
                if(event.mouse.button == BTN_GAUCHE) {
                    if(pointEstDansRect(event.mouse.x, event.mouse.y, rectangle)) {
                        deplacementSouris = true;
                        offsetX = event.mouse.x - rectangle.x;
                        offsetY = event.mouse.y - rectangle.y;
                    }
                }
                break;
            }
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP: {
                if(event.mouse.button == BTN_GAUCHE) { // si on relache le bouton gauche
                    deplacementSouris = false;
                }
                break;
            }
            case ALLEGRO_EVENT_MOUSE_AXES: {
                xSouris = event.mouse.x;
                ySouris = event.mouse.y;
                break;
            }
            case ALLEGRO_EVENT_TIMER: {
                if(touchesEnfoncees[TOUCHE_DROITE]) {
                    rectangle.x += PX_DEPLACEMENT_RECTANGLE;
                    redessiner = true;
                }
                if(touchesEnfoncees[TOUCHE_GAUCHE]) {
                    rectangle.x -= PX_DEPLACEMENT_RECTANGLE;
                    redessiner = true;
                }
                if(touchesEnfoncees[TOUCHE_HAUT]) {
                    rectangle.y -= PX_DEPLACEMENT_RECTANGLE;
                    redessiner = true;
                }
                if(touchesEnfoncees[TOUCHE_BAS]) {
                    rectangle.y += PX_DEPLACEMENT_RECTANGLE;
                    redessiner = true;
                }
                if(deplacementSouris) {
                    rectangle.x = xSouris - offsetX;
                    rectangle.y = ySouris - offsetY;
                    redessiner = true;
                }
                repositionnerRectangle(&rectangle);
                if(redessiner) {
                    dessiner(rectangle);
                    redessiner = false;
                }
                break;
            }
        }
    }

    al_destroy_display(fenetre);
    al_destroy_event_queue(fifo);
    al_destroy_timer(timer);
    return 0;
}

