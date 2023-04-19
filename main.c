//
// Created by Félix Pignal on 05/04/2023.
//
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <assert.h>
#include "constantes.h"
#include "duck.h"
#include "test.h"

#define BTN_GAUCHE 1

int main() {
    int i;
    int dessin = 0;
    ALLEGRO_DISPLAY* fenetre = NULL;
    ALLEGRO_EVENT_QUEUE* fifo = NULL;
    ALLEGRO_TIMER* timer = NULL;
    ALLEGRO_EVENT event;
    Duck Canard;
    Ennemi *ennemis[NB_MAX_ENNEMIS];
    for( i = 0 ; i < NB_MAX_ENNEMIS; i++ ){
        ennemis[i] = malloc(sizeof(Ennemi));
    }

    int xSouris, ySouris, offsetX, offsetY;
    bool fini = false, redessiner = false, deplacementSouris = false;

    assert(al_init());
    assert(al_init_primitives_addon());
    assert(al_install_mouse());
    assert(al_init_image_addon());

    duckPosition(&Canard, 80, 50);

    fenetre = al_create_display(LARGEUR, HAUTEUR);
    assert(fenetre);
    al_set_window_title(fenetre, "CoinCoin");

    timer = al_create_timer(1.0/FPS);
    assert(timer);

    fifo = al_create_event_queue();
    assert(fifo);
    al_register_event_source(fifo, al_get_display_event_source(fenetre));
    al_register_event_source(fifo, al_get_mouse_event_source());
    al_register_event_source(fifo, al_get_timer_event_source(timer));

    init_ennemis(ennemis);
    //dessiner(Canard);

    al_start_timer(timer);
    while(!fini) {
        al_wait_for_event(fifo, &event);
        switch(event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE: {
                fini = true;
                break;
            }
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: {
                if(event.mouse.button == BTN_GAUCHE) {
                    if(pointEstDansRect(event.mouse.x, event.mouse.y, Canard)) {
                        deplacementSouris = true;
                        offsetX = event.mouse.x - Canard.x;
                        offsetY = event.mouse.y - Canard.y;
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
                if(deplacementSouris) {
                    Canard.x = xSouris - offsetX;
                    Canard.y = ySouris - offsetY;
                    redessiner = true;

                }
                dessin = 1;
                apparition_ennemis(ennemis);
                affiche_ennemis(ennemis);
                mouvement_ennemis(ennemis);

                duckReposition(&Canard);
                /*if(redessiner) {
                    dessiner(Canard);
                    redessiner = false;
                }*/
                break;
            }
        }
        if (dessin) {
            al_clear_to_color(BLANC);
            affiche_ennemis(ennemis);
            al_flip_display();
            dessin = 0;
        }
    }

    for (i = 0; i < NB_MAX_ENNEMIS; i++) {
        free(ennemis[i]);
    }

    al_destroy_event_queue(fifo);
    al_destroy_timer(timer);
    al_destroy_bitmap("../Images/pixelBoat2.png");
    al_destroy_bitmap("../Images/Duck.png");
    al_destroy_display(fenetre);
    return 0;
}

