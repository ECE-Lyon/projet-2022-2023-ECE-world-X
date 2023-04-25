#include "Ship.h"
#include "Turret_and_timer.h"
#include "const.h"
#include "Player_crosshair.h"

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
    Crosshair crosshair;

    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_FONT *fontBangers60 = NULL;
    ALLEGRO_FONT *fontBangers160 = NULL;
    ALLEGRO_EVENT event;

    srand(time(NULL));

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

    al_set_window_position(display, 200, 100);
    if (!display) {
        error("Création de la fenêtre");
    }
    turret.turretdisplay = al_load_bitmap("../Pictures/POV_Ship.png");
    crosshair.crosshair = al_load_bitmap("../Pictures/crosshair.png");
    turret.backgrounddisplay = al_load_bitmap("../Pictures/background.png");
    al_draw_bitmap(turret.backgrounddisplay, 0, 0, 0);
    al_draw_bitmap(turret.turretdisplay, 0, 159, 0);
    init_ships(ships);
    spawn_ships(ships);
    display_ships(ships);
    al_flip_display();
    al_rest(15);
    al_destroy_display(display);
    return 0;
}
