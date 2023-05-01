#ifndef PROJET_ECE_WORLD_TURRET_AND_TIMER_H
#define PROJET_ECE_WORLD_TURRET_AND_TIMER_H

#include "Ship.h"
#include "Player_crosshair.h"

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

typedef struct {
    int score;
    ALLEGRO_BITMAP *turretdisplay;
    ALLEGRO_BITMAP *backgrounddisplay;
}FPSdisplay;

void error(const char *txt);

void init_images(FPSdisplay turret, Crosshair crosshair);

void display_turret(FPSdisplay turret);

void display_timer(ALLEGRO_TIMER *timer, int scoreP1, int scoreP2);

int shoot_turret(Ship ships[], Crosshair crosshair, int destroyed_ships);

void start_game(Player P1, Player P2, FPSdisplay turret, ALLEGRO_FONT *font, ALLEGRO_TIMER *timerP1, ALLEGRO_TIMER *timerP2);

#endif //PROJET_ECE_WORLD_TURRET_AND_TIMER_H
