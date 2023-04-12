//
// Created by trist on 04/04/2023.
//
#include "snake.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <stdlib.h>

#include "constante.h"

#define STARTSPEED 1
#define SIZESTART 3
#define STARTDIRECTION 2

void check_load_img(ALLEGRO_BITMAP* img) {
    if(img == NULL) {
        printf("Failed to load image\n");
    }
}

void init_snake(Body* player) {
    player->x = PLAYERX;
    player->y = PLAYERY;
    player->direction = STARTDIRECTION;
    player->next = NULL;
    player->img =  al_load_bitmap("../snakehead.png");
    check_load_img(player->img);
    player->next = NULL;
}

void debug_player(Body* p) {
    if (p == NULL) {
        return;
    }
    printf("x:%d, y:%d, next:%x direc:%d\n", p->x, p->y, p->next, p->direction);
}

void print_player (Body* player) {
    if (player == NULL) {
        return;
    }
    al_draw_bitmap(player->img, player->x, player->y, 0);
    //debug_player(player);
    al_flip_display();
    print_player(player->next);
}



int bordure(Body* player, Damier board) {
    switch (player->direction) {
        case HAUT :
            if (player->y-board.heightsquare < PLAYERY) {
                return 0;
            }
            break;
        case DROITE :
            if(player->x+board.widthsquare > WIGAME+STARTX) {
                return 0;
            }
            break;
        case BAS :
            if(player->y > HEIGAME) {
                return 0;
            }
            break;
        case GAUCHE :
            if(player->x-board.widthsquare < PLAYERX) {
                return 0;
            }
            break;
    }
    return 1;
}

void change_all_direction(Body* player, int direction) {
    if (player != NULL) {
        switch (direction) {
            case HAUT:
                player->direction = HAUT;
                break;
            case DROITE :
                player->direction= DROITE;
                break;
            case BAS:
                player->direction = BAS;
                break;
            case GAUCHE :
                player->direction = GAUCHE;
                break;
        }
        change_direction(player->next, direction);
        return;
    }
}


void move_player(Body* player, Damier board) {
    if (player != NULL) {
        switch (player->direction) {
            case HAUT:
                player->y -= board.heightsquare;
                break;
            case DROITE :
                player->x += board.widthsquare;
                break;
            case BAS:
                player->y += board.heightsquare;
                break;
            case GAUCHE :
                player->x -= board.widthsquare;
                break;
        }
        move_player(player->next, board);
        return;
    }

}

void add(Body* player, Damier board) {
    if (player->next == NULL) {
        player->next = malloc(sizeof(Body));
        switch (player->direction) {
            case HAUT :
                player->next->x = player->x;
                player->next->y = player->y-board.heightsquare;
                break;
            case DROITE :
                player->next->x = player->x-board.widthsquare;
                player->next->y = player->y;
                break;
            case BAS :
                player->next->x = player->x;
                player->next->y = player->y+board.heightsquare;
                break;
            case GAUCHE :
                player->next->x = player->x+board.widthsquare;
                player->next->y = player->y;
                break;
        }
        player->next->direction = player->direction;
        player->next->img = al_load_bitmap("../bodysnake.png");
        if(player->next->img == NULL) {
            printf("Image doesn't load\n");
        }
        player->next->next = NULL;
        debug_player(player->next);
        return;
    }
    add(player->next, board);

}

void free_snake(Body* player) {
    if (player != NULL) {
        free_snake(player->next);
    }
    free(player);
}

int check_food(Body* player, Food pomme) {
    if (player->x == pomme.x && player->y == pomme.y) {

        return 1;
    }
    return 0;
}


