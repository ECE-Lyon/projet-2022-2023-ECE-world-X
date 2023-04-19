//
// Created by trist on 19/04/2023.
//
#include "character.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

#define FPS 60.0
#define WIDTH 1200
#define HEIGHT 600

ALLEGRO_DISPLAY* setting(){
    assert(al_init());
    ALLEGRO_DISPLAY*display=NULL;
    display=al_create_display(WIDTH, HEIGHT);
    assert(display!=NULL);
    //Initialiser avec assert le reste
    assert(al_init_image_addon());
    assert(al_init_primitives_addon());
    assert(al_install_keyboard());
    al_set_window_title(display,"Title");
    al_set_window_position(display,200,100);
    al_flip_display();
    srand(time(NULL));
    return display;

}


void menu(){
    ALLEGRO_DISPLAY* display=setting();
    int isEnd=0;
    ALLEGRO_EVENT_QUEUE*queue;

    Perso player1;
    init_Luke(&player1);

    //Créer un timer si nécéssaire
    ALLEGRO_TIMER*timer=al_create_timer(1/FPS);
    al_start_timer(timer);
    queue=al_create_event_queue();
    assert(queue);


    //Ajouter tous les types d'événements souhaités
    al_register_event_source(queue,al_get_display_event_source(display));
    al_register_event_source(queue,al_get_timer_event_source(timer));


    while(!isEnd){
        ALLEGRO_EVENT event={0};
        al_wait_for_event(queue,&event);//on pioche un événement dès qu'il y en a un
        switch(event.type){//en fonction de son type (événement de souris,du clavier...),on agit
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                isEnd=1;
                break;
            case ALLEGRO_EVENT_KEY_DOWN://Si on arrive ici, c'est qu'on a pioché un événement du clavier de type touche  enfoncée
                switch(event.keyboard.keycode){//On vérifie de quelle touche il s'agit
                    case ALLEGRO_KEY_ESCAPE://on ne gère quel cas où la touche enfoncée est ECHAP
                        isEnd=1;
                        break;
                }
                break;
            case ALLEGRO_EVENT_TIMER :
                al_clear_to_color(al_map_rgb(0,0,0));
                print_character(player1);
                al_flip_display();
        }

    }
    al_destroy_event_queue(queue);
}

