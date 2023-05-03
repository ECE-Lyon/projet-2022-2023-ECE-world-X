//
// Created by trist on 19/04/2023.
//
#include "character.h"
#include "constante.h"
#include "background.h"
#include "collision.h"
#include "dialog.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "../Snake/game.h"

void reset_keys(int Keys[NBKEYS]) {
    for(int i=0; i<NBKEYS; i++) {
        Keys[i] = 0;
    }
}

int mapgame(ALLEGRO_DISPLAY* display, Perso player1, Perso player2){
    int isEnd=0;
    int res = 0;
    int choosepnj = 0;

    ALLEGRO_EVENT_QUEUE*queue;
    printf("side : %d", player1.side);

    if (player1.side == 0) {
        init_Luke(&player1);
        init_vador(&player2);
    }
    else if (player1.side == 1) {
        init_vador(&player1);
        init_Luke(&player2);
    }
    Background bar;
    init_bg(&bar);

    int lst_collision[COLLISIONHEI][COLLISIONWI];
    load_file_collision(lst_collision);
    Mapcollision poscollision;
    update_map_pos(&poscollision, bar);

    ALLEGRO_FONT* police;
    police = init_font();
    Choose bb8;
    init_bb8(&bb8);


    ALLEGRO_SAMPLE *maintheme = al_load_sample("../Map/cantina.wav");

    //al_reserve_samples(1);
    if (maintheme == NULL) {
        printf("Music doesn't load");
    }
    else {
        al_play_sample(maintheme, 1.0f, 0.0f, 1.0f, ALLEGRO_PLAYMODE_LOOP, 0);
    }
    //Créer un timer si nécéssaire
    ALLEGRO_TIMER*timer=al_create_timer(1/FPS);
    al_start_timer(timer);
    queue=al_create_event_queue();
    assert(queue);


    //Ajouter tous les types d'événements souhaités
    al_register_event_source(queue,al_get_display_event_source(display));
    al_register_event_source(queue,al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_keyboard_event_source());

    int Keys[NBKEYS] = {0};

    while(!isEnd){
        ALLEGRO_EVENT event={0};
        al_wait_for_event(queue,&event);//on pioche un événement dès qu'il y en a un
        switch(event.type) {//en fonction de son type (événement de souris,du clavier...),on agit
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                isEnd = 1;
                return 1;
            case ALLEGRO_EVENT_KEY_DOWN://Si on arrive ici, c'est qu'on a pioché un événement du clavier de type touche  enfoncée
                switch (event.keyboard.keycode) {//On vérifie de quelle touche il s'agit
                    case ALLEGRO_KEY_UP :
                        reset_keys(Keys);
                        player1.direction = T1;
                        Keys[HAUT] = 1;
                        break;
                    case ALLEGRO_KEY_LEFT :
                        reset_keys(Keys);
                        Keys[GAUCHE] = 1;
                        player1.direction = L1;
                        break;
                    case ALLEGRO_KEY_RIGHT :
                        reset_keys(Keys);
                        Keys[DROITE] = 1;
                        player1.direction = R1;
                        break;
                    case ALLEGRO_KEY_DOWN :
                        reset_keys(Keys);
                        Keys[BAS] = 1;
                        player1.direction = B1;
                        break;
                    case ALLEGRO_KEY_ENTER :
                        Keys[ENTER] = 1;
                        break;
                }
                break;
            case ALLEGRO_EVENT_KEY_UP :
                switch (event.keyboard.keycode) {//On vérifie de quelle touche il s'agit
                    case ALLEGRO_KEY_UP :
                        if (Keys[HAUT] == 1) {
                            Keys[HAUT] = 0;
                            player1.img = player1.anim[T1];
                        }
                        break;
                    case ALLEGRO_KEY_LEFT :
                        if (Keys[GAUCHE] == 1) {
                            Keys[GAUCHE] = 0;
                            player1.img = player1.anim[L1];
                            break;
                        }
                    case ALLEGRO_KEY_RIGHT :
                        if (Keys[DROITE] == 1) {
                            Keys[DROITE] = 0;
                            player1.img = player1.anim[R1];
                            break;
                        }
                    case ALLEGRO_KEY_DOWN :
                        if (Keys[BAS] == 1) {
                            Keys[BAS] = 0;
                            player1.img = player1.anim[B1];
                            break;
                        }
                    case ALLEGRO_KEY_ENTER :
                        Keys[ENTER] = 0;
                        break;
                }
                break;
            case ALLEGRO_EVENT_TIMER :
                if (check_collision(player1, poscollision, lst_collision, Keys) == 0) {
                        choosepnj = check_eventmap(player1,poscollision,&bar, lst_collision, Keys);
                        al_clear_to_color(al_map_rgb(0,0,0));
                        print_background(bar);
                        if (al_get_timer_count(timer)%3 == 0) {
                            animation(&player1, Keys);
                            //printf("x:%d y:%d\n", bar.x, bar.y);
                        }
                        update_map_pos(&poscollision, bar);
                        //printf("x:%d, y:%d\n", poscollision.posmapx, poscollision.posmapy);
                        move_bg(&bar, Keys);
                        print_character(player1);
                    if (choosepnj !=0) {
                        res = anim_text(queue, bb8, police, player1, bar, choosepnj);
                        Keys[ENTER] = 0;
                    }
                    switch (res) {
                        case -1 :
                            isEnd = 1;
                            break;
                        case PECHE :
                            printf("Peche\n");
                            //Lancer la peche au canard
                            break;
                        case SNAKE :
                            game(display);
                            al_flush_event_queue(queue);
                            //Lancer le snake
                            break;
                        case SHIP :
                            printf("Vaisseau\n");
                            break;
                        case OSU :
                            printf("Osu\n");
                            break;
                        case TAPETAUPE :
                            printf("Tape taupe\n");
                            break;
                        case COURSE :
                            printf("Course\n");
                            break;
                        case BARMAN :
                            //Donner les tickets / expliquer le jeu
                            printf("ticket/regles\n");
                            break;
                        case STAT :
                            printf("Stat\n");
                            break;
                    }
                    res = 0;
                    al_flip_display();
                    break;
                }

        }
    }
    al_destroy_event_queue(queue);
    return 0;
}

