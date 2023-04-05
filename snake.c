//
// Created by trist on 04/04/2023.
//
#include "snake.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>

#include "constante.h"

#define STARTSPEED 2
#define SIZESTART 3
#define STARTDIRECTION 2

void check_load_img(ALLEGRO_BITMAP* img) {
    if(img == NULL) {
        printf("Failed to load image\n");
    }
}

void init_snake(Body* player) {
    player->x = STARTX;
    player->y = STARTY;
    player->speed = STARTSPEED;
    player->direction = STARTDIRECTION;
    player->next = NULL;
    player->img = al_load_bitmap("/Users/trist/OneDrive/Documents/CoursECE/CLionProjects/projet2minijeux/snake/snakehead.png");
    check_load_img(player->img);
}

void print_player (Body player) {
    al_draw_bitmap(player.img, player.x, player.y, 0);
    al_flip_display();
}

void move_player(Body* player) {
    switch (player->direction) {
        case 0:
            player->y -= player->speed;
            break;
        case 1 :
            player->x += player->speed;
            break;
        case 2 :
            player->y += player->speed;
            break;
        case 3 :
            player->x -= player->speed;
            break;
    }
}


