//
// Created by trist on 28/04/2023.
//
#include "constante.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#ifndef PROJET_DIALOG_H
#define PROJET_DIALOG_H

enum{HINKS, JABBA, OBI, JAWA1, JAWA2, YODA, CHEWI, C3P0};

typedef struct {
    int x;
    ALLEGRO_BITMAP* img;
}Choose;

ALLEGRO_FONT* init_font ();
void init_bb8(Choose *bb8);
void set_textbox();
void afficher_texte_dialog(ALLEGRO_FONT* police, char text[MAXCH]);
void set_yes_no(ALLEGRO_FONT* police, Choose bb8);
void set_text(Choose bb8, ALLEGRO_FONT* police, char text[MAXCH]);
#endif //PROJET_DIALOG_H


