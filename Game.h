#ifndef ESGI_CPP_GIT_EVAL1_GAME_H
#define ESGI_CPP_GIT_EVAL1_GAME_H

#include "Joueur.h"
#include "Grid.h"


class Game
{
    private:
        Joueur j1;
        Joueur j2;
        Joueur* currentPlayer;
        Grid grid;


    public:
        Game();
        void turn();
        void start();
        void selectNames();
};

#endif //ESGI_CPP_GIT_EVAL1_GAME_H