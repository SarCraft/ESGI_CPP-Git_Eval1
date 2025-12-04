#include "GameRenderer.h"
#include "Game.h"

GameRenderer::GameRenderer() {}

// Crétion de la fen^tre
void GameRenderer::initWindow() {
    InitWindow(screenWidth, screenHeight, "Tic Tac Toe - Raylib");
    SetTargetFPS(60);
}

void GameRenderer::closeWindow() {
    CloseWindow();
}

void GameRenderer::drawBoard(const Grid& grid, const Joueur* currentPlayer, bool gameOver, const string& winner) {
    // Fond blanc
    ClearBackground(RAYWHITE);

    // Afficher le titre en haut et le centre
    DrawText("TIC TAC TOE", screenWidth/2 - MeasureText("TIC TAC TOE", 40)/2, 20, 40, DARKBLUE);

    // Afficher de quel joueur c'est le tour
    if (!gameOver && currentPlayer != nullptr) {
        string currentText = "Tour de " + currentPlayer->getNom() + " (" + string(1, currentPlayer->getSymbole()) + ")";
        // Centre le texte et calcul la taille du texte
        DrawText(currentText.c_str(), screenWidth/2 - MeasureText(currentText.c_str(), 20)/2, 65, 20, DARKGRAY);
    }

    // Dessiner les 4 lignes de la grille (horizontales et verticales)
    for (int i = 0; i <= 3; i++) {
        int x = offsetX + i * cellSize;
        int y = offsetY + i * cellSize;
        
        // Ligne horizontale
        DrawLineEx({(float)offsetX, (float)y}, {(float)(offsetX + cellSize * 3), (float)y}, 3, BLACK);
        // Ligne verticale
        DrawLineEx({(float)x, (float)offsetY}, {(float)x, (float)(offsetY + cellSize * 3)}, 3, BLACK);
    }

    // Dessiner les X et O dans chaque case
    vector<vector<char>> cells = grid.getCells();
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            char symbol = cells[i][j];
            int centerX = offsetX + j * cellSize + cellSize / 2;
            int centerY = offsetY + i * cellSize + cellSize / 2;

            // Dessiner X en rouge
            if (symbol == 'X') {
                DrawLine(centerX - 40, centerY - 40, centerX + 40, centerY + 40, RED);
                DrawLine(centerX + 40, centerY - 40, centerX - 40, centerY + 40, RED);
            }
            // Dessiner O en bleu
            else if (symbol == 'O') {
                DrawCircleLines(centerX, centerY, 50, BLUE);
            }
        }
    }

    // Affichage d'une modal
    if (gameOver) {
        // Couleur et border de la modal
        DrawRectangle(100, 250, 400, 150, Fade(WHITE, 0.9f));
        DrawRectangleLines(100, 250, 400, 150, BLACK);
        
        // Message du gagnant ou match nul
        if (!winner.empty()) {
            string winText = winner + " a gagne!";
            DrawText(winText.c_str(), 300 - MeasureText(winText.c_str(), 30)/2, 290, 30, DARKGREEN);
        } else {
            DrawText("Match nul!", 300 - MeasureText("Match nul!", 30)/2, 290, 30, ORANGE);
        }
        
        // Instructions
        DrawText("Appuyez sur R pour rejouer", 300 - MeasureText("Appuyez sur R pour rejouer", 20)/2, 340, 20, DARKGRAY);
        DrawText("Appuyez sur ESC pour quitter", 300 - MeasureText("Appuyez sur ESC pour quitter", 20)/2, 370, 20, DARKGRAY);
    }
}

bool GameRenderer::getCellFromMouseClick(int mouseX, int mouseY, int& row, int& col) {
    // Utiliser le renderer pour convertir les coordonnées de la souris en cellule
    col = (mouseX - offsetX) / cellSize;
    row = (mouseY - offsetY) / cellSize;

    // Vérifier que le clic est bien dans la grille 3x3
    return (row >= 0 && row < 3 && col >= 0 && col < 3);
}

void GameRenderer::drawNameSelection(const Game& game) {
    ClearBackground(RAYWHITE);

    // Titre principal
    DrawText("TIC TAC TOE", screenWidth/2 - MeasureText("TIC TAC TOE", 50)/2, 80, 50, DARKBLUE);
    DrawText("Configuration des joueurs", screenWidth/2 - MeasureText("Configuration des joueurs", 25)/2, 150, 25, DARKGRAY);

    // Instructions écrtes
    DrawText("Appuyez sur TAB pour changer de champ", screenWidth/2 - MeasureText("Appuyez sur TAB pour changer de champ", 18)/2, 200, 18, GRAY);
    DrawText("Appuyez sur ENTREE pour commencer", screenWidth/2 - MeasureText("Appuyez sur ENTREE pour commencer", 18)/2, 225, 18, GRAY);

    // Saisie Joueur 1
    DrawText("Joueur 1 (X):", 100, 280, 25, DARKBLUE);
    Rectangle input1 = {100, 315, 400, 50};
    
    // Couleur selon si le champ est actif ou non
    Color bgColor1 = (game.getActiveInput() == 1) ? Fade(SKYBLUE, 0.3f) : Fade(LIGHTGRAY, 0.3f);
    Color borderColor1 = (game.getActiveInput() == 1) ? BLUE : DARKGRAY;
    
    DrawRectangleRec(input1, bgColor1);
    DrawRectangleLinesEx(input1, 3, borderColor1);
    
    string player1Name = game.getPlayer1Name();
    if (player1Name.empty()) {
        DrawText("Entrez le nom...", 110, 330, 20, GRAY);
    } else {
        DrawText(player1Name.c_str(), 110, 330, 20, BLACK);
    }

    // Saisie Joueur 2
    DrawText("Joueur 2 (O):", 100, 400, 25, DARKGREEN);
    Rectangle input2 = {100, 435, 400, 50};
    
    Color bgColor2 = (game.getActiveInput() == 2) ? Fade(DARKGREEN, 0.3f) : Fade(LIGHTGRAY, 0.3f);
    Color borderColor2 = (game.getActiveInput() == 2) ? DARKGREEN : DARKGRAY;
    
    DrawRectangleRec(input2, bgColor2);
    DrawRectangleLinesEx(input2, 3, borderColor2);
    
    string player2Name = game.getPlayer2Name();
    if (player2Name.empty()) {
        DrawText("Entrez le nom...", 110, 450, 20, GRAY);
    } else {
        DrawText(player2Name.c_str(), 110, 450, 20, BLACK);
    }

    // Bouton commencer
    bool canStart = !player1Name.empty() && !player2Name.empty();
    Rectangle startButton = {200, 550, 200, 60};
    
    Color buttonColor = canStart ? Fade(GREEN, 0.8f) : Fade(GRAY, 0.5f);
    Color buttonBorder = canStart ? DARKGREEN : DARKGRAY;
    
    DrawRectangleRec(startButton, buttonColor);
    DrawRectangleLinesEx(startButton, 2, buttonBorder);
    DrawText("COMMENCER", 225, 570, 20, WHITE);
}
