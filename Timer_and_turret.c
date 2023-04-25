#include "Ship.h"
#include "Turret_and_timer.h"
#include "const.h"

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

void error(const char *txt) {
    printf("ERREUR : %s", txt);
    exit(EXIT_FAILURE);
}

//int Timer(){
//    ALLEGRO_TIMER *al_create_timer()
//}

void display_turret(FPSdisplay turret, bool endgame){
    while (endgame == 0){
        al_draw_bitmap(turret.turretdisplay, 0, 159, 0);
        al_draw_bitmap(turret.backgrounddisplay, 0, 0, 0);
    }
}

void init_images(FPSdisplay turret, Crosshair crosshair){
    turret.turretdisplay = al_load_bitmap("../Pictures/POV_Ship.png");
    turret.backgrounddisplay = al_load_bitmap("../Picture/background.png");
    //turrettimerdisplay;
    crosshair.crosshair = al_load_bitmap("../Pictures/crosshair.png");
}