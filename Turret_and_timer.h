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
    ALLEGRO_BITMAP *timerdisplay;
    ALLEGRO_BITMAP *turretdisplay;
}FPSdisplay;

void error(const char *txt);

void init_turret(FPSdisplay *turret);

void display_turret(FPSdisplay *turret);

void shoot_turret(FPSdisplay *turret, Ship ships[], Crosshair crosshair);

#endif //PROJET_ECE_WORLD_TURRET_AND_TIMER_H
