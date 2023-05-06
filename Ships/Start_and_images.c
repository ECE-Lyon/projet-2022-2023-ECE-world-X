#include "Ship.h"
#include "Start_and_images.h"
#include "const.h"

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

void error(const char *txt) {
    printf("ERREUR : %s", txt);
    exit(EXIT_FAILURE);
}


void display_turret(FPSdisplay turret) {
    al_draw_bitmap(turret.backgrounddisplay, 0, 0, 0);
    al_draw_bitmap(turret.turretdisplay, 0, 159, 0);
}

void init_images(FPSdisplay *turret, Crosshair *crosshair) {
    turret->turretdisplay = al_load_bitmap("../Ships/Pictures/POV_Ship.png");
    turret->backgrounddisplay = al_load_bitmap("../Ships/Pictures/background.png");
    crosshair->crosshair = al_load_bitmap("../Ships/Pictures/crosshair.png");
}

void start_game(Player P1, Player P2, FPSdisplay turret, ALLEGRO_FONT *font, ALLEGRO_FONT *fontBig) {
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(turret.backgrounddisplay, 0, 0, 0);
    al_draw_bitmap(turret.turretdisplay, 0, 159, 0);
    if (P1.turn == true) {
        al_draw_text(font, al_map_rgb(255, 255, 0), SCREEN_WIDTH / 2,
                     SCREEN_HEIGHT / 2 - al_get_font_ascent(font), ALLEGRO_ALIGN_CENTER, "c'est au tour de 1");

    } else if (P2.turn == true) {
        al_draw_text(font, al_map_rgb(255, 255, 0), SCREEN_WIDTH / 2,
                     SCREEN_HEIGHT / 2 - al_get_font_ascent(font), ALLEGRO_ALIGN_CENTER, "c'est au tour de 2");
    }
    al_flip_display();
    al_rest(2);
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(turret.backgrounddisplay, 0, 0, 0);
    al_draw_bitmap(turret.turretdisplay, 0, 159, 0);
    al_draw_text(fontBig, al_map_rgb(255, 255, 0), SCREEN_WIDTH / 2,
                 SCREEN_HEIGHT / 2 - al_get_font_ascent(fontBig), ALLEGRO_ALIGN_CENTER, "3");
    al_flip_display();
    al_rest(1);
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(turret.backgrounddisplay, 0, 0, 0);
    al_draw_bitmap(turret.turretdisplay, 0, 159, 0);
    al_draw_text(fontBig, al_map_rgb(255, 255, 0), SCREEN_WIDTH / 2,
                 SCREEN_HEIGHT / 2 - al_get_font_ascent(fontBig), ALLEGRO_ALIGN_CENTER, "2");
    al_flip_display();
    al_rest(1);
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(turret.backgrounddisplay, 0, 0, 0);
    al_draw_bitmap(turret.turretdisplay, 0, 159, 0);
    al_draw_text(fontBig, al_map_rgb(255, 255, 0), SCREEN_WIDTH / 2,
                 SCREEN_HEIGHT / 2 - al_get_font_ascent(fontBig), ALLEGRO_ALIGN_CENTER, "1");
    al_flip_display();
    al_rest(1);
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(turret.backgrounddisplay, 0, 0, 0);
    al_draw_bitmap(turret.turretdisplay, 0, 159, 0);
    al_draw_text(fontBig, al_map_rgb(255, 255, 0), SCREEN_WIDTH / 2,
                 SCREEN_HEIGHT / 2 - al_get_font_ascent(fontBig), ALLEGRO_ALIGN_CENTER, "game start !");
    al_flip_display();
    al_rest(1);

}

void shoot_turret(Ship ships[NB_SHIPS], Crosshair crosshair) {
    for (int i = 0; i < NB_SHIPS; ++i) {
        if (ships[i].destroyed == false) {
            if (crosshair.location_x >= ships[i].x && crosshair.location_x <= (ships[i].x + ships[i].width)
                && crosshair.location_y >= ships[i].y && crosshair.location_y <= (ships[i].y + ships[i].length)) {
                if (ships[i].size == 1) {
                    al_draw_bitmap(ships->explosion1, ships[i].x, ships[i].y, 0);
                    ships[i].destroyed = true;
                } else if (ships[i].size == 2) {
                    al_draw_bitmap(ships->explosion2, ships[i].x, ships[i].y, 0);
                    ships[i].destroyed = true;
                } else if (ships[i].size == 3) {
                    al_draw_bitmap(ships->explosion3, ships[i].x, ships[i].y, 0);
                    ships[i].destroyed = true;
                }
            }
        }
    }
}
