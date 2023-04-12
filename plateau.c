//
// Created by trist on 12/04/2023.
//
#include "plateau.h"
#include "constante.h"

void init_board(Damier* board) {
    board->widthsquare = WIGAME/NBSQUARE;
    board->heightsquare = HEIGAME/NBSQUARE;
    board->nb = NBSQUARE;
}