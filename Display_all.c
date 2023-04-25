#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

#include "Ship.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 600

/* void display_end(bool endgame,Player player1, Player player2, ALLEGRO_FONT *font, ALLEGRO_FONT *fontBig) {
    if (endgame == 0) {
        al_draw_textf(font, al_map_rgb(255, 255, 0), SCREEN_WIDTH / 2,
                      SCREEN_HEIGHT / 2 + al_get_font_ascent(fontBig), ALLEGRO_ALIGN_CENTER, "Score : %d s",
                      player1.score);
        al_draw_textf(font, al_map_rgb(255, 255, 0), SCREEN_WIDTH / 2,
                      SCREEN_HEIGHT / 3 + al_get_font_ascent(fontBig), ALLEGRO_ALIGN_CENTER, "Score : %d s",
                      player2.score);

        if (player1.score > player2.score) {
            al_draw_textf(font, al_map_rgb(255, 255, 0), SCREEN_WIDTH / 2,
                          SCREEN_HEIGHT / 3 + al_get_font_ascent(fontBig), ALLEGRO_ALIGN_CENTER, "Player 1 wins");
        } else {
            al_draw_textf(font, al_map_rgb(255, 255, 0), SCREEN_WIDTH / 2,
                          SCREEN_HEIGHT / 3 + al_get_font_ascent(fontBig), ALLEGRO_ALIGN_CENTER, "Player 2 wins");
        }
    }
} */