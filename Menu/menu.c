//
// Created by trist on 01/05/2023.
//
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <string.h>

#include "../Map/map.h"
#include <stdio.h>


#define WIDTH 1200
#define HEIGHT 600

#define WILOGO 50
#define HEILOGO 500


#include "../Map/character.h"


ALLEGRO_DISPLAY* setting(){
    assert(al_init());
    ALLEGRO_DISPLAY*display=NULL;
    display=al_create_display(WIDTH, HEIGHT);
    assert(display!=NULL);
    //Initialiser avec assert le reste
    assert(al_init_image_addon());
    assert(al_install_mouse());
    assert(al_init_primitives_addon());
    assert(al_install_keyboard());
    assert(al_install_audio());
    assert(al_init_acodec_addon());
    al_init_font_addon();
    assert(al_init_ttf_addon());
    al_set_window_title(display,"Title");
    al_set_window_position(display,200,100);
    al_flip_display();
    srand(time(NULL));
    return display;

}

void draw_select_character (ALLEGRO_BITMAP* bg, ALLEGRO_BITMAP* p1, ALLEGRO_BITMAP* p2, int pos) {
    al_draw_bitmap(bg, 0,0,0);
    al_draw_bitmap(p2, 200,150, 0);
    al_draw_bitmap(p1, 800,150, 0);
    if (pos == 0) {
        al_draw_filled_rectangle(0, 0, WIDTH / 2, HEIGHT, al_map_rgb(0, 0, 0));
    }
    else if (pos == 1) {
        al_draw_filled_rectangle(WIDTH/2, 0, WIDTH, HEIGHT, al_map_rgb(0,0,0));
    }
}


int select_character(ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* perso1, ALLEGRO_BITMAP* perso2) {
    int close = 0;
    int end = 0;

    int pos = -1;
    int dessiner = 0;
    ALLEGRO_BITMAP* background = al_load_bitmap("../Menu/lukevadorselect.jpg");


    ALLEGRO_TIMER* timer = al_create_timer(1/FPSMAP);
    al_start_timer(timer);
    assert(background!=NULL);
    assert(perso1!=NULL);
    assert(perso2!=NULL);

    ALLEGRO_EVENT_QUEUE*queue;
    queue = al_create_event_queue();
    assert(queue);

    al_register_event_source(queue,al_get_display_event_source(display));
    al_register_event_source(queue,al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_timer_event_source(timer));

    al_draw_bitmap(background, 0,0,0);
    al_draw_bitmap(perso2, 200,150, 0);
    al_draw_bitmap(perso1, 800,150, 0);
    al_flip_display();

    while(!end){
        ALLEGRO_EVENT event={0};
        al_wait_for_event(queue,&event);
        switch(event.type){
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                return 1;
            case ALLEGRO_EVENT_MOUSE_AXES :
                if (event.mouse.x > HEIGHT-100) {
                    if (pos != 0) {
                        pos = 0;
                        dessiner = 1;
                    }
                }
                else if (event.mouse.x < HEIGHT+100){
                    if (pos != 1) {
                        pos = 1;
                        dessiner = 1;
                    }
                }

                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN :
                if (pos == 1) {
                    return 0;
                }
                else if (pos == 0) {
                    return -1;
                }
                break;
            case ALLEGRO_EVENT_TIMER :
                if (dessiner == 1) {
                    al_map_rgb(0,0,0);
                    draw_select_character(background, perso1, perso2, pos);
                    dessiner = 0;
                    al_flip_display();
                }
        }
    }
}

int set_name(ALLEGRO_DISPLAY* display, ALLEGRO_FONT* police, Perso* player, int res, ALLEGRO_BITMAP* img, char* side) {
    int close = 0;
    int end = 0;
    int unichar;
    int lettre[MAXCH];
    int indice = 0;
    char* name;
    name = (char*) malloc(sizeof (char));
    name[indice] = '=';
    name[indice+1] = '\0';
    ALLEGRO_EVENT_QUEUE*queue;
    queue = al_create_event_queue();
    assert(queue);

    ALLEGRO_TIMER* timer = al_create_timer(1/60.0);
    al_start_timer(timer);
    assert(timer);

    al_register_event_source(queue,al_get_display_event_source(display));
    al_register_event_source(queue,al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_timer_event_source(timer));

    while (end == 0) {
        ALLEGRO_EVENT event={0};
        al_wait_for_event(queue,&event);
        switch(event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE :
                return 1;
            case ALLEGRO_EVENT_KEY_CHAR:
                unichar = event.keyboard.unichar;
                if ((unichar >= 32 && unichar <= 122) || unichar == 8) {
                    if (unichar == 8) {
                        if (indice >= 1) {
                            indice -=1;
                        }
                    }
                    else if(indice < 10) {
                        unichar = event.keyboard.unichar;
                        lettre[indice] = unichar;
                        indice +=1;
                    }
                    if (indice>=1) {
                        realloc(name,(indice+1)*sizeof(char));
                        name[indice] = '=';
                        name[indice+1] = '\0';
                    }
                    for(int i=0; i<indice; i++) {
                        name[i] = (char) lettre[i];
                    }
                }
                break;
            case ALLEGRO_EVENT_KEY_DOWN :
                switch(event.keyboard.keycode) {
                    case ALLEGRO_KEY_ENTER :
                        name[indice] = '\0';
                        strcpy(player->name, name);
                        return 0;
                }
                break;
            case ALLEGRO_EVENT_TIMER :
                al_clear_to_color(al_map_rgb(0,0,0));
                al_draw_bitmap(img, 50,50, 0);
                al_draw_text(police, al_map_rgb(255,239,56), 130, 70, 0,side);
                al_draw_text(police, al_map_rgb(255,239,56), WIDTH/4-100, HEIGHT/2, 0, "entrez votre nom : ");
                al_draw_text(police, al_map_rgb(255,239,56), WIDTH/2, HEIGHT/2, 0,  name);
                al_draw_text(police, al_map_rgb(255,239,56), WIDTH/3, HEIGHT/2+50, 0, "appuyez sur entree pour valider");
                al_flip_display();
        }
    }
}


void menu() {
    int res = 0;
    int isEnd=0;

    ALLEGRO_DISPLAY* display = setting();
    ALLEGRO_BITMAP* background = al_load_bitmap("../Menu/menubackground.jpg");
    ALLEGRO_BITMAP* logo = al_load_bitmap("../Menu/logogame.png");
    ALLEGRO_BITMAP* touch = al_load_bitmap("../Menu/logotouch2.png");
    ALLEGRO_BITMAP* perso1 = al_load_bitmap("../Menu/luke2.png");
    ALLEGRO_BITMAP* perso2 = al_load_bitmap("../Menu/Vador1.png");

    assert(background!=NULL);
    assert(logo!=NULL);
    assert(touch!=NULL);

    ALLEGRO_EVENT_QUEUE*queue;
    queue = al_create_event_queue();
    assert(queue);

    al_register_event_source(queue,al_get_display_event_source(display));
    al_register_event_source(queue, al_get_keyboard_event_source());

    ALLEGRO_SAMPLE* menusample = al_load_sample("../Menu/menumusic.wav"); //Extension .wav reconnu par acodec
    ALLEGRO_FONT* police = al_load_ttf_font("../Map/star_jedi/starjedi/Starjedi.ttf", 23, 0);

    assert(menusample!=NULL);
    al_reserve_samples(2);
    al_draw_bitmap(background, 0,0,0);
    al_draw_bitmap(logo, WILOGO, HEILOGO,0);
    al_draw_bitmap(touch, 50, 150,0);
    al_flip_display();
    al_play_sample(menusample, 1.0f, 0.0f, 1.0f, ALLEGRO_PLAYMODE_LOOP, 0);

    Perso player1;
    Perso player2;

    while(!isEnd){
        ALLEGRO_EVENT event={0};
        al_wait_for_event(queue,&event);
        switch(event.type){
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                isEnd=1;
                res = 1;
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                al_clear_to_color(al_map_rgb(0,0,0));
                res  = select_character(display, perso1, perso2);
                if (res != 1) {
                    if (res == 0) {
                        res = set_name(display, police, &player1, res, perso2, "joueur 1 du cote obscur");
                        player1.side = 1;
                        if (res == 1) {
                            isEnd = 1;
                        }
                        else {
                            res = set_name(display, police, &player2, res, perso1, "joueur 2 du cote lumineux");
                            player2.side = 0;
                        }
                    }
                    else if (res == -1) {
                        res = set_name(display, police, &player1, res, perso1, "joueur 1 du cote lumineux");
                        player1.side = 0;
                        if (res == 1) {
                            isEnd = 1;
                        }
                        else {
                            res = set_name(display, police, &player2, res, perso2, "joueur 2 du cote obscur");
                            player2.side = 0;
                        }
                    }
                }
                al_flush_event_queue(queue);
                break;
            }
        if (res == 1) {
            isEnd = 1;
        }
        else {
            al_destroy_sample(menusample);
            res = mapgame(display, player1, player2);
        }
        if (res == 1) {
            isEnd = 1;
        }
        }
    al_destroy_event_queue(queue);
}
