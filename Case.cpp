#include "Case.hpp"

Case::Case(int x, int y, bool c) : pos(x,y), couleur(c), p(false) {
    this->pion = nullptr;
}

Case::~Case() {
    if (p) {
        delete pion;
    }
}

Pion* Case::getPion() {
    return pion;
}

Pion* Case::getPionWithDelete() {
    Pion* a = pion;
    p = false;
    pion = nullptr;
    return a;
}

void Case::setPion(Pion* p) {
    this->p = true;
    this->pion = p;
}

char Case::toStringCouleur() {
    if (couleur)
        return 'B';
    return 'N';
}

char Case::toStringPion() {
    if (p)
        return pion->toString();
    return ' ';
}

bool Case::caseEstBlanche() {
    if (couleur) {
        return true;
    }
    return false;
}

bool Case::caseEstNoir() {
    if(!couleur)
        return true;
    return false;
}

bool Case::ifPion() {
    return p;
}

bool Case::canMoveTo(int x, int y) {
    return pion->canMoveTo(x,y);
}

Pion* Case::supprimerPion() {
    p = false;
    Pion* a = pion;
    pion = nullptr;
    return a;
}