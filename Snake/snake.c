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
#include "../Map/constante.h"


#define STARTSPEED 1
#define SIZESTART 3
#define STARTDIRECTION 2

void check_load_img(ALLEGRO_BITMAP* img) {
    if(img == NULL) {
        printf("Failed to load image\n");
    }
}

void init_image(Body* player) {
    player->img[HAUT] = al_load_bitmap("../Snake/vadorh.png");
    player->img[DROITE] =  al_load_bitmap("../Snake/vadorr.png");
    player->img[BAS] =  al_load_bitmap("../Snake/vadorb.png");
    player->img[GAUCHE] =  al_load_bitmap("../Snake/vadorl.png");
    for(int i =0; i<NBHEAD; i++) {
        check_load_img(player->img[i]);
    }

}

void init_snake(Body* player) {
    player->x = PLAYERX;
    player->y = PLAYERY;
    player->direction = STARTDIRECTION;
    player->next = NULL;
    init_image(player);
    player->nextchange = NULL;
    player->next = NULL;
}

int size_snake(Body* player, int size) {
    if (player->next == NULL) {
        return size;
    }
    size+=1;
    size_snake(player->next, size);
}

void debug_player(Body* p) {
    if (p == NULL) {
        return;
    }
    printf("x:%d, y:%d, next:%x direc:%d\n", p->x, p->y, p->next, p->direction);
}

void debuglst (Waychange *l) {
    if (l == NULL) {
        return;
    }
    printf("x:%d, y:%d, next:%x direc:%d\n", l->x, l->y, l->next, l->direction);
}

void print_body(Body* player) {
    if(player == NULL) {
        return;
    }
    al_draw_bitmap(player->img[0], player->x, player->y, 0);
    print_body(player->next);
}

void print_player (Body* player) {
    if (player == NULL) {
        return;
    }
    al_draw_bitmap(player->img[player->direction], player->x, player->y, 0);
    //debug_player(player);
    print_body(player->next);
}



int bordure(Body* player, Damier board) {
    switch (player->direction) {
        case HAUT :
            if (player->y-board.heightsquare < PLAYERY) {
                return 0;
            }
            break;
        case DROITE :
            if(player->x+board.widthsquare >= WIGAME+STARTX) {
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


Waychange* add_change_way(Body* player, Waychange** lstchange) {
    if (*lstchange == NULL) {
        (*lstchange) = malloc(sizeof(Waychange));
        (*lstchange)->x = player->x;
        (*lstchange)->y = player->y;
        (*lstchange)->direction = player->direction;
        (*lstchange)->next = NULL;
        return *lstchange;
    }
    add_change_way(player, &(*lstchange)->next);
}

void change_direction(Body* player, int direction) {
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
    }
}

void set_change(Body* player, Waychange* newchange) {
    while(player->nextchange==NULL){
            player->nextchange = newchange;
            if (player->next == NULL) {
                return;
            }
            player = player->next;
    }
}


void move_body(Body* player, Damier board) {
    if (player != NULL) {
        move_player(player, board);
        if (player->nextchange != NULL) {
            if ((player->x == player->nextchange->x) && (player->y == player->nextchange->y)) {
                player->direction = player->nextchange->direction;
                player->nextchange = player->nextchange->next;
            }
        }
        move_body(player->next, board);
    }
}

void add_body(Body* player, Waychange* lstchange, Damier board, ALLEGRO_BITMAP* stormtrooper) {
    if (player->next == NULL) {
        player->next = malloc(sizeof(Body));
        switch (player->direction) {
            case HAUT :
                player->next->x = player->x;
                player->next->y = player->y+board.heightsquare;
                break;
            case DROITE :
                player->next->x = player->x-board.widthsquare;
                player->next->y = player->y;
                break;
            case BAS :
                player->next->x = player->x;
                player->next->y = player->y-board.heightsquare;
                break;
            case GAUCHE :
                player->next->x = player->x+board.widthsquare;
                player->next->y = player->y;
                break;
        }
        player->next->direction = player->direction;
        player->next->nextchange = player->nextchange;
        player->next->img[0] = stormtrooper;
        player->next->next = NULL;
        return;
    }
    add_body(player->next, lstchange, board, stormtrooper);
}

int check_body_collision(Body* playerhead, Body* playerbody) {
    if(playerbody == NULL) {
        return 0;
    }
    else if (playerhead->x == playerbody->x && playerhead->y == playerbody->y) {
        return 1;
    }
    check_body_collision(playerhead, playerbody->next);
}

void free_snake(Body* player) {
    if (player != NULL) {
        free_snake(player->next);
    }
    free(player);
}

int check_food(Body* player, Food pomme, int *size) {
    if (player->x == pomme.x && player->y == pomme.y) {
        *size += 1;
        return 1;
    }
    return 0;
}


