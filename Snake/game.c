//
// Created by trist on 19/04/2023.
//


#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "snake.h"
#include "constante.h"
#include "interface.h"
#include "miam.h"
#include "game.h"


void game(ALLEGRO_DISPLAY* display){
    int isEnd=0;
    float fps;
    int changeallowed;
    int size = 0;

    fps = 6.0f;
    changeallowed = 1;
    ALLEGRO_EVENT_QUEUE* queue2;

    ALLEGRO_BITMAP* stormtrooper = al_load_bitmap("../Snake/strooperhead.png");
    if(stormtrooper == NULL) {
        printf("Image doesn't load\n");
    }

    //Créer un timer si nécéssaire
    ALLEGRO_TIMER*timer=al_create_timer(1/fps);
    al_start_timer(timer);
    queue2=al_create_event_queue();
    assert(queue2);

    al_register_event_source(queue2,al_get_display_event_source(display));
    al_register_event_source(queue2, al_get_keyboard_event_source());
    al_register_event_source(queue2,al_get_timer_event_source(timer));

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

    while(!isEnd) {
        ALLEGRO_EVENT event = {0};
        al_wait_for_event(queue2, &event);

        switch (event.type) {//en fonction de son type (événement de souris,du clavier...),on agit
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                isEnd = 1;
                break;
            case ALLEGRO_EVENT_KEY_DOWN://Si on arrive ici, c'est qu'on a pioché un événement du clavier de type touche  enfoncée
                switch (event.keyboard.keycode) {//On vérifie de quelle touche il s'agit
                    case ALLEGRO_KEY_ESCAPE://on ne gère quel cas où la touche en foncée est ECHAP
                        isEnd = 1;
                        break;
                    case ALLEGRO_KEY_UP :
                        if (changeallowed == 1) {
                            if (player->direction != BAS && player->direction != HAUT) {
                                change_direction(player, HAUT);
                                if (player->next != NULL) {
                                    newchange = add_change_way(player, &lstchange);
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
                isEnd = update(player, lstchange, &pomme, bg_star, board, stormtrooper);
                al_flip_display();
                break;
        }
    }
    al_destroy_event_queue(queue2);
    al_destroy_timer(timer);
    al_destroy_bitmap(stormtrooper);
    size = size_snake(player, size);
    printf("Votre taille etait de %d\n", size);
    free_snake(player);

}