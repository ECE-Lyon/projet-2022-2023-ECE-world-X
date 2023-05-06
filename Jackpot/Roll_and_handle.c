#include "const2.h"
#include "Roll_and_handle.h"

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

void init_images(Roll roll, Handle handle){
    roll.Picture1 = al_load_bitmap("../Jackpot/Pictures2/Bb8.png");
    roll.Picture2 = al_load_bitmap("../Jackpot/Pictures2/Bobba_fett.png");
    roll.Picture3 = al_load_bitmap("../Jackpot/Pictures2/Darth_Vather.png");
    roll.Picture4 = al_load_bitmap("../Jackpot/Pictures2/Death_star.png");
    roll.Picture5 = al_load_bitmap("../Jackpot/Pictures2/General_grievous.png");
    roll.Picture6 = al_load_bitmap("../Jackpot/Pictures2/Millenium_falcon.png");
    roll.Picture7 = al_load_bitmap("../Jackpot/Pictures2/R2d2.png");
    roll.Picture8 = al_load_bitmap("../Jackpot/Pictures2/Small_alien.png");
    roll.Picture9 = al_load_bitmap("../Jackpot/Pictures2/Storm_trooper.png");
    handle.Machine_up = al_load_bitmap("../Jackpot/Pictures2/Machine_up.png");
    handle.Machine_down = al_load_bitmap("../Jackpot/Pictures2/Machine_down.png");
}