#include "Grid.h"
#include <iostream>

int main(int argc, char const *argv[]){
    Grid grid;
    
    std::cout << "Grille initiale:";
    grid.display();
    
    // Test de placement de symboles
    std::cout << "Placement de X en (0,0): " << (grid.placeSymbol(0, 0, 'X') ? "OK" : "ECHEC") << std::endl;
    std::cout << "Placement de O en (1,1): " << (grid.placeSymbol(1, 1, 'O') ? "OK" : "ECHEC") << std::endl;
    std::cout << "Placement de X en (0,1): " << (grid.placeSymbol(0, 1, 'X') ? "OK" : "ECHEC") << std::endl;
    
    std::cout << "\nGrille apres placements:";
    grid.display();
    
    // Test de placement sur une case occupée
    std::cout << "Tentative de placement de O en (0,0): " << (grid.placeSymbol(0, 0, 'O') ? "OK" : "ECHEC") << std::endl;
    
    
    system("pause");
    return 0;
}