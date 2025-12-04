#include "Joueur.h"

Joueur::Joueur(string n, char s) : nom(n), symbole(s) {}

string Joueur::getNom() const {
    return nom;
}

void Joueur::setNom(const string n){
    nom = n;
}

char Joueur::getSymbole(){
    return symbole;
}
