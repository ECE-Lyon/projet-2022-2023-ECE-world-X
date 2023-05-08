//
// Created by trist on 23/04/2023.
//

#include "background.h"
#include "constante.h"
#include "character.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>


#include <stdio.h>

void init_bg (Background* bar) {
    bar->x = BGX;
    bar->y = BGY;
    bar->img = al_load_bitmap("../Map/mapv2large.png");
    if (bar->img == NULL) {
        printf("Failed to load Background\n");
    }
}

void print_background(Background bar) {
    al_draw_bitmap(bar.img, bar.x, bar.y, 0);
}

void move_bg(Background* bar, int Keys[NBKEYS]) {
    bar->x -= SPEEDBG*Keys[DROITE];
    bar->x += SPEEDBG*Keys[GAUCHE];
    bar->y += SPEEDBG*Keys[HAUT];
    bar->y -= SPEEDBG*Keys[BAS];
}

void square_ticket (ALLEGRO_FONT* police, Perso player1, Perso player2, ALLEGRO_BITMAP* ticket) {
    al_draw_filled_rectangle(800, 0, 1000, 50, al_map_rgb(0,0,0));
    al_draw_rectangle(800, 0, 1000, 50, al_map_rgb(255,255,255), 1);
    al_draw_filled_rectangle(1000, 0, 1200, 50, al_map_rgb(0,0,0));
    al_draw_rectangle(1000, 0, 1200, 50, al_map_rgb(255,255,255), 1);
    al_draw_textf(police, al_map_rgb(255,236,59), 810, 10,0, "%s", player1.name);
    al_draw_textf(police, al_map_rgb(255,236,59), 1010, 10,0, "%s", player2.name);
    al_draw_textf(police, al_map_rgb(255,236,59), 980, 10,0, "%d", player1.ticket);
    al_draw_textf(police, al_map_rgb(255,236,59), 1180, 10,0, "%d", player2.ticket);
    al_draw_bitmap(ticket, 950, 18,0);
    al_draw_bitmap(ticket, 1150, 18,0);

}