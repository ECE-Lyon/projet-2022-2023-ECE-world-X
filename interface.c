//
// Created by trist on 04/04/2023.
//
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>

#include "constante.h"
#include "interface.h"
#include "snake.h"
#include "plateau.h"

#define SIZESTAR 2


void create_map(Damier board) {
    int x, y;
    int indice = 0;
    x = STARTX;
    y = STARTY;

    for(int i = 0; i<NBSQUARE; i++) {
        for(int j = 0; j<NBSQUARE; j++) {
            switch (indice) {
                case 0 :
                    al_draw_filled_rectangle(x, y, x+board.widthsquare, y+board.heightsquare, al_map_rgb(96,96,96));
                    indice = 1;
                    break;
                case 1 :
                    al_draw_filled_rectangle(x, y, x+board.widthsquare, y+board.heightsquare, al_map_rgb(113,106,105));
                    indice = 0;
                    break;
            }
            x += board.widthsquare;
        }
        y+=board.heightsquare;
        x=STARTX;
    }
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

int collision_apple(Body* player, int coordx, int coordy) {
    if(player == NULL) {
        return 0;
    }
    if (coordx == player->x && coordy == player->y) {
        return 1;
    }
    collision_apple(player->next, coordx, coordy);
}

int update(Body* player,Waychange* lstchange, Food* pomme, star bg_star[NBSTAR], Damier board) {
    int res, collision = 0;

    al_clear_to_color(al_map_rgb(0, 0, 0));
    print_all_stars(bg_star);
    create_map(board);
    res = bordure(player, board);
    if (res == 1) {
        move_player(player, board);
        move_body(player->next, board);
    }
    else {
        return 1;
    }
    print_player(player);
    res = check_food(player, *pomme);
    if (res == 1) {
        do {
            coord(pomme, board);
        }while(collision_apple(player, pomme->x, pomme->y)==1);
        add_body(player, lstchange, board);
    }
    if (player->next != NULL) {
        collision = check_body_collision(player, player->next);
    }
    if (collision == 1) {
        return 1;
    }
    print_apple(*pomme);

}