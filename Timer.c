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

int Timer(){
    ALLEGRO_TIMER *al_create_timer()
}