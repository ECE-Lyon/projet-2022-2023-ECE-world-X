//
// Created by Félix Pignal on 27/04/2023.
//

#include "constantes.h"
#include "duckGame.h"


void init_lauchGame(Game *jeux, ALLEGRO_DISPLAY* display){
    /*assert(al_init());
    assert(al_init_primitives_addon());
    assert(al_install_mouse());
    assert(al_init_image_addon());
    assert(al_init_font_addon());
    assert(al_init_ttf_addon());
    assert(al_install_keyboard());
    assert(al_install_audio());
    assert(al_init_acodec_addon());*/

    jeux->i = 0;
    jeux->dessin = false;
    jeux->offsetXduck = 0;
    jeux->offsetYduck = 0;
    jeux->bgImage = al_load_bitmap("../JarJar/Images/pixelWater.jpg");
    jeux->tempsRestant = 60;
    jeux->duckSelect = -1;
    jeux->gamePause = false;
    jeux->window = display;
    //jeux->event;
    jeux->fifo = al_create_event_queue();
    jeux->timer = al_create_timer(1.0/FPSCOIN);
    jeux->timerPartie = al_create_timer(1.0);// timer allegro pour le decompte du temps de partie
    //jeux->mouse_state;
    jeux->jedi = al_load_ttf_font("../JarJar/Fonts/Starjedi.ttf",30,0);
    jeux->jediout = al_load_ttf_font("../JarJar/Fonts/Starjout.ttf",30,0);
    jeux->jedihol = al_load_ttf_font("../JarJar/Fonts/Starjhol.ttf",50,0);
    jeux->backgoundMusic = al_load_sample("../JarJar/Audio/AcrosstheStars.ogg");
    init_boat(&jeux->smallBoat);// initalisation de toute la structure Bateau
    init_Cane(&jeux->pixelCane);
    init_Duck(jeux->ducks);
}

int launchGame(Game *jeux, Perso *playeractive){

    int isEnd = 0;// verification de la fin de la partie

    al_reserve_samples(1);//permet de lancer la musique
    al_set_window_title(jeux->window, "JarJar le filou");
    assert(jeux->backgoundMusic);
    assert(jeux->window);
    assert(jeux->timer);
    assert(jeux->timerPartie);
    assert(jeux->fifo);
    assert(jeux->jedi);
    al_register_event_source(jeux->fifo, al_get_display_event_source(jeux->window));//creation d'un event soit la file
    al_register_event_source(jeux->fifo, al_get_mouse_event_source());// les fonctions allegro utilisant la souris seront pris en compte
    al_register_event_source(jeux->fifo, al_get_keyboard_event_source());
    al_register_event_source(jeux->fifo, al_get_timer_event_source(jeux->timer));
    al_register_event_source(jeux->fifo, al_get_timer_event_source(jeux->timerPartie));

    al_hide_mouse_cursor(jeux->window);
    al_start_timer(jeux->timer);
    al_start_timer(jeux->timerPartie);
    al_play_sample(jeux->backgoundMusic,1.0f,0.0f,1.0f,ALLEGRO_PLAYMODE_LOOP,0);// jouer la musique
    while(!isEnd) {
        al_wait_for_event(jeux->fifo, &jeux->event);// en attente d'une tache des event_source (soit les inputs)
        al_get_mouse_state(&jeux->mouse_state);
        switch(jeux->event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE: {// si on click sur le X rouge
                isEnd = 1;
                break;
            }
            case ALLEGRO_EVENT_KEY_DOWN:{// si une touche est appuie
                if (jeux->event.keyboard.keycode == ALLEGRO_KEY_P) {// si la touche P est presse
                    jeux->gamePause = !jeux->gamePause;// inversion de l'etat du Boolen en fonction de l'etat present
                    if (jeux->gamePause) {
                        al_stop_timer(jeux->timerPartie);
                        al_stop_timer(jeux->timer);// pause des timers
                        al_draw_text(jeux->jedihol, JAUNE, LARGEUR /2, HAUTEUR/4, ALLEGRO_ALIGN_CENTER, "Game Paused");
                        al_draw_text(jeux->jedi, JAUNE, LARGEUR /2, HAUTEUR/2, ALLEGRO_ALIGN_CENTER, "press P to resume");
                        al_flip_display();
                    } else {// si gamePause etait egal a true
                        al_start_timer(jeux->timer);
                        al_start_timer(jeux->timerPartie);//redemmarage des timers
                    }
                }
                if(jeux->event.keyboard.keycode == ALLEGRO_KEY_ESCAPE){// si on tape sur la touche ECHAP
                    isEnd=1;
                    break;
                }
                break;
            }
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: {// si interaction avec les boutons de la souris
                if(jeux->event.mouse.button == BTN_LEFT) {// click bouton gauche
                    for(jeux->i=0; jeux->i < NB_MAX_JARJAR; jeux->i++){
                        if(cane_active(jeux->event.mouse.x, jeux->event.mouse.y, &jeux->ducks[jeux->i])) {
                            jeux->duckSelect = jeux->i;// duckSelect juste le mouvement du canard selectionee par le bouton de la souris
                            jeux->offsetXduck = jeux->event.mouse.x - jeux->ducks[jeux->i].x;// pour eviter des erreurs, les deplacements sont fait a partir du centre de la bitmap
                            jeux->offsetYduck = jeux->event.mouse.y - jeux->ducks[jeux->i].y;
                        }
                    }
                }
                break;
            }
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP: {// si l'interaction avec le bouton est termine
                if(jeux->event.mouse.button == BTN_LEFT) {// verification du lache de bouton
                    jeux->duckSelect = -1;
                }
                break;
            }
            case ALLEGRO_EVENT_TIMER: {// les actions qui vont etre renouveler a la vitesse du timer (constante verification)
                if(jeux->event.timer.source == jeux->timerPartie){// si le timerPartie est pris comme source (affecte uniquement les conditions mis dans la boucle
                    jeux->tempsRestant--;// on fait baisser un timer avec une valeur fixe
                    if(jeux->tempsRestant == 0){
                        isEnd = 1;
                        break;
                    }
                }
                jeux->pixelCane.x = jeux->mouse_state.x - 20;// sans interaction avec la souirs, la cane prends comme coordonees en continue ce de la souris
                jeux->pixelCane.y = jeux->mouse_state.y - 20;
                if(jeux->duckSelect != -1 ){// si duckSelect correspond a un canard
                    jeux->ducks[jeux->duckSelect].x = jeux->mouse_state.x - jeux->offsetXduck;//il va suivre egalement les deplacements de la souris
                    jeux->ducks[jeux->duckSelect].y = jeux->mouse_state.y - jeux->offsetYduck;
                    jeux->dessin = true;// fonction dessin pour un affichage fluide
                }
                if(jeux->duckSelect != -1 && duckOnBoat(&jeux->smallBoat, &jeux->ducks[jeux->duckSelect])){//verification de colision
                    if (jeux->ducks[jeux->duckSelect].compte != true){// le prendre en compte
                        jeux->smallBoat.score++;// l'ajouter au score joueur
                        jeux->ducks[jeux->duckSelect].actif = 0;// le detruire
                        jeux->ducks[jeux->duckSelect].compte = true;// prise en compte
                        jeux->ducks[jeux->duckSelect].compte = false;// remettre l'etat a faux
                        jeux->duckSelect = -1;
                    }
                    jeux->dessin = true;
                }
                apparitionDuck(jeux->ducks);//etre sur qu'ils apparaissent une premiere fois
                duckReposition(jeux->ducks);
                jeux->dessin = true;
                break;
            }
        }
        if (jeux->dessin) {// impression fluide a 60FPS
            al_clear_to_color(BLEU);
            al_draw_bitmap(jeux->bgImage,0,0,0);
            al_draw_textf(jeux->jedi,NOIR,50,50,ALLEGRO_ALIGN_LEFT,"Score: %d",jeux->smallBoat.score);
            al_draw_textf(jeux->jediout,NOIR,50,550,ALLEGRO_ALIGN_LEFT,"temps: %d",jeux->tempsRestant);
            printBoat(&jeux->smallBoat);
            printDuck(jeux->ducks);
            drawCane(&jeux->pixelCane);
            moveDuck(jeux->ducks);
            al_flip_display();
            jeux->dessin = false;
        }
    }
    playeractive->score = jeux->smallBoat.score;
    al_destroy_sample(jeux->backgoundMusic);
    al_destroy_font(jeux->jedi);
    al_destroy_font(jeux->jedihol);
    al_destroy_font(jeux->jediout);
    al_destroy_event_queue(jeux->fifo);
    al_destroy_timer(jeux->timer);
    al_destroy_timer(jeux->timerPartie);
    //al_destroy_display(jeux->window);
    return 0;

}