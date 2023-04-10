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
#include "miam.h"

#define STARTSPEED 1
#define SIZESTART 3
#define STARTDIRECTION 2

void check_load_img(ALLEGRO_BITMAP* img) {
    if(img == NULL) {
        printf("Failed to load image\n");
    }
}

void init_snake(Body* player) {
    enum {HAUT, DROITE, BAS, GAUCE};
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
    debug_player(player);
    al_flip_display();
    print_player(player->next);
}



int bordure(Body* player, int wi, int hei) {
    enum{HAUT, DROITE, BAS, GAUCHE};
    switch (player->direction) {
        case HAUT :
            if (player->y-hei < PLAYERY) {
                return 0;
            }
            break;
        case DROITE :
            if(player->x+wi > WIGAME+STARTX) {
                return 0;
            }
            break;
        case BAS :
            if(player->y > HEIGAME) {
                return 0;
            }
            break;
        case GAUCHE :
            if(player->x-wi < PLAYERX) {
                return 0;
            }
            break;
    }
    return 1;
}


void move_player(Body* player, int wi, int hei) {
    enum{HAUT,DROITE,BAS, GAUCHE};
    if (player != NULL) {
        switch (player->direction) {
            case HAUT:
                player->y -= hei;
                break;
            case DROITE :
                player->x += wi;
                break;
            case BAS:
                player->y += hei;
                break;
            case GAUCHE :
                player->x -= wi;
                break;
        }
        move_player(player->next, wi, hei);
        return;
    }

}

void add(Body* player, int wisquare, int heisquare) {
    enum{HAUT, DROITE, BAS, GAUCHE};
    if (player->next == NULL) {
        printf("J'ajoute\n");
        player->next = malloc(sizeof(Body));
        switch (player->direction) {
            case HAUT :
                player->next->x = player->x;
                player->next->y = player->y-heisquare;
                break;
            case DROITE :
                player->next->x = player->x-wisquare;
                player->next->y = player->y;
                break;
            case BAS :
                player->next->x = player->x;
                player->next->y = player->y+heisquare;
                break;
            case GAUCHE :
                player->next->x = player->x+wisquare;
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
    add(player->next, wisquare, heisquare);

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


