#include "const_jackpot.h"
#include "Roll_and_handle.h"

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

void error_jackpot(const char *txt) {
    printf("ERREUR : %s", txt);
    exit(EXIT_FAILURE);
}

void init_images_jackpot(Roll roll[NB_ROLLS], Handle *handle) {
    handle->Machine_up = al_load_bitmap("../Jackpot/Pictures2/Machine_up.png");
    handle->Machine_down = al_load_bitmap("../Jackpot/Pictures2/Machine_down.png");
    handle->Machine_background = al_load_bitmap("../Jackpot/Pictures2/Machine_background.png");
}

void init_rolls(Roll roll[NB_ROLLS]) {
    int j = 0, temp = 0;
    for (int k = 0; k < NB_ROLLS; ++k) {
        for (int i = 0; i < 9; i++) {
            roll[k].order[i] = i + 1;
        }
        for (int i = 9 - 1; i > 0; i--) {
            j = rand() % (i + 1);
            temp = roll[k].order[i];
            roll[k].order[i] = roll[k].order[j];
            roll[k].order[j] = temp;
        }
    }
    for (int k = 0; k < NB_ROLLS; ++k) {
        roll[k].y1 = 272 - (140 * 2);
        roll[k].y2 = 272 - 140;
        roll[k].y3 = 272;
        roll[k].y4 = 272 + 140;
        roll[k].y5 = 272 + (140*2);
        roll[k].y6 = 272 + (140*3);
        roll[k].y7 = 272 + (140*4);
        roll[k].y8 = 272 + (140*5);
        roll[k].y9 = 272 + (140*6);
        for (int i = 0; i < 9; ++i) {
            if(roll[k].order[i] == 1) {
                roll[k].Picture1 = al_load_bitmap("../Jackpot/Pictures2/Bb8.png");
                roll[k].Picture2 = al_load_bitmap("../Jackpot/Pictures2/Bb8.png");
                roll[k].Picture3 = al_load_bitmap("../Jackpot/Pictures2/Bb8.png");
                roll[k].Picture4 = al_load_bitmap("../Jackpot/Pictures2/Bb8.png");
                roll[k].Picture5 = al_load_bitmap("../Jackpot/Pictures2/Bb8.png");
                roll[k].Picture6 = al_load_bitmap("../Jackpot/Pictures2/Bb8.png");
                roll[k].Picture7 = al_load_bitmap("../Jackpot/Pictures2/Bb8.png");
                roll[k].Picture8 = al_load_bitmap("../Jackpot/Pictures2/Bb8.png");
                roll[k].Picture9 = al_load_bitmap("../Jackpot/Pictures2/Bb8.png");
            } else if (roll[k].order[i] == 2) {
                roll[k].Picture1 = al_load_bitmap("../Jackpot/Pictures2/Bobba_fett.png");
            } else if (roll[k].order[i] == 3) {
                roll[k].Picture1 = al_load_bitmap("../Jackpot/Pictures2/Darth_Vather.png");
            } else if (roll[k].order[i] == 4) {
                roll[k].Picture1 = al_load_bitmap("../Jackpot/Pictures2/Death_star.png");
            } else if (roll[k].order[i] == 5) {
                roll[k].Picture1 = al_load_bitmap("../Jackpot/Pictures2/General_grievous.png");
            } else if (roll[k].order[i] == 6) {
                roll[k].Picture1 = al_load_bitmap("../Jackpot/Pictures2/Millenium_falcon.png");
            } else if (roll[k].order[i] == 7) {
                roll[k].Picture1 = al_load_bitmap("../Jackpot/Pictures2/R2d2.png");
            } else if (roll[k].order[i] == 8) {
                roll[k].Picture1 = al_load_bitmap("../Jackpot/Pictures2/Small_alien.png");
            } else if (roll[k].order[i] == 9) {
                roll[k].Picture1 = al_load_bitmap("../Jackpot/Pictures2/Storm_trooper.png");
            }
        }
    }
}


void display_Machine(Handle handle, ALLEGRO_FONT *font) {
    if (handle.down == true) {
        al_draw_bitmap(handle.Machine_down, 0, 0, 0);
        al_draw_text(font, al_map_rgb(255, 255, 0), 885,
                     495 - al_get_font_ascent(font), 0, "cliquez sur ");
        al_draw_text(font, al_map_rgb(255, 255, 0), 885,
                     515 - al_get_font_ascent(font), 0, "le bras de la machine ");
        al_draw_text(font, al_map_rgb(255, 255, 0), 885,
                     535 - al_get_font_ascent(font), 0, "pour la lancer !");
        al_draw_text(font, al_map_rgb(255, 255, 0), 900,
                     40 - al_get_font_ascent(font), 0, "cliquez sur echap ");
        al_draw_text(font, al_map_rgb(255, 255, 0), 900,
                     60 - al_get_font_ascent(font), 0, "pour arrêter de jouer");
    } else if (handle.down == false) {
        al_draw_bitmap(handle.Machine_up, 0, 0, 0);
        al_draw_text(font, al_map_rgb(255, 255, 0), 885,
                     495 - al_get_font_ascent(font), 0, "cliquez sur ");
        al_draw_text(font, al_map_rgb(255, 255, 0), 885,
                     515 - al_get_font_ascent(font), 0, "le bras de la machine ");
        al_draw_text(font, al_map_rgb(255, 255, 0), 885,
                     535 - al_get_font_ascent(font), 0, "pour la lancer !");
        al_draw_text(font, al_map_rgb(255, 255, 0), 900,
                     40 - al_get_font_ascent(font), 0, "cliquez sur echap ");
        al_draw_text(font, al_map_rgb(255, 255, 0), 900,
                     60 - al_get_font_ascent(font), 0, "pour arrêter de jouer");
    }
}

void display_background(Handle handle) {
    al_draw_bitmap(handle.Machine_background, 0, 0, 0);
    al_flip_display();
}

void display_rolls(Roll roll[NB_ROLLS]) {
    for (int k = 0; k < NB_ROLLS; ++k) {

            al_draw_bitmap(roll[k].Picture1, roll[k].location_x, roll[k].y1, 0);

            al_draw_bitmap(roll[k].Picture2, roll[k].location_x, roll[k].y2, 0);

            al_draw_bitmap(roll[k].Picture3, roll[k].location_x, roll[k].y3, 0);

            al_draw_bitmap(roll[k].Picture4, roll[k].location_x, roll[k].y4, 0);

            al_draw_bitmap(roll[k].Picture5, roll[k].location_x, roll[k].y5, 0);

            al_draw_bitmap(roll[k].Picture6, roll[k].location_x, roll[k].y6, 0);

            al_draw_bitmap(roll[k].Picture7, roll[k].location_x, roll[k].y7, 0);

            al_draw_bitmap(roll[k].Picture8, roll[k].location_x, roll[k].y8, 0);

            al_draw_bitmap(roll[k].Picture9, roll[k].location_x, roll[k].y9, 0);

    }
}

void rolling(Roll roll[NB_ROLLS], float acceleration1, float acceleration2, float acceleration3, float max_speed) {
    roll[0].rotation_speed += acceleration1;
    roll[1].rotation_speed += acceleration2;
    roll[2].rotation_speed += acceleration3;
    for (int i = 0; i < NB_ROLLS; ++i) {
        roll[i].y1 += roll[i].rotation_speed;
        roll[i].y2 += roll[i].rotation_speed;
        roll[i].y3 += roll[i].rotation_speed;
        roll[i].y4 += roll[i].rotation_speed;
        roll[i].y5 += roll[i].rotation_speed;
        roll[i].y6 += roll[i].rotation_speed;
        roll[i].y7 += roll[i].rotation_speed;
        roll[i].y8 += roll[i].rotation_speed;
        roll[i].y9 += roll[i].rotation_speed;
        if (roll[i].rotation_speed > max_speed) {
            roll[i].rotation_speed = 0;
        }
    }
}

int prize(Roll roll[NB_ROLLS], Perso P1) {

    return;
}