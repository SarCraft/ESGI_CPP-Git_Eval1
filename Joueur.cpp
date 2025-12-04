#include "Joueur.h"

Joueur::Joueur(string n, string s) : nom(n), symbole(s) {}

string Joueur::getNom() const {
    return nom;
}

string Joueur::getSymbole() const{
    return symbole;
}