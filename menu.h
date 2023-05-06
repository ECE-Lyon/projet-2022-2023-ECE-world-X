//
// Created by benja on 27/04/2023.
//

#ifndef OSU_MENU_H
#define OSU_MENU_H

#include <stdbool.h>
#include <allegro5/allegro_font.h>

typedef struct {
    char *text;
    bool selected;
} MenuItem;


int inTheMenu(ALLEGRO_FONT *font, ALLEGRO_EVENT_QUEUE *queue, int selectedItem, ALLEGRO_DISPLAY *display);

void beginning(ALLEGRO_FONT *font, ALLEGRO_EVENT_QUEUE *queue, ALLEGRO_DISPLAY *display, const char *name);

#endif //OSU_MENU_H
