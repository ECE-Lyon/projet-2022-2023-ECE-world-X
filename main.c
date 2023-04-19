#include "Ship.h"
#include "Turret_and_timer.h"
#include "const.h"

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

int main() {
    int endgame = 0;
    int pause = 0;
    int quit = 0;
    FPSdisplay turret;
    Ship ships[NB_SHIPS];

    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_FONT *fontBangers60 = NULL;
    ALLEGRO_FONT *fontBangers160 = NULL;
    ALLEGRO_EVENT event;

    if (!al_init()) {
        error("Initialisation Allegro");
    }
    if (!al_install_keyboard()) {
        error("Installation clavier");
    }
    if (!al_init_primitives_addon()) {
        error("Initialisation primitives de dessin");
    }
    al_init_font_addon();
    if (!al_init_ttf_addon()) {
        error("Initialisation polices TTF");
    }
    if (!al_init_image_addon()) {
        error("Initialisation images");
    }

    display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!display) {
        error("Création de la fenêtre");
    }
    return 0;
}
