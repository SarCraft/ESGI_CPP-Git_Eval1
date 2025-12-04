#ifndef ESGI_CPP_GIT_EVAL1_GAME_H
#define ESGI_CPP_GIT_EVAL1_GAME_H

#include "Joueur.h"
#include "Grid.h"
#include "GameRenderer.h"

enum class GameState {
    MODE_SELECTION,
    NAME_SELECTION,
    PLAYING
};

enum class GameMode {
    PVP,  // Joueur vs Joueur
    PVE   // Joueur vs Bot
};

class Game
{
    private:
        Joueur j1;
        Joueur j2;
        Joueur* currentPlayer;
        Grid grid;
        bool gameOver;
        string winner;
        GameRenderer renderer;
        GameState gameState;
        GameMode gameMode;
        string player1Name;
        string player2Name;
        int activeInput;

    public:
        Game();
        void turn();
        void start();
        void selectNames();
        void handleMouseClick(int mouseX, int mouseY);
        void handleTextInput();
        void handleModeSelection(int mouseX, int mouseY);
        void botTurn();
        void run();
        GameState getGameState() const;
        GameMode getGameMode() const;
        string getPlayer1Name() const;
        string getPlayer2Name() const;
        int getActiveInput() const;
};

#endif
