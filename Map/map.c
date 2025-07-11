//
// Created by trist on 19/04/2023.
//
#include "character.h"
#include "constante.h"
#include "background.h"
#include "collision.h"
#include "dialog.h"
#include "savescore.h"

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
#include "../JarJar/duckGame.h"
#include "../Ships/Start_and_images.h"
#include "../osu/osugame.h"
#include "../Jackpot/Roll_and_handle.h"



void reset_keys(int Keys[NBKEYS]) {
    for(int i=0; i<NBKEYS; i++) {
        Keys[i] = 0;
    }
}

int score_comparaison(Perso* player1, Perso* player2) {
    if (player1->score > player2->score) {
        player2->ticket -= 1;
    }
    else if (player2->score > player1->score) {
        player1->ticket -= 1;
    }
    else if (player1->score == player2->score) {
        player1->ticket -=1;
        player2->ticket -= 1;
    }
}

int check_win(Perso player1, Perso player2) {
    if (player1.ticket == 0 && player2.ticket == 0) {
        return 3;
    }
    else if (player1.ticket == 0) {
        return 1;
    }
    else if (player2.ticket == 0) {
        return 2;
    }
    return 0;
}

void endgame (ALLEGRO_FONT* police, Perso player1, Perso player2, int *isEnd) {
    int res = check_win(player1, player2);
    if (res != 0) {
        *isEnd = 1;
        if (res == 1) {
            al_clear_to_color(al_map_rgb(0,0,0));
            al_draw_textf(police, al_map_rgb(255,239,59), 450, 300, 0, "%s a gagné la partie !!!", player2.name);
        }
        else if (res == 2) {
            al_clear_to_color(al_map_rgb(0,0,0));
            al_draw_textf(police, al_map_rgb(255,239,59), 450, 300, 0, "%s a gagné la partie !!!", player1.name);
        }
        else if (res == 3) {
            al_clear_to_color(al_map_rgb(0,0,0));
            al_draw_text(police, al_map_rgb(255,239,59), 450, 300, 0, "Il n'y a pas de gagnant....");
        }
        al_flip_display();
        al_rest(3);
    }
}

void textrules(ALLEGRO_FONT* police) {
    set_large_textbox();
    al_draw_text(police, al_map_rgb(255, 239, 56), 10, 10, 0, "bonjour bienvenue dans la cantina !");
    al_draw_text(police, al_map_rgb(255, 239, 56), 10, 30, 0,
                 "ici tu pourras trouver toutes sortes de mini jeux jouable à deux joueurs");
    al_draw_text(police, al_map_rgb(255, 239, 56), 10, 50, 0,
                 "tu as un nombre limité de tickets une défaite te fait perdre un ticket ");
    al_draw_text(police, al_map_rgb(255, 239, 56), 10, 70, 0, "alors qu'une victoire ne t'en fait perdre aucun");
    al_draw_text(police, al_map_rgb(255, 239, 56), 10, 90, 0, "le perdant est celui qui n'a plus de ticket");
    al_draw_text(police, al_map_rgb(255, 239, 56), 10, 110, 0,
                 "toute les interactions sur la map se font avec la touche entrée");
    al_draw_text(police, al_map_rgb(255, 239, 56), 10, 150, 0, "appuyez sur la touche entrée pour quitter...");
    al_flip_display();
}

void textscore(ALLEGRO_FONT* police, int score[NBGAME]) {
    set_large_textbox();
    al_draw_text(police, al_map_rgb(255, 239, 56), 20, 10, 0, "voici les meilleurs scores sur chaque jeux :");
    al_draw_textf(police, al_map_rgb(255, 239, 56), 20, 50, 0,
                 "snake : %d", score[0]);
    al_draw_textf(police, al_map_rgb(255, 239, 56), 20, 90, 0,
                 "osu : %d ", score[1]);
    al_draw_textf(police, al_map_rgb(255, 239, 56), 20, 130, 0, "peche au canard :  %d", score[2]);
    al_draw_textf(police, al_map_rgb(255, 239, 56), 20, 170, 0, "vaisseaux : %d", score[3]);
    al_draw_text(police, al_map_rgb(255, 239, 56), 20, 210, 0, "appuyez sur la touche entrée pour quitter...");
    al_flip_display();


}

int rulesscore(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_FONT* police, int choose, int score[NBGAME]) {
    int end = 0;
    if (choose == 0) {
        textrules(police);
    }
    else if(choose == 1) {
        textscore(police, score);
    }

    while (end == 0) {
        ALLEGRO_EVENT event = {0};
        al_wait_for_event(queue, &event);
        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE :
                return 1;
            case ALLEGRO_EVENT_KEY_DOWN :
                switch (event.keyboard.keycode) {
                    case ALLEGRO_KEY_ENTER :
                        end = 1;
                        break;
                }
                break;
        }
    }
}


int mapgame(ALLEGRO_DISPLAY* display, Perso player1, Perso player2){
    int isEnd=0;
    int res = 0;
    int choosepnj = 0;

    ALLEGRO_EVENT_QUEUE*queue;

    if (player1.side == 0) {
        init_Luke(&player1);
        init_vador(&player2);
    }
    else if (player1.side == 1) {
        init_vador(&player1);
        init_Luke(&player2);
    }
    Perso* playeractive = &player1;
    Perso* otherplayer = &player2;

    Background bar;
    init_bg(&bar);

    int lst_collision[COLLISIONHEI][COLLISIONWI];
    int score[NBGAME];
    readscore(score);
    load_file_collision(lst_collision);
    Mapcollision poscollision;
    update_map_pos(&poscollision, bar);

    ALLEGRO_FONT* police;
    police = init_font();
    Choose bb8;
    init_bb8(&bb8);

    Game jeuxCoin;

    ALLEGRO_SAMPLE *maintheme = al_load_sample("../Map/cantina.wav");
    if (maintheme == NULL) {
        printf("Music doesn't load");
    }
    else {
        al_play_sample(maintheme, 1.0f, 0.0f, 1.0f, ALLEGRO_PLAYMODE_LOOP, 0);
    }
    ALLEGRO_TIMER*timer=al_create_timer(1/FPSMAP);
    al_start_timer(timer);
    queue=al_create_event_queue();
    assert(queue);

    ALLEGRO_BITMAP* ticket = al_load_bitmap("../Map/money.png");

    al_register_event_source(queue,al_get_display_event_source(display));
    al_register_event_source(queue,al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_keyboard_event_source());

    int Keys[NBKEYS] = {0};

    while(isEnd == 0){
        ALLEGRO_EVENT event={0};
        al_wait_for_event(queue,&event);
        switch(event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                isEnd = 1;
                return 1;
            case ALLEGRO_EVENT_KEY_DOWN:
                switch (event.keyboard.keycode) {
                    case ALLEGRO_KEY_UP :
                        reset_keys(Keys);
                        playeractive->direction = T1;
                        Keys[HAUT] = 1;
                        break;
                    case ALLEGRO_KEY_LEFT :
                        reset_keys(Keys);
                        Keys[GAUCHE] = 1;
                        playeractive->direction = L1;
                        break;
                    case ALLEGRO_KEY_RIGHT :
                        reset_keys(Keys);
                        Keys[DROITE] = 1;
                        playeractive->direction = R1;
                        break;
                    case ALLEGRO_KEY_DOWN :
                        reset_keys(Keys);
                        Keys[BAS] = 1;
                        playeractive->direction = B1;
                        break;
                    case ALLEGRO_KEY_ENTER :
                        Keys[ENTER] = 1;
                        break;
                }
                break;
            case ALLEGRO_EVENT_KEY_UP :
                switch (event.keyboard.keycode) {
                    case ALLEGRO_KEY_UP :
                        if (Keys[HAUT] == 1) {
                            Keys[HAUT] = 0;
                            playeractive->img = playeractive->anim[T1];
                        }
                        break;
                    case ALLEGRO_KEY_LEFT :
                        if (Keys[GAUCHE] == 1) {
                            Keys[GAUCHE] = 0;
                            playeractive->img = playeractive->anim[L1];
                            break;
                        }
                    case ALLEGRO_KEY_RIGHT :
                        if (Keys[DROITE] == 1) {
                            Keys[DROITE] = 0;
                            playeractive->img = playeractive->anim[R1];
                            break;
                        }
                    case ALLEGRO_KEY_DOWN :
                        if (Keys[BAS] == 1) {
                            Keys[BAS] = 0;
                            playeractive->img = playeractive->anim[B1];
                            break;
                        }
                    case ALLEGRO_KEY_ENTER :
                        Keys[ENTER] = 0;
                        break;
                }
                break;
            case ALLEGRO_EVENT_TIMER :
                if (check_collision(*playeractive, poscollision, lst_collision, Keys) == 0) {
                        choosepnj = check_eventmap(*playeractive, poscollision, &bar, lst_collision, Keys);
                        al_clear_to_color(al_map_rgb(0,0,0));
                        print_background(bar);
                        square_ticket(police, player1, player2, ticket);
                        if (al_get_timer_count(timer)%3 == 0) {
                            animation(playeractive, Keys);
                        }
                        update_map_pos(&poscollision, bar);
                        move_bg(&bar, Keys);
                        print_character(*playeractive);
                    if (choosepnj !=0) {
                        res = anim_text(queue, bb8, police, *playeractive, bar, choosepnj);
                        Keys[ENTER] = 0;
                    }
                    switch (res) {
                        case -1 :
                            isEnd = 1;
                            break;
                        case PECHE :
                            al_destroy_sample(maintheme);
                            init_lauchGame(&jeuxCoin, display);
                            launchGame(&jeuxCoin, playeractive);
                            al_flush_event_queue(queue);
                            init_lauchGame(&jeuxCoin, display);
                            launchGame(&jeuxCoin, otherplayer);
                            al_flush_event_queue(queue);
                            score_comparaison(&player1, &player2);
                            if (player1.score > score[2]) {
                                score[2] = player1.score;
                                writescore(score);
                            }
                            else if (player2.score > score[2]) {
                                score[2] = player2.score;
                                writescore(score);
                            }
                            break;
                        case SNAKE :
                            al_destroy_sample(maintheme);
                            gamesnake(display, playeractive, police);
                            al_flush_event_queue(queue);
                            gamesnake(display, otherplayer, police);
                            al_flush_event_queue(queue);
                            score_comparaison(&player1, &player2);
                            if (player1.score > score[0]) {
                                score[0] = player1.score;
                                writescore(score);
                            }
                            else if (player2.score > score[0]) {
                                score[0] = player2.score;
                                writescore(score);
                            }
                            break;
                        case SHIP :
                            al_destroy_sample(maintheme);
                            game_ships(display,playeractive, otherplayer);
                            al_flush_event_queue(queue);
                            if (player1.score < score[3]) {
                                score[3] = player1.score;
                                writescore(score);
                            }
                            else if (player2.score < score[3]) {
                                score[3] = player2.score;
                                writescore(score);
                            }
                            al_show_mouse_cursor(display);
                            break;
                        case OSU :
                            al_destroy_sample(maintheme);
                            osuGame(display, playeractive);
                            al_flush_event_queue(queue);
                            osuGame(display, otherplayer);
                            score_comparaison(&player1, &player2);
                            if (player1.score > score[1]) {
                                score[1] = player1.score;
                                writescore(score);
                            }
                            else if (player2.score > score[1]) {
                                score[1] = player2.score;
                                writescore(score);
                            }
                            al_show_mouse_cursor(display);
                            break;
                        case TAPETAUPE:
                            game_jackpot(display);
                            res = 0;
                            break;
                        case COURSE :
                            res = 0;
                            break;
                        case BARMAN :
                            rulesscore(queue, police, 0, score);
                            al_flush_event_queue(queue);
                            res = 0;
                            break;
                        case STAT :
                            readscore(score);
                            rulesscore(queue, police, 1, score);
                            res = 0;
                            break;
                    }
                    if (res !=0) {
                        maintheme = al_load_sample("../Map/cantina.wav");
                        if (playeractive == &player1) {
                            playeractive = &player2;
                            otherplayer = &player1;
                        }
                        else{
                            playeractive = &player1;
                            otherplayer = &player2;
                        }
                        if (maintheme == NULL) {
                            printf("Music doesn't load");
                        }
                        else {
                            al_play_sample(maintheme, 1.0f, 0.0f, 1.0f, ALLEGRO_PLAYMODE_LOOP, 0);
                        }
                        endgame(police, player1, player2, &isEnd);
                    }
                    res = 0;
                    al_flip_display();
                    break;
                }
        }
    }
    al_destroy_sample(maintheme);
    al_destroy_bitmap(ticket);
    al_destroy_event_queue(queue);
    return 1;
}

