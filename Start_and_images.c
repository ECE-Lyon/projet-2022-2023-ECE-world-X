#include "Ship.h"
#include "Start_and_images.h"
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


void display_turret(FPSdisplay turret) {
    al_draw_bitmap(turret.backgrounddisplay, 0, 0, 0);
    al_draw_bitmap(turret.turretdisplay, 0, 159, 0);
}

void init_images(FPSdisplay* turret, Crosshair* crosshair) {
    turret->turretdisplay = al_load_bitmap("../Pictures/POV_Ship.png");
    turret->backgrounddisplay = al_load_bitmap("../Pictures/background.png");
    crosshair->crosshair = al_load_bitmap("../Pictures/crosshair.png");
}

void start_game(Player P1, Player P2, FPSdisplay turret, ALLEGRO_FONT *font, ALLEGRO_FONT *fontBig, ALLEGRO_TIMER *count) {
    if (P1.turn) {
        al_draw_text(font, al_map_rgb(255, 255, 0), SCREEN_WIDTH / 2,
                      SCREEN_HEIGHT / 2 - al_get_font_ascent(font), ALLEGRO_ALIGN_CENTER, "c'est au tour de");
        al_start_timer(count);
    } else if (P2.turn) {
        al_draw_text(font, al_map_rgb(255, 255, 0), SCREEN_WIDTH / 2,
                      SCREEN_HEIGHT / 2 - al_get_font_ascent(font), ALLEGRO_ALIGN_CENTER, "c'est au tour de");
        al_start_timer(count);
    }
    al_rest(2);
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(turret.backgrounddisplay, 0, 0, 0);
    al_draw_bitmap(turret.turretdisplay, 0, 159, 0);
    al_draw_text(fontBig, al_map_rgb(255, 255, 0), SCREEN_WIDTH / 2,
                  SCREEN_HEIGHT / 2 - al_get_font_ascent(font), ALLEGRO_ALIGN_CENTER, "3");
    al_flip_display();
    al_rest(1);
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(turret.backgrounddisplay, 0, 0, 0);
    al_draw_bitmap(turret.turretdisplay, 0, 159, 0);
    al_draw_text(fontBig, al_map_rgb(255, 255, 0), SCREEN_WIDTH / 2,
                  SCREEN_HEIGHT / 2 - al_get_font_ascent(font), ALLEGRO_ALIGN_CENTER, "2");
    al_flip_display();
    al_rest(1);
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(turret.backgrounddisplay, 0, 0, 0);
    al_draw_bitmap(turret.turretdisplay, 0, 159, 0);
    al_draw_text(fontBig, al_map_rgb(255, 255, 0), SCREEN_WIDTH / 2,
                  SCREEN_HEIGHT / 2 - al_get_font_ascent(font), ALLEGRO_ALIGN_CENTER, "1");
    al_flip_display();
    al_rest(1);
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(turret.backgrounddisplay, 0, 0, 0);
    al_draw_bitmap(turret.turretdisplay, 0, 159, 0);
    al_draw_text(fontBig, al_map_rgb(255, 255, 0), SCREEN_WIDTH / 2,
                  SCREEN_HEIGHT / 2 - al_get_font_ascent(font), ALLEGRO_ALIGN_CENTER, "game start !");
    al_flip_display();

}

int shoot_turret(Ship ships[NB_SHIPS], Crosshair crosshair, int destroyed_ships){
    for (int i = 0; i < NB_SHIPS; ++i) {
        if(crosshair.location_x >= ships[i].x && crosshair.location_x <= (ships[i].x + ships[i].width)
        && crosshair.location_y >= ships[i].y && crosshair.location_y <= (ships[i].y + ships[i].length)){
            if (ships[i].size == 1) {
                al_draw_bitmap(ships[i].explosion1, ships[i].x, ships[i].y, 0);
            } else if (ships[i].size == 2) {
                al_draw_bitmap(ships[i].explosion2, ships[i].x, ships[i].y, 0);
            } else if (ships[i].size == 3) {
                al_draw_bitmap(ships[i].explosion3, ships[i].x, ships[i].y, 0);
            }
            destroyed_ships++;
        }
    }
    return destroyed_ships;
}

void display_timer(ALLEGRO_TIMER *timer, int scoreP1, int scoreP2){

}