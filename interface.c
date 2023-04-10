//
// Created by trist on 04/04/2023.
//
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>

#include "constante.h"
#include "interface.h"
#include "snake.h"

#define SIZESTAR 2


void create_map(int width, int height) {
    int x, y;
    int indice = 0;
    x = STARTX;
    y = STARTY;

    for(int i = 0; i<NBSQUARE; i++) {
        for(int j = 0; j<NBSQUARE; j++) {
            switch (indice) {
                case 0 :
                    al_draw_filled_rectangle(x, y, x+width, y+height, al_map_rgb(96,96,96));
                    indice = 1;
                    break;
                case 1 :
                    al_draw_filled_rectangle(x, y, x+width, y+height, al_map_rgb(113,106,105));
                    indice = 0;
                    break;
            }
            x += width;
        }
        y+=height;
        x=STARTX;
    }
    al_flip_display();
}

void drawstars(int cx, int cy) {
    al_draw_filled_circle(cx, cy, SIZESTAR, al_map_rgb(255,255,255));
    al_draw_filled_circle(cx-SIZESTAR ,cy-SIZESTAR, SIZESTAR, al_map_rgb(0,0,0));
    al_draw_filled_circle(cx+SIZESTAR ,cy-SIZESTAR, SIZESTAR, al_map_rgb(0,0,0));
    al_draw_filled_circle(cx-SIZESTAR ,cy+SIZESTAR, SIZESTAR, al_map_rgb(0,0,0));
    al_draw_filled_circle(cx+SIZESTAR ,cy+SIZESTAR, SIZESTAR,al_map_rgb(0,0,0));
}

void create_star_list(star bg_star[NBSTAR]) {
    int cx, cy;
    for(int i=0; i<NBSTAR; i++) {
        cx = rand()%WIDTH;
        cy = rand()%HEIGHT;
        bg_star[i].x = cx;
        bg_star[i].y = cy;
    }
}

void print_all_stars(star bg_star[NBSTAR]) {
    for(int i=0; i<NBSTAR; i++) {
        drawstars(bg_star[i].x, bg_star[i].y);
    }
}

void update(Body* player, Food* pomme, star bg_star[NBSTAR], int width, int height) {
    int res;
    al_clear_to_color(al_map_rgb(0, 0, 0));
    print_all_stars(bg_star);
    create_map(width, height);
    res = bordure(player, width, height);
    if (res == 1) {
        move_player(player, width, height);
    }
    print_player(player);
    res = check_food(player, *pomme);
    if (res == 1) {
        coord(pomme, width, height);
        add(player, width, height);
    }
    print_apple(*pomme);

}