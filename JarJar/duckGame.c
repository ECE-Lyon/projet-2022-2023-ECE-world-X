//
// Created by Félix Pignal on 27/04/2023.
//

#include "constantes.h"
#include "duckGame.h"
#include "../Map/character.h"


void init_lauchGame(Game *jeux, ALLEGRO_DISPLAY* display){
    jeux->i = 0;
    jeux->dessin = false;
    jeux->offsetXduck = 0;
    jeux->offsetYduck = 0;
    jeux->tempsRestant = 90;
    jeux->duckSelect = -1;
    jeux->gamePause = false;
    jeux->window = display;
    //jeux->event;
    jeux->fifo = al_create_event_queue();
    jeux->timer = al_create_timer(1.0/FPSCOIN);
    jeux->timerPartie = al_create_timer(1.0);
    //jeux->mouse_state;
    jeux->jedi = al_load_ttf_font("../JarJar/Fonts/Starjedi.ttf",30,0);
    jeux->jediout = al_load_ttf_font("../JarJar/Fonts/Starjout.ttf",30,0);
    jeux->jedihol = al_load_ttf_font("../JarJar/Fonts/Starjhol.ttf",50,0);
    jeux->backgoundMusic = al_load_sample("../JarJar/Audio/AcrosstheStars.ogg");
    init_boat(&jeux->smallBoat);
    init_Cane(&jeux->pixelCane);
    init_Duck(jeux->ducks);
}

int launchGame(Game *jeux, Perso *playeractive){

    int isEnd = 0;

    al_reserve_samples(1);
    assert(jeux->backgoundMusic);
    assert(jeux->window);
    al_set_window_title(jeux->window, "JarJar le filou");

    assert(jeux->timer);
    assert(jeux->timerPartie);
    assert(jeux->fifo);
    assert(jeux->jedi);
    al_register_event_source(jeux->fifo, al_get_display_event_source(jeux->window));
    al_register_event_source(jeux->fifo, al_get_mouse_event_source());
    al_register_event_source(jeux->fifo, al_get_keyboard_event_source());
    al_register_event_source(jeux->fifo, al_get_timer_event_source(jeux->timer));
    al_register_event_source(jeux->fifo, al_get_timer_event_source(jeux->timerPartie));

    canePos(&jeux->pixelCane, 80, 50);
    //al_hide_mouse_cursor(jeux->window);
    al_start_timer(jeux->timer);
    al_start_timer(jeux->timerPartie);
    al_play_sample(jeux->backgoundMusic,1.0f,0.0f,1.0f,ALLEGRO_PLAYMODE_LOOP,0);
    while(!isEnd) {
        al_wait_for_event(jeux->fifo, &jeux->event);
        al_get_mouse_state(&jeux->mouse_state);
        switch(jeux->event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE: {
                isEnd = 1;
                break;
            }
            case ALLEGRO_EVENT_KEY_DOWN:{
                if (jeux->event.keyboard.keycode == ALLEGRO_KEY_P) {
                    jeux->gamePause = !jeux->gamePause;
                    if (jeux->gamePause) {
                        al_stop_timer(jeux->timerPartie);
                        al_stop_timer(jeux->timer);
                        al_draw_text(jeux->jedihol, JAUNE, LARGEUR /2, HAUTEUR/4, ALLEGRO_ALIGN_CENTER, "Game Paused");
                        al_draw_text(jeux->jedi, JAUNE, LARGEUR /2, HAUTEUR/2, ALLEGRO_ALIGN_CENTER, "press P to resume");
                        al_flip_display();
                    } else {
                        al_start_timer(jeux->timer);
                        al_start_timer(jeux->timerPartie);
                    }
                }
                if(jeux->event.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
                    isEnd=1;
                    break;
                }
                break;
            }
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: {
                if(jeux->event.mouse.button == BTN_LEFT) {
                    for(jeux->i=0; jeux->i < NB_MAX_JARJAR; jeux->i++){
                        if(cane_active(jeux->event.mouse.x, jeux->event.mouse.y, &jeux->ducks[jeux->i])) {
                            jeux->duckSelect = jeux->i;
                            jeux->offsetXduck = jeux->event.mouse.x - jeux->ducks[jeux->i].x;
                            jeux->offsetYduck = jeux->event.mouse.y - jeux->ducks[jeux->i].y;
                        }
                    }
                }
                break;
            }
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP: {
                if(jeux->event.mouse.button == BTN_LEFT) {
                    jeux->duckSelect = -1;
                }
                break;
            }
            case ALLEGRO_EVENT_TIMER: {
                if(jeux->event.timer.source == jeux->timerPartie){
                    jeux->tempsRestant--;
                    if(jeux->tempsRestant == 0){
                        isEnd = 1;
                        break;
                    }
                }
                jeux->pixelCane.x = jeux->mouse_state.x - 20;
                jeux->pixelCane.y = jeux->mouse_state.y - 20;
                if(jeux->duckSelect != -1 ){
                    jeux->ducks[jeux->duckSelect].x = jeux->mouse_state.x - jeux->offsetXduck;
                    jeux->ducks[jeux->duckSelect].y = jeux->mouse_state.y - jeux->offsetYduck;
                    jeux->dessin = true;
                }
                if(jeux->duckSelect != -1 && duckOnBoat(&jeux->smallBoat, &jeux->ducks[jeux->duckSelect])){
                    if (jeux->ducks[jeux->duckSelect].compte != true){
                        jeux->smallBoat.score++;
                        jeux->ducks[jeux->duckSelect].actif = 0;
                        jeux->ducks[jeux->duckSelect].compte = true;
                        jeux->ducks[jeux->duckSelect].compte = false;
                        jeux->duckSelect = -1;
                    }
                    jeux->dessin = true;
                }
                apparitionDuck(jeux->ducks);
                duckReposition(jeux->ducks);
                jeux->dessin = true;
                break;
            }
        }
        if (jeux->dessin) {
            al_clear_to_color(BLEU);
            al_draw_textf(jeux->jedi,NOIR,50,50,ALLEGRO_ALIGN_LEFT,"Score: %d",jeux->smallBoat.score);
            al_draw_textf(jeux->jediout,NOIR,50,550,ALLEGRO_ALIGN_LEFT,"temps: %d",jeux->tempsRestant);
            printBoat(&jeux->smallBoat);
            printDuck(jeux->ducks);
            drawCane(&jeux->pixelCane);
            moveDuck(jeux->ducks);
            al_flip_display();
            jeux->dessin = false;
        }
    }
    playeractive->score = jeux->smallBoat.score;
    al_destroy_sample(jeux->backgoundMusic);
    al_destroy_font(jeux->jedi);
    al_destroy_event_queue(jeux->fifo);
    al_destroy_timer(jeux->timer);
    al_destroy_timer(jeux->timerPartie);
    //al_destroy_display(jeux->window);
    return 0;

}