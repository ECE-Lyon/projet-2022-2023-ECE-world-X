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
#include "boat.h"
#include "cane.h"

#define BTN_GAUCHE 1

int main() {
    int i;
    int dessin = 0;
    ALLEGRO_DISPLAY* fenetre = NULL;
    ALLEGRO_EVENT_QUEUE* fifo = NULL;
    ALLEGRO_TIMER* timer = NULL;
    ALLEGRO_EVENT event;
    //Cane Canard;
    Boat smallBoat;
    Cane pixelCane;
    Coin ducks[NB_MAX_ENNEMIS];


    int xSouris, ySouris, offsetX, offsetY;
    bool fini = false, redessiner = false, deplacementSouris = false;

    assert(al_init());
    assert(al_init_primitives_addon());
    assert(al_install_mouse());
    assert(al_init_image_addon());

    canePos(&pixelCane, 80, 50);

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

    init_Duck(&ducks);
    init_boat(&smallBoat);
    init_Cane(&pixelCane);
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
                    if(pointEstDansRect(event.mouse.x, event.mouse.y, &pixelCane)) {
                        deplacementSouris = true;
                        offsetX = event.mouse.x - pixelCane.x;
                        offsetY = event.mouse.y - pixelCane.y;
                    }
                }
                break;
            }
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP: {
                if(event.mouse.button == BTN_GAUCHE) {
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
                    pixelCane.x = xSouris - offsetX;
                    pixelCane.y = ySouris - offsetY;
                    dessin = true;

                }
                apparitionDuck(&ducks);
                printDuck(&ducks);
                moveDuck(&ducks);
                duckReposition(&ducks);
                dessin = true;

                /*if(redessiner) {
                    al_clear_to_color(BLANC);
                    drawCane(&pixelCane);
                    redessiner = false;
                }*/
                break;
            }
        }
        if (dessin) {
            al_clear_to_color(BLANC);
            drawCane(&pixelCane);
            printDuck(&ducks);
            printBoat(&smallBoat);
            al_flip_display();
            dessin = false;
        }
    }



    al_destroy_event_queue(fifo);
    al_destroy_timer(timer);
    al_destroy_bitmap("../Images/pixelBoat.png");
    al_destroy_bitmap("../Images/Cane.png");
    al_destroy_display(fenetre);
    return 0;
}

