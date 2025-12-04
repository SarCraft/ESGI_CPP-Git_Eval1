#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

Game::Game() : j1("Joueur1", 'X'), j2("Joueur2", 'O'), grid(), gameOver(false), winner(""), 
               gameState(GameState::MODE_SELECTION), gameMode(GameMode::PVP), player1Name(""), player2Name(""), activeInput(1){
    // Initialiser le générateur de nombres aléatoires pour le bot
    srand(time(nullptr));
}

void Game::handleMouseClick(int mouseX, int mouseY)
{
    if (gameOver) return;

    // En mode PVE, seul le joueur 1 peut cliquer
    if (gameMode == GameMode::PVE && currentPlayer != &j1) {
        return;
    }

    int row, col;
    
    // Utiliser le renderer pour convertir les coordonnées de la souris en cellule
    if (renderer.getCellFromMouseClick(mouseX, mouseY, row, col)) {
        // Essayer de placer le symbole
        if (grid.placeSymbol(row, col, currentPlayer->getSymbole())) {
            // Vérifier la victoire
            if (grid.checkWin(currentPlayer->getSymbole())) {
                gameOver = true;
                winner = currentPlayer->getNom();
                return;
            }
            // Vérifier l'égalité
            else if (grid.isFull()) {
                gameOver = true;
                winner = "";
                return;
            }
            // Changer de joueur
            else {
                if (currentPlayer == &j1) {
                    currentPlayer = &j2;
                    
                    // En mode PVE, faire jouer le bot automatiquement
                    if (gameMode == GameMode::PVE) {
                        botTurn();
                    }
                } else {
                    currentPlayer = &j1;
                }
            }
        }
    }
}

void Game::botTurn() {
    if (gameOver) return;
    
    // Attendre un peu pour que ce soit plus naturel (simulé visuellement)
    int row, col;
    
    // Le bot choisit une case aléatoire parmi les cases vides
    do {
        row = rand() % 3;
        col = rand() % 3;
    } while (!grid.placeSymbol(row, col, currentPlayer->getSymbole()));
    
    // Vérifier la victoire du bot
    if (grid.checkWin(currentPlayer->getSymbole())) {
        gameOver = true;
        winner = currentPlayer->getNom();
        return;
    }
    
    // Vérifier l'égalité
    if (grid.isFull()) {
        gameOver = true;
        winner = "";
        return;
    }
    
    // Redonner le tour au joueur
    currentPlayer = &j1;
}

GameState Game::getGameState() const {
    return gameState;
}

GameMode Game::getGameMode() const {
    return gameMode;
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

void Game::handleModeSelection(int mouseX, int mouseY) {
    // Bouton PVP
    if (mouseX >= 150 && mouseX <= 450 && mouseY >= 300 && mouseY <= 380) {
        gameMode = GameMode::PVP;
        gameState = GameState::NAME_SELECTION;
    }
    // Bouton PVE
    else if (mouseX >= 150 && mouseX <= 450 && mouseY >= 400 && mouseY <= 480) {
        gameMode = GameMode::PVE;
        gameState = GameState::NAME_SELECTION;
        player2Name = "Bot";
    }
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
        if (gameMode == GameMode::PVE) {
            // Mode contre le bot : seul le nom du joueur 1 est requis
            if (!player1Name.empty()) {
                j1.setNom(player1Name);
                j2.setNom("Bot");
                gameState = GameState::PLAYING;
                currentPlayer = &j1;
            }
        } else {
            // Mode PVP : les deux noms sont requis
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
}

void Game::run()
{
    renderer.initWindow();

    while (!WindowShouldClose())
    {
        if (gameState == GameState::MODE_SELECTION) {
            // Gestion du clic pour sélectionner le mode
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                Vector2 mousePos = GetMousePosition();
                handleModeSelection((int)mousePos.x, (int)mousePos.y);
            }
        } else if (gameState == GameState::NAME_SELECTION) {
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
        if (gameState == GameState::MODE_SELECTION) {
            renderer.drawModeSelection();
        } else if (gameState == GameState::NAME_SELECTION) {
            renderer.drawNameSelection(*this);
        } else {
            renderer.drawBoard(grid, currentPlayer, gameOver, winner);
        }
        EndDrawing();
    }

    renderer.closeWindow();
}
