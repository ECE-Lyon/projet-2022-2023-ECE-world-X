//
// Created by Félix Pignal on 27/04/2023.
//

// DuckGame.h
#include "constantes.h"
//#include "boat.h"
#include "cane.h"
#include "Duck.h"

#ifndef PROJET_DUCKGAME_H
#define PROJET_DUCKGAME_H

typedef struct {
    int dessin, i, offsetXduck, offsetYduck, tempsRestant, duckSelect;
    bool gamePause, end;
    ALLEGRO_DISPLAY* window;
    ALLEGRO_TIMER* timer;
    ALLEGRO_TIMER* timerPartie;
    ALLEGRO_EVENT event;
    ALLEGRO_EVENT_QUEUE* fifo;
    ALLEGRO_MOUSE_STATE mouse_state;
    ALLEGRO_FONT *jedi;
    ALLEGRO_FONT *jediout;
    ALLEGRO_FONT *jedihol;
    ALLEGRO_SAMPLE *backgoundMusic;
    Boat smallBoat;
    Cane pixelCane;
    Coin ducks[NB_MAX_JARJAR];
}Game;

int launchGame(Game *jeux);

void init_lauchGame(Game *jeux);

#endif //PROJET_DUCKGAME_H