//
// Created by trist on 28/04/2023.
//

#include "dialog.h"
#include <stdio.h>
#include <string.h>
#include "constante.h"
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


