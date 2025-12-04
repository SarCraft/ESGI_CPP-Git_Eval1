#include "Game.h"
#include "pvp.h"
#include "pve.h"
#include <iostream>

using namespace std;

Game::Game() : j1("Joueur1", 'X'), j2("Joueur2", 'O'), grid(), gameOver(false), winner(""), 
               gameState(GameState::NAME_SELECTION), player1Name(""), player2Name(""), activeInput(1){}

void Game::start()
{
    Pvp pvp;
    Pve pve;


    int modeJeu;
    cout << "Choisissez votre mode de jeu : 1 = 1_Joueur, 2 = 2_Joueurs" <<endl;
    cin >> modeJeu;
    switch (modeJeu) {
        case 1:
            pve.start();
            break;
        case 2:
            pvp.start();
            break;
        default:
            cout << "Entree invalide" << endl;
            break;
    }
}

void Game::handleMouseClick(int mouseX, int mouseY)
{
    if (gameOver) return;

    int row, col;
    
    // Utiliser le renderer pour convertir les coordonnées de la souris en cellule
    if (renderer.getCellFromMouseClick(mouseX, mouseY, row, col)) {
        // Essayer de placer le symbole
        if (grid.placeSymbol(row, col, currentPlayer->getSymbole())) {
            // Vérifier la victoire
            if (grid.checkWin(currentPlayer->getSymbole())) {
                gameOver = true;
                winner = currentPlayer->getNom();
            }
            // Vérifier l'égalité
            else if (grid.isFull()) {
                gameOver = true;
                winner = "";
            }
            // Changer de joueur
            else {
                if (currentPlayer == &j1) {
                    currentPlayer = &j2;
                } else {
                    currentPlayer = &j1;
                }
            }
        }
    }
}

GameState Game::getGameState() const {
    return gameState;
}

string Game::getPlayer1Name() const {
    return player1Name;
}

string Game::getPlayer2Name() const {
    return player2Name;
}

int Game::getActiveInput() const {
    return activeInput;
}

void Game::handleTextInput() {
    int key = GetCharPressed();
    while (key > 0) {
        if (key >= 32 && key <= 125) {
            if (activeInput == 1 && player1Name.length() < 15) {
                player1Name += (char)key;
            } else if (activeInput == 2 && player2Name.length() < 15) {
                player2Name += (char)key;
            }
        }
        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE)) {
        if (activeInput == 1 && !player1Name.empty()) {
            player1Name.pop_back();
        } else if (activeInput == 2 && !player2Name.empty()) {
            player2Name.pop_back();
        }
    }

    if (IsKeyPressed(KEY_TAB)) {
        activeInput = (activeInput == 1) ? 2 : 1;
    }

    if (IsKeyPressed(KEY_ENTER)) {
        if (!player1Name.empty() && !player2Name.empty()) {
            j1.setNom(player1Name);
            j2.setNom(player2Name);
            gameState = GameState::PLAYING;
            currentPlayer = &j1;
        } else if (!player1Name.empty() && activeInput == 1) {
            activeInput = 2;
        }
    }
}

void Game::run()
{
    renderer.initWindow();

    while (!WindowShouldClose())
    {
        if (gameState == GameState::NAME_SELECTION) {
            handleTextInput();
        } else {
            // Gestion des événements
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                Vector2 mousePos = GetMousePosition();
                handleMouseClick((int)mousePos.x, (int)mousePos.y);
            }

            // Gestion du redémarrage
            if (gameOver && IsKeyPressed(KEY_R)) {
                grid.reset();
                gameOver = false;
                winner = "";
                currentPlayer = &j1;
            }
        }

        // Dessin
        BeginDrawing();
        if (gameState == GameState::NAME_SELECTION) {
            renderer.drawNameSelection(*this);
        } else {
            renderer.drawBoard(grid, currentPlayer, gameOver, winner);
        }
        EndDrawing();
    }

    renderer.closeWindow();
}
