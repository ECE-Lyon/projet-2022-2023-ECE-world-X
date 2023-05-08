//
// Created by trist on 28/04/2023.
//

#include "dialog.h"
#include <stdio.h>
#include <string.h>
#include "constante.h"
#include "character.h"
#include "background.h"

#define TEXTSIZE 23
#define SIZEBOX 100
#define WITEXT 25
#define WIOUI 250
#define WINO 750
#define HEIOUINO HEIGHT-TEXTSIZE*2
#define SIZEBB8 20
#define BB8X1 WIOUI-SIZEBB8
#define BB8X2 WINO-SIZEBB8

ALLEGRO_FONT* init_font () {
    ALLEGRO_FONT* police = al_load_ttf_font("../Map/star_jedi/starjedi/Starjedi.ttf", TEXTSIZE, 0);
    if (police == NULL) {
        printf("Police doesn't load\n");

    }
    return police;

}

int anim_text(ALLEGRO_EVENT_QUEUE* queue, Choose bb8, ALLEGRO_FONT* police, Perso player, Background bar, int res) {
    int end = 0;
    ALLEGRO_TIMER *timer = al_create_timer(1 / FPSMAP);
    al_start_timer(timer);
    assert(queue);
    while (end == 0) {
        ALLEGRO_EVENT event = {0};
        al_wait_for_event(queue, &event);
        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE :
                end = 1;
                return -1;
            case ALLEGRO_EVENT_KEY_DOWN :
                switch (event.keyboard.keycode) {
                    case ALLEGRO_KEY_ESCAPE :
                        return 0;
                    case ALLEGRO_KEY_ENTER :
                        if (bb8.x == BB8X1) {
                            return res;
                        }
                        else if (bb8.x == BB8X2) {
                            return 0;
                        }
                        break;
                    case ALLEGRO_KEY_RIGHT :
                        bb8.x = BB8X2;
                        break;
                    case ALLEGRO_KEY_LEFT :
                        bb8.x = BB8X1;
                        break;
                }
                break;
            case ALLEGRO_EVENT_TIMER :
                al_clear_to_color(al_map_rgb(0, 0, 0));
                print_background(bar);
                print_character(player);
                choose_event_pnj(bb8, police, res);
                al_flip_display();
                break;
        }
    }
    al_destroy_timer(timer);
}


void choose_event_pnj (Choose bb8, ALLEGRO_FONT* police, int res) {
    switch (res) {
        case PECHE :
            set_text(bb8, police, "pêche au canard ?");
            break;
        case SNAKE :
            set_text(bb8, police, "snake ?");
            break;
        case SHIP :
            set_text(bb8, police, "vaisseau ?");
            break;
        case OSU :
            set_text(bb8, police, "musique ?");
            break;
        case TAPETAUPE :
            set_text(bb8, police, "tape taupe ?");
            break;
        case COURSE :
            set_text(bb8, police, "course ?");
            break;
        case BARMAN :
            set_text(bb8, police, "bonjour, que souhaites tu ?");
            break;
        case STAT :
            set_text(bb8, police, "moi c'est c3p0 souhaites tu accéder au statistiques ?");
            break;
    }
}
void init_bb8(Choose *bb8) {
    bb8->x = BB8X1;
    bb8->img =  al_load_bitmap("../Map/bb8.png");
}

void set_text(Choose bb8, ALLEGRO_FONT* police, char text[MAXCH]) {
    set_textbox();
    afficher_texte_dialog(police, text);
    set_yes_no(police, bb8);
}

void set_yes_no(ALLEGRO_FONT* police, Choose bb8) {
    al_draw_text(police, al_map_rgb(255,239,56), WIOUI, HEIOUINO, 0, "oui");
    al_draw_text(police, al_map_rgb(255,239,56), WINO, HEIOUINO, 0, "non");
    al_draw_bitmap(bb8.img, bb8.x, HEIOUINO, 0);

}

void set_textbox() {
    al_draw_filled_rectangle(0,HEIGHT-SIZEBOX, WIDTH, HEIGHT, al_map_rgb(0,0,0));
    al_draw_rectangle(0,HEIGHT-SIZEBOX, WIDTH, HEIGHT, al_map_rgb(255,255,255), 2);

}

void afficher_texte_dialog(ALLEGRO_FONT* police, char text[MAXCH]) {
    al_draw_text(police, al_map_rgb(255,239,56), WITEXT, HEIGHT-SIZEBOX, 0, text);
}


