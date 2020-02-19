#include "Pion.hpp"

Pion::Pion(){}

Pion::Pion(int x, int y, bool c){
    this->pos = new Position(x, y);
    couleur = c;
}

Pion::~Pion() {
    delete pos;
}


Position* Pion::getPos() {
    return this->pos;
}

void Pion::setPos(int x, int y) {
    this->pos->setX(x);
    this->pos->setY(y);
}

char Pion::toStringCouleur() {
    if (couleur) {
        return 'B';
    }
    return 'N';
}

char Pion::toString() {
    return 'X';
}

bool Pion::canMoveTo(int x, int y) {
    return false;
}

bool Pion::getCouleur() {
    return couleur;
}

bool Pion::estUneDame() {
    return false;
}

bool Pion::estUnPionEchec() {
    return false;
}

bool Pion::estUnCavalier() {
    return false;
}

bool Pion::estUnRoi() {
    return false;
}














/*
*
##################################################################
#                       CLASS JEU DE DAME                        #
##################################################################
*
*/

// Classe Jeu de Dame PION BLANC

PionBlanc::PionBlanc(int x, int y) : Pion(x, y, true) {}

char PionBlanc::toString() {
    return 'B';
}

PionBlanc::~PionBlanc() {
    delete pos;
}

bool PionBlanc::canMoveTo(int x, int y) {
    if (pos->getX()-1 == x) {
        if (pos->getY()-1 == y || pos->getY()+1 == y) {
            return true;
        }
    }
    return false;
}

bool PionBlanc::estUneDame() {
    return false;
}


// Classe Jeu de Dame Pion NOIR

PionNoir::PionNoir(int x, int y) : Pion(x, y, false) {}

PionNoir::~PionNoir() {
    delete pos;
}

char PionNoir::toString() {
    return 'N';
}

bool PionNoir::canMoveTo(int x, int y) {
    if (pos->getX()+1 == x) {
        if (pos->getY()-1 == y || pos->getY()+1 == y) {
            return true;
        }
    }
    return false;
}

bool PionNoir::estUneDame() {
    return false;
}

// Classe Jeu de Dame Pion Dame BLANCHE

PionDameBlanche::PionDameBlanche(int x, int y) : Pion(x, y, true) {}

PionDameBlanche::~PionDameBlanche() {
    delete pos;
}

char PionDameBlanche::toString() {
    return 'D';
}

bool PionDameBlanche::canMoveTo(int x, int y) {
    if (pos->getX()-x == pos->getY()-y ||
        pos->getX()-x == (-1)*(pos->getY()-y))
        return true;
    return false;
}

bool PionDameBlanche::estUneDame() {
    return true;
}


// Classe Jeu de D Pion Dame NOIRE

PionDameNoire::PionDameNoire(int x, int y) : Pion(x, y, false) {}

PionDameNoire::~PionDameNoire() {
    delete pos;
}

char PionDameNoire::toString() {
    return 'Q';
}

bool PionDameNoire::canMoveTo(int x, int y) {
    if (pos->getX()-x == pos->getY()-y ||
        pos->getX()-x == (-1)*(pos->getY()-y))
        return true;
    return false;
}

bool PionDameNoire::estUneDame() {
    return true;
}













/*
*
##################################################################
#                       CLASS JEU D'ECHEC                        #
##################################################################
*
*/


/*
*      +-----------+
*      | Pion noir |
*      +-----------+
*/

PionEchecNoir::PionEchecNoir(int x, int y) : Pion(x, y, false) {
    premierMove = true;
}

PionEchecNoir::~PionEchecNoir() {
    delete pos;
}

bool PionEchecNoir::canMoveTo(int x, int y) {
    if (premierMove && y == pos->getY() && (x-2 == pos->getX() || x-1 == pos->getX())) {
        premierMove = false;
        return true;
    }
    else if (!premierMove && abs(pos->getY()-y) < 2 && x-1 == pos->getX())
        return true;
    return false;
}

char PionEchecNoir::toString() {
    return 'P';
}

bool PionEchecNoir::estUnPionEchec() {
    return true;
}



/*
*      +------------+
*      | Pion blanc |
*      +------------+
*/

PionEchecBlanc::PionEchecBlanc(int x, int y) : Pion (x, y, true) {
    premierMove = true;
}

PionEchecBlanc::~PionEchecBlanc() {
    delete pos;
}

bool PionEchecBlanc::canMoveTo(int x, int y) {
    if (premierMove && y == pos->getY() && (x+2 == pos->getX() || x+1 == pos->getX())) {
        premierMove = false;
        return true;
    }
    else if (!premierMove && abs(pos->getY()-y) < 2 && x+1 == pos->getX())
        return true;
    return false;
}

char PionEchecBlanc::toString() {
    return 'P';
}

bool PionEchecBlanc::estUnPionEchec() {
    return true;
}



/*
*      +-----------+
*      | Pion tour |
*      +-----------+
*/

PionTour::PionTour(int x, int y, bool c) : Pion(x, y, c){}

PionTour::~PionTour() {
    delete pos;
}

bool PionTour::canMoveTo(int x, int y) {
    if (pos->getX() == x || pos->getY() == y)
        return true;
    return false;
}

char PionTour::toString() {
    return 'T';
}


/*
*      +---------------+
*      | Pion cavalier |
*      +---------------+
*/


PionCavalier::PionCavalier(int x, int y, bool c) : Pion(x, y, c){}

PionCavalier::~PionCavalier() {
    delete pos;
}

bool PionCavalier::canMoveTo(int x, int y) {
    if (abs(pos->getX()-x) == 2 && abs(pos->getY()-y) == 1)
        return true;
    if (abs(pos->getY()-y) == 2 && abs(pos->getX())-x == 1)
        return true;
    return false;
}

char PionCavalier::toString() {
    return 'C';
}

bool PionCavalier::estUnCavalier() {
    return true;
}


/*
*      +----------+
*      | Pion fou |
*      +----------+
*/


PionFou::PionFou(int x, int y, bool c) : Pion(x, y, c) {}

PionFou::~PionFou() {
    delete pos;
}

bool PionFou::canMoveTo(int x, int y) {
    if (abs(pos->getX()-x) == abs(pos->getY()-y))
        return true;
    return false;
}

char PionFou::toString() {
    return 'F';
}


/*
*      +------------+
*      | Pion reine |
*      +------------+
*/

PionReine::PionReine(int x, int y, bool c) : Pion(x, y, c){}

PionReine::~PionReine() {
    delete pos;
}

bool PionReine::canMoveTo(int x, int y) {
    if (pos->getX() == x ||
        pos->getY() == y ||
        abs(pos->getX()-x) == abs(pos->getY()-y))
        return true;
    return false;
}

char PionReine::toString() {
    return 'Q';
}


/*
*      +----------+
*      | Pion roi |
*      +----------+
*/

PionRoi::PionRoi(int x, int y, bool c) : Pion(x, y, c) {}

PionRoi::~PionRoi() {
    delete pos;
}

bool PionRoi::canMoveTo(int x, int y) {
    if (abs(pos->getX()-x) >= 2 ||
        abs(pos->getY()-y) >= 2)
        return false;
    return true;
}

char PionRoi::toString() {
    return 'K';
}

bool PionRoi::estUnRoi() {
    return true;
}














/*
*
##################################################################
#                       CLASS JEU DE MAKRUK                      #
##################################################################
*
*/


/*
*      +-------------+
*      | Pion graine |
*      +-------------+
*/ 


PionGraine::PionGraine(int x, int y, bool c) : Pion(x, y, c) {}

PionGraine::~PionGraine() {
    delete pos;
}

bool PionGraine::canMoveTo(int x, int y) {
    if (pos->getX() == x || pos->getY() == y ||
        abs(pos->getX()-x) >= 2 ||
        abs(pos->getY()-y) >= 2)
        return false;
    return true;
}

char PionGraine::toString() {
    return 'G';
}


/*
*      +------------+
*      | Pion noble |
*      +------------+
*/ 


PionNoble::PionNoble(int x, int y, bool c) : Pion(x, y, c) {}

PionNoble::~PionNoble() {
    delete pos;
}

bool PionNoble::canMoveTo(int x, int y) {
    if (couleur) {
        if (x-1 == pos->getX() && abs(y-pos->getY()) <= 1)
            return true;
        else if (x+1 == pos->getX() && abs(y-pos->getY()) == 1)
            return true;
    }
    else {
        if (x+1 == pos->getX() && abs(y-pos->getY()) <= 1)
            return true;
        else if (x+1 == pos->getX() && abs(y-pos->getY()) == 1)
            return true;
    }
    return false;
}

char PionNoble::toString() {
    return 'N';
}