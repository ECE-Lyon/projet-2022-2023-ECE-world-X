//
// Created by trist on 04/04/2023.
//
#include "snake.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>

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
    player->img =  al_load_bitmap("/Users/trist/OneDrive/Documents/CoursECE/CLionProjects/projet2minijeux/projet-2022-2023-ECE-world-X/snakehead.png");
    check_load_img(player->img);
}

void print_player (Body player) {
    al_draw_bitmap(player.img, player.x, player.y, 0);
    al_flip_display();
}

int bordure(Body player, int wi, int hei) {
    enum{HAUT, DROITE, BAS, GAUCHE};
    switch (player.direction) {
        case HAUT :
            if (player.y-hei < PLAYERY) {
                return 0;
            }
            break;
        case DROITE :
            if(player.x+wi > WIGAME+STARTX) {
                return 0;
            }
            break;
        case BAS :
            if(player.y > HEIGAME) {
                return 0;
            }
            break;
        case GAUCHE :
            if(player.x-wi < PLAYERX) {
                return 0;
            }
            break;
    }
    return 1;
}


void move_player(Body* player, int wi, int hei) {
    enum{HAUT,DROITE,BAS, GAUCHE};
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
}

int check_food(Body player, Food pomme) {
    if (player.x == pomme.x && player.y == pomme.y) {
        return 1;
    }
    return 0;
}


