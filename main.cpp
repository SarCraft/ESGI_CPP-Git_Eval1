#include "Grid.h"
#include <iostream>

using namespace std;

int main(){
    Grid grid;
    
    cout << "Grille initiale:";
    grid.display();
    
    // Test de placement de symboles
    cout << "Placement de X en (0,0): " << (grid.placeSymbol(0, 0, 'X') ? "OK" : "ECHEC") << endl;
    cout << "Placement de O en (1,1): " << (grid.placeSymbol(1, 1, 'O') ? "OK" : "ECHEC") << endl;
    cout << "Placement de X en (0,1): " << (grid.placeSymbol(0, 1, 'X') ? "OK" : "ECHEC") << endl;
    
    cout << "\nGrille apres placements:";
    grid.display();
    
    // Test de placement sur une case occupée
    cout << "Tentative de placement de O en (0,0): " << (grid.placeSymbol(0, 0, 'O') ? "OK" : "ECHEC") << endl;
    
    system("pause");
    return 0;
}