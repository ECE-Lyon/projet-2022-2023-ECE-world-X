//
// Created by trist on 28/04/2023.
//
#include "constante.h"
#include "character.h"
#include "background.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#ifndef PROJET_DIALOG_H
#define PROJET_DIALOG_H


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
void choose_event_pnj (Choose bb8, ALLEGRO_FONT* police, int res);
int anim_text(ALLEGRO_EVENT_QUEUE* queue, Choose bb8, ALLEGRO_FONT* police, Perso player, Background bar, int res);
void set_large_textbox();

#endif //PROJET_DIALOG_H


