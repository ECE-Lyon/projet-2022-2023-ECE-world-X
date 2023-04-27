//
// Created by Félix Pignal on 27/04/2023.
//

#include "constantes.h"

int dessin = false;
int i, xMouse, yMouse, offsetXduck, offsetYduck, offsetXcursor, offsetYcursor;
int duckSelect = -1;
bool end = false;
ALLEGRO_DISPLAY* window = NULL;
ALLEGRO_EVENT_QUEUE* fifo = NULL;
ALLEGRO_TIMER* timer = NULL;
ALLEGRO_EVENT event;
ALLEGRO_MOUSE_STATE mouse_state;
Boat smallBoat;
Cane pixelCane;
Coin ducks[NB_MAX_ENNEMIS];


int launchGame(){

    assert(al_init());
    assert(al_init_primitives_addon());
    assert(al_install_mouse());
    assert(al_init_image_addon());

    canePos(&pixelCane, 80, 50);

    window = al_create_display(LARGEUR, HAUTEUR);
    assert(window);
    al_set_window_title(window, "CoinCoin");

    timer = al_create_timer(1.0/FPS);
    assert(timer);

    fifo = al_create_event_queue();
    assert(fifo);
    al_register_event_source(fifo, al_get_display_event_source(window));
    al_register_event_source(fifo, al_get_mouse_event_source());
    al_register_event_source(fifo, al_get_timer_event_source(timer));

    init_Duck(ducks);
    init_boat(&smallBoat);
    init_Cane(&pixelCane);
    //al_hide_mouse_cursor(window);

    al_start_timer(timer);
    while(!end) {
        al_wait_for_event(fifo, &event);
        switch(event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE: {
                end = true;
                break;
            }
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: {
                if(event.mouse.button == BTN_LEFT) {
                    for(i=0; i<NB_MAX_ENNEMIS; i++){
                        if(cane_active(event.mouse.x, event.mouse.y, &ducks[i])) {
                            duckSelect = i;
                            offsetXduck = event.mouse.x - ducks[i].x;
                            offsetYduck = event.mouse.y - ducks[i].y;
                        }
                    }
                }
                break;
            }
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP: {
                if(event.mouse.button == BTN_LEFT) {
                    duckSelect = -1;
                }
                break;
            }
            case ALLEGRO_EVENT_MOUSE_AXES: {
                /*if(cursEstDansWIND(event.mouse.x, event.mouse.y, &pixelCane)) {
                    offsetXcursor = event.mouse.x - pixelCane.x;
                    offsetYcursor = event.mouse.y - pixelCane.y;
                }*/
                xMouse = event.mouse.x;
                yMouse = event.mouse.y;
                if(duckSelect != -1){
                    ducks[duckSelect].x = xMouse - offsetXduck;
                    ducks[duckSelect].y = yMouse - offsetYduck;
                    dessin = true;
                }
                break;
            }
            case ALLEGRO_EVENT_TIMER: {
                al_get_mouse_state(&mouse_state);
                pixelCane.x = mouse_state.x - 80;
                pixelCane.y = mouse_state.y - 80;
                apparitionDuck(ducks);
                printDuck(ducks);
                moveDuck(ducks);
                duckReposition(ducks);
                dessin = true;
                break;
            }
        }
        if (dessin) {
            al_clear_to_color(BLEU);
            printDuck(ducks);
            printBoat(&smallBoat);
            drawCane(&pixelCane);
            al_flip_display();
            dessin = false;
        }
    }

    al_destroy_event_queue(fifo);
    al_destroy_timer(timer);
    al_destroy_display(window);
    return 0;

}