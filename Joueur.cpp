#include "Joueur.h"

Joueur::Joueur(string n, string s) : nom(n), symbole(s) {}

string Joueur::getNom() const {
    return nom;
}

void Joueur::setNom(const string n){
    nom = n;
}

string Joueur::getSymbole() const{
    return symbole;
}

void Joueur::setSymbole(const string s){
    symbole = s;
}