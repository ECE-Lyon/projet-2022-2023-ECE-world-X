//
// Created by trist on 19/04/2023.
//


#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

#include "snake.h"
#include "constante.h"
#include "interface.h"
#include "miam.h"
#include "game.h"

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

void game(){
    ALLEGRO_DISPLAY* display=setting();
    int isEnd=0;
    float fps;
    int changeallowed;

    fps = 7.0f;
    changeallowed = 1;
    ALLEGRO_EVENT_QUEUE* queue;

    //Créer un timer si nécéssaire
    ALLEGRO_TIMER*timer=al_create_timer(1/fps);
    al_start_timer(timer);
    queue=al_create_event_queue();
    assert(queue);

    al_register_event_source(queue,al_get_display_event_source(display));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue,al_get_timer_event_source(timer));

    Damier board;
    Body* player;
    star bg_star[NBSTAR];
    Food pomme;
    Waychange* lstchange = NULL;

    player = malloc(sizeof(Body));

    init_board(&board);
    init_snake(player);
    create_star_list(bg_star);
    init_apple(&pomme, board);

    Waychange* newchange;

    while(!isEnd){
        ALLEGRO_EVENT event={0};
        al_wait_for_event(queue,&event);

        switch(event.type){//en fonction de son type (événement de souris,du clavier...),on agit
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                isEnd=1;
                break;
            case ALLEGRO_EVENT_KEY_DOWN://Si on arrive ici, c'est qu'on a pioché un événement du clavier de type touche  enfoncée
                switch(event.keyboard.keycode){//On vérifie de quelle touche il s'agit
                    case ALLEGRO_KEY_ESCAPE://on ne gère quel cas où la touche en foncée est ECHAP
                        isEnd=1;
                        break;
                    case ALLEGRO_KEY_UP :
                        if (changeallowed == 1) {
                            if (player->direction != BAS && player->direction != HAUT) {
                                change_direction(player, HAUT);
                                if (player->next != NULL) {
                                    newchange= add_change_way(player, &lstchange);
                                    set_change(player->next, newchange);
                                }
                                changeallowed = 0;
                            }
                            break;
                        }
                    case ALLEGRO_KEY_RIGHT :
                        if (changeallowed == 1) {
                            if (player->direction != GAUCHE && player->direction != DROITE) {
                                change_direction(player, DROITE);
                                if (player->next != NULL) {
                                    newchange = add_change_way(player, &lstchange);
                                    set_change(player->next, newchange);
                                }
                                changeallowed = 0;
                            }
                            break;
                        }
                    case ALLEGRO_KEY_DOWN :
                        if (changeallowed == 1) {
                            if (player->direction != HAUT && player->direction != BAS) {
                                change_direction(player, BAS);
                                if (player->next != NULL) {
                                    newchange = add_change_way(player, &lstchange);
                                    set_change(player->next, newchange);
                                }
                                changeallowed = 0;
                            }
                            break;
                        }
                    case ALLEGRO_KEY_LEFT :
                        if (changeallowed == 1) {
                            if (player->direction != DROITE && player->direction != GAUCHE) {
                                change_direction(player, GAUCHE);
                                if (player->next != NULL) {
                                    newchange = add_change_way(player, &lstchange);
                                    set_change(player->next, newchange);
                                }
                                changeallowed = 0;
                            }
                            break;
                        }
                }
                break;
            case ALLEGRO_EVENT_TIMER :
                changeallowed = 1;
                isEnd = update(player, lstchange, &pomme, bg_star, board);
                al_flip_display();
                break;
        }
    }
    al_destroy_event_queue(queue);
    free_snake(player);
}