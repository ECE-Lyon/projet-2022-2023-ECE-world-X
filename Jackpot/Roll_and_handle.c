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
    roll->Picture1 = al_load_bitmap("../Jackpot/Pictures2/Bb8.png");
    roll->Picture2 = al_load_bitmap("../Jackpot/Pictures2/Bobba_fett.png");
    roll->Picture3 = al_load_bitmap("../Jackpot/Pictures2/Darth_Vather.png");
    roll->Picture4 = al_load_bitmap("../Jackpot/Pictures2/Death_star.png");
    roll->Picture5 = al_load_bitmap("../Jackpot/Pictures2/General_grievous.png");
    roll->Picture6 = al_load_bitmap("../Jackpot/Pictures2/Millenium_falcon.png");
    roll->Picture7 = al_load_bitmap("../Jackpot/Pictures2/R2d2.png");
    roll->Picture8 = al_load_bitmap("../Jackpot/Pictures2/Small_alien.png");
    roll->Picture9 = al_load_bitmap("../Jackpot/Pictures2/Storm_trooper.png");
    handle->Machine_up = al_load_bitmap("../Jackpot/Pictures2/Machine_up.png");
    handle->Machine_down = al_load_bitmap("../Jackpot/Pictures2/Machine_down.png");
    handle->Machine_background = al_load_bitmap("../Jackpot/Pictures2/Machine_background.png");
}

void init_rolls(Roll roll[NB_ROLLS]) {
    int i, j = 0;
    for (int k = 0; k < NB_ROLLS; ++k) {
        for (i = 0; i < 9; i++) {
            roll[k].order[i] = -1;
        }
        for (i = 0; i < 9; i++) {
            do {
                j = rand() % 9;
            } while (roll[k].order[j] != -1);
            roll[k].order[j] = i;
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
    for (int j = 0; j < NB_ROLLS; ++j) {
        for (int i = 0; i < 9; ++i) {
            if (roll[j].order[i] == 0) {
                al_draw_bitmap(roll->Picture1, X_ROLL1, roll[j].y1, 0);
                al_draw_bitmap(roll->Picture1, X_ROLL2, roll[j].y1, 0);
                al_draw_bitmap(roll->Picture1, X_ROLL3, roll[j].y1, 0);
            } else if (roll[j].order[i] == 1) {
                al_draw_bitmap(roll->Picture2, X_ROLL1, roll[j].y2, 0);
                al_draw_bitmap(roll->Picture2, X_ROLL2, roll[j].y2, 0);
                al_draw_bitmap(roll->Picture2, X_ROLL3, roll[j].y2, 0);
            } else if (roll[j].order[i] == 2) {
                al_draw_bitmap(roll->Picture3, X_ROLL1, roll[j].y3, 0);
                al_draw_bitmap(roll->Picture3, X_ROLL2, roll[j].y3, 0);
                al_draw_bitmap(roll->Picture3, X_ROLL3, roll[j].y3, 0);
            } else if (roll[j].order[i] == 3) {
                al_draw_bitmap(roll->Picture4, X_ROLL1, roll[j].y4, 0);
                al_draw_bitmap(roll->Picture4, X_ROLL2, roll[j].y4, 0);
                al_draw_bitmap(roll->Picture4, X_ROLL3, roll[j].y4, 0);
            } else if (roll[j].order[i] == 4) {
                al_draw_bitmap(roll->Picture5, X_ROLL1, roll[j].y5, 0);
                al_draw_bitmap(roll->Picture5, X_ROLL2, roll[j].y5, 0);
                al_draw_bitmap(roll->Picture5, X_ROLL3, roll[j].y5, 0);
            } else if (roll[j].order[i] == 5) {
                al_draw_bitmap(roll->Picture6, X_ROLL1, roll[j].y6, 0);
                al_draw_bitmap(roll->Picture6, X_ROLL2, roll[j].y6, 0);
                al_draw_bitmap(roll->Picture6, X_ROLL3, roll[j].y6, 0);
            } else if (roll[j].order[i] == 6) {
                al_draw_bitmap(roll->Picture7, X_ROLL1, roll[j].y7, 0);
                al_draw_bitmap(roll->Picture7, X_ROLL2, roll[j].y7, 0);
                al_draw_bitmap(roll->Picture7, X_ROLL3, roll[j].y7, 0);
            } else if (roll[j].order[i] == 7) {
                al_draw_bitmap(roll->Picture8, X_ROLL1, roll[j].y8, 0);
                al_draw_bitmap(roll->Picture8, X_ROLL2, roll[j].y8, 0);
                al_draw_bitmap(roll->Picture8, X_ROLL3, roll[j].y8, 0);
            } else if (roll[j].order[i] == 8) {
                al_draw_bitmap(roll->Picture9, X_ROLL1, roll[j].y9, 0);
                al_draw_bitmap(roll->Picture9, X_ROLL2, roll[j].y9, 0);
                al_draw_bitmap(roll->Picture9, X_ROLL3, roll[j].y9, 0);
            }


        }
    }
}

void rolling(Roll roll[NB_ROLLS], float acceleration, float max_speed) {
    roll[0].rotation_speed += acceleration * 2;
    roll[1].rotation_speed += acceleration;
    roll[2].rotation_speed += acceleration / 2;
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
//
    return;
}