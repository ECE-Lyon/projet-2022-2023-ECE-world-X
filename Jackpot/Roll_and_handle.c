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
    ALLEGRO_BITMAP *pic1 = al_load_bitmap("../Jackpot/Pictures2/Bb8.png");
    ALLEGRO_BITMAP *pic2 = al_load_bitmap("../Jackpot/Pictures2/Bobba_fett.png");
    ALLEGRO_BITMAP *pic3 = al_load_bitmap("../Jackpot/Pictures2/Darth_Vather.png");
    ALLEGRO_BITMAP *pic4 = al_load_bitmap("../Jackpot/Pictures2/Death_star.png");
    ALLEGRO_BITMAP *pic5 = al_load_bitmap("../Jackpot/Pictures2/General_grievous.png");
    ALLEGRO_BITMAP *pic6 = al_load_bitmap("../Jackpot/Pictures2/Millenium_falcon.png");
    ALLEGRO_BITMAP *pic7 = al_load_bitmap("../Jackpot/Pictures2/R2d2.png");
    ALLEGRO_BITMAP *pic8 = al_load_bitmap("../Jackpot/Pictures2/Small_alien.png");
    ALLEGRO_BITMAP *pic9 = al_load_bitmap("../Jackpot/Pictures2/Storm_trooper.png");


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

            if(roll[k].order[0] == 1) {
                roll[k].Picture1 = pic1;
            } else if (roll[k].order[0] == 2) {
                roll[k].Picture1 = pic2;
            } else if (roll[k].order[0] == 3) {
                roll[k].Picture1 = pic3;
            } else if (roll[k].order[0] == 4) {
                roll[k].Picture1 = pic4;
            } else if (roll[k].order[0] == 5) {
                roll[k].Picture1 = pic5;
            } else if (roll[k].order[0] == 6) {
                roll[k].Picture1 = pic6;
            } else if (roll[k].order[0] == 7) {
                roll[k].Picture1 = pic7;
            } else if (roll[k].order[0] == 8) {
                roll[k].Picture1 = pic8;
            } else if (roll[k].order[0] == 9) {
                roll[k].Picture1 = pic9;
            } else if (roll[k].order[1] == 1) {
                roll[k].Picture2 = pic1;
            } else if (roll[k].order[1] == 2) {
                roll[k].Picture2 = pic2;
            } else if (roll[k].order[1] == 3) {
                roll[k].Picture2 = pic3;
            } else if (roll[k].order[1] == 4) {
                roll[k].Picture2 = pic4;
            } else if (roll[k].order[1] == 5) {
                roll[k].Picture2 = pic5;
            } else if (roll[k].order[1] == 6) {
                roll[k].Picture2 = pic6;
            } else if (roll[k].order[1] == 7) {
                roll[k].Picture2 = pic7;
            } else if (roll[k].order[1] == 8) {
                roll[k].Picture2 = pic8;
            } else if (roll[k].order[1] == 9) {
                roll[k].Picture2 = pic9;
            } else if (roll[k].order[2] == 1) {
                roll[k].Picture3 = pic1;
            } else if (roll[k].order[2] == 2) {
                roll[k].Picture3 = pic2;
            } else if (roll[k].order[2] == 3) {
                roll[k].Picture3 = pic3;
            } else if (roll[k].order[2] == 4) {
                roll[k].Picture3 = pic4;
            } else if (roll[k].order[2] == 5) {
                roll[k].Picture3 = pic5;
            } else if (roll[k].order[2] == 6) {
                roll[k].Picture3 = pic6;
            } else if (roll[k].order[2] == 7) {
                roll[k].Picture3 = pic7;
            } else if (roll[k].order[2] == 8) {
                roll[k].Picture3 = pic8;
            } else if (roll[k].order[2] == 9) {
                roll[k].Picture3 = pic9;
            } else if (roll[k].order[3] == 1) {
                roll[k].Picture4 = pic1;
            } else if (roll[k].order[3] == 2) {
                roll[k].Picture4 = pic2;
            } else if (roll[k].order[3] == 3) {
                roll[k].Picture4 = pic3;
            } else if (roll[k].order[3] == 4) {
                roll[k].Picture4 = pic4;
            } else if (roll[k].order[3] == 5) {
                roll[k].Picture4 = pic5;
            } else if (roll[k].order[3] == 6) {
                roll[k].Picture4 = pic6;
            } else if (roll[k].order[3] == 7) {
                roll[k].Picture4 = pic7;
            } else if (roll[k].order[3] == 8) {
                roll[k].Picture4 = pic8;
            } else if (roll[k].order[3] == 9) {
                roll[k].Picture4 = pic9;
            } else if (roll[k].order[4] == 1) {
                roll[k].Picture5 = pic1;
            } else if (roll[k].order[4] == 2) {
                roll[k].Picture5 = pic2;
            } else if (roll[k].order[4] == 3) {
                roll[k].Picture5 = pic3;
            } else if (roll[k].order[4] == 4) {
                roll[k].Picture5 = pic4;
            } else if (roll[k].order[4] == 5) {
                roll[k].Picture5 = pic5;
            } else if (roll[k].order[4] == 6) {
                roll[k].Picture5 = pic6;
            } else if (roll[k].order[4] == 7) {
                roll[k].Picture5 = pic7;
            } else if (roll[k].order[4] == 8) {
                roll[k].Picture5 = pic8;
            } else if (roll[k].order[4] == 9) {
                roll[k].Picture5 = pic9;
            } else if (roll[k].order[5] == 1) {
                roll[k].Picture6 = pic1;
            } else if (roll[k].order[5] == 2) {
                roll[k].Picture6 = pic2;
            } else if (roll[k].order[5] == 3) {
                roll[k].Picture6 = pic3;
            } else if (roll[k].order[5] == 4) {
                roll[k].Picture6 = pic4;
            } else if (roll[k].order[5] == 5) {
                roll[k].Picture6 = pic5;
            } else if (roll[k].order[5] == 6) {
                roll[k].Picture6 = pic6;
            } else if (roll[k].order[5] == 7) {
                roll[k].Picture6 = pic7;
            } else if (roll[k].order[5] == 8) {
                roll[k].Picture6 = pic8;
            } else if (roll[k].order[5] == 9) {
                roll[k].Picture6 = pic9;
            } else if (roll[k].order[6] == 1) {
                roll[k].Picture7 = pic1;
            } else if (roll[k].order[6] == 2) {
                roll[k].Picture7 = pic2;
            } else if (roll[k].order[6] == 3) {
                roll[k].Picture7 = pic3;
            } else if (roll[k].order[6] == 4) {
                roll[k].Picture7 = pic4;
            } else if (roll[k].order[6] == 5) {
                roll[k].Picture7 = pic5;
            } else if (roll[k].order[6] == 6) {
                roll[k].Picture7 = pic6;
            } else if (roll[k].order[6] == 7) {
                roll[k].Picture7 = pic7;
            } else if (roll[k].order[6] == 8) {
                roll[k].Picture7 = pic8;
            } else if (roll[k].order[6] == 9) {
                roll[k].Picture7 = pic9;
            } else if (roll[k].order[7] == 1) {
                roll[k].Picture8 = pic1;
            } else if (roll[k].order[7] == 2) {
                roll[k].Picture8 = pic2;
            } else if (roll[k].order[7] == 3) {
                roll[k].Picture8 = pic3;
            } else if (roll[k].order[7] == 4) {
                roll[k].Picture8 = pic4;
            } else if (roll[k].order[7] == 5) {
                roll[k].Picture8 = pic5;
            } else if (roll[k].order[7] == 6) {
                roll[k].Picture8 = pic6;
            } else if (roll[k].order[7] == 7) {
                roll[k].Picture8 = pic7;
            } else if (roll[k].order[7] == 8) {
                roll[k].Picture8 = pic8;
            } else if (roll[k].order[7] == 9) {
                roll[k].Picture8 = pic9;
            } else if (roll[k].order[8] == 1) {
                roll[k].Picture9 = pic1;
            } else if (roll[k].order[8] == 2) {
                roll[k].Picture9 = pic2;
            } else if (roll[k].order[8] == 3) {
                roll[k].Picture9 = pic3;
            } else if (roll[k].order[8] == 4) {
                roll[k].Picture9 = pic4;
            } else if (roll[k].order[8] == 5) {
                roll[k].Picture9 = pic5;
            } else if (roll[k].order[8] == 6) {
                roll[k].Picture9 = pic6;
            } else if (roll[k].order[8] == 7) {
                roll[k].Picture9 = pic7;
            } else if (roll[k].order[8] == 8) {
                roll[k].Picture9 = pic8;
            } else if (roll[k].order[8] == 9) {
                roll[k].Picture9 = pic9;
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