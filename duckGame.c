//
// Created by Félix Pignal on 27/04/2023.
//

#include "constantes.h"

int dessin = false;
int i, offsetXduck, offsetYduck;
int tempsRestant = 20;
int duckSelect = -1;
bool end = false;
ALLEGRO_DISPLAY* window = NULL;
ALLEGRO_EVENT_QUEUE* fifo = NULL;
ALLEGRO_TIMER* timer = NULL;
ALLEGRO_TIMER* timerPartie = NULL;
ALLEGRO_EVENT event;
ALLEGRO_MOUSE_STATE mouse_state;
ALLEGRO_FONT *jedi;
Boat smallBoat;
Cane pixelCane;
Coin ducks[NB_MAX_ENNEMIS];

int launchGame(){

    assert(al_init());
    assert(al_init_primitives_addon());
    assert(al_install_mouse());
    assert(al_init_image_addon());
    assert(al_init_font_addon());
    assert(al_init_ttf_addon());

    canePos(&pixelCane, 80, 50);

    window = al_create_display(LARGEUR, HAUTEUR);
    assert(window);
    al_set_window_title(window, "CoinCoin");

    timer = al_create_timer(1.0/FPS);
    timerPartie = al_create_timer(1.0);
    assert(timer);

    fifo = al_create_event_queue();
    assert(fifo);
    al_register_event_source(fifo, al_get_display_event_source(window));
    al_register_event_source(fifo, al_get_mouse_event_source());
    al_register_event_source(fifo, al_get_timer_event_source(timer));
    al_register_event_source(fifo, al_get_timer_event_source(timerPartie));

    jedi = al_load_ttf_font("../Fonts/Starjhol.ttf",50,0);
    assert(jedi);
    init_Duck(ducks);
    init_boat(&smallBoat);
    init_Cane(&pixelCane);
    //al_hide_mouse_cursor(window);

    al_start_timer(timer);
    al_start_timer(timerPartie);
    while(!end) {
        al_wait_for_event(fifo, &event);
        al_get_mouse_state(&mouse_state);
        switch(event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE: {
                end = true;
                break;
            }
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: {
                printf("Mouse button down event triggered\n");
                if(event.mouse.button == BTN_LEFT) {
                    for(i=0; i<NB_MAX_ENNEMIS; i++){
                        if(cane_active(event.mouse.x, event.mouse.y, &ducks[i])) {
                            duckSelect = i;
                            offsetXduck = event.mouse.x - ducks[i].x;
                            offsetYduck = event.mouse.y - ducks[i].y;
                            printf("Duck selected: %d\n", i);
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
            case ALLEGRO_EVENT_TIMER: {
                if(event.timer.source == timerPartie){
                    tempsRestant--;
                    if(tempsRestant == 0){
                        end = true;
                    }
                }
                al_get_mouse_state(&mouse_state);
                pixelCane.x = mouse_state.x - 80;
                pixelCane.y = mouse_state.y - 80;
                if(duckSelect != -1 ){
                    ducks[duckSelect].x = mouse_state.x - offsetXduck;
                    ducks[duckSelect].y = mouse_state.y - offsetYduck;
                    dessin = true;
                }
                if(duckSelect != -1 && duckOnBoat(&smallBoat, &ducks[duckSelect])){
                    if (ducks[duckSelect].compte != true){
                        smallBoat.score++;
                        ducks[duckSelect].actif = 0;
                        ducks[duckSelect].compte = true;
                        ducks[duckSelect].compte = false;
                        printf("score: %d\n",smallBoat.score);
                        duckSelect = -1;
                    }
                    dessin = true;
                }
                apparitionDuck(ducks);
                duckReposition(ducks);
                dessin = true;
                break;
            }
        }
        if (dessin) {
            al_clear_to_color(BLEU);
            al_draw_textf(jedi,NOIR,50,50,0,"Score: %d",smallBoat.score);
            al_draw_textf(jedi,NOIR,50,1000,0,"temps: %d",tempsRestant);
            printBoat(&smallBoat);
            printDuck(ducks);
            drawCane(&pixelCane);
            moveDuck(ducks);
            al_flip_display();
            dessin = false;
        }

    }

    al_destroy_font(jedi);
    al_destroy_event_queue(fifo);
    al_destroy_timer(timer);
    al_destroy_display(window);
    return 0;

}