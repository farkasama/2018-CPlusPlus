#include "Position.hpp"

Position::Position(){}

Position::Position(int a, int b) {
    this->x = a;
    this->y = b;
}

void Position::setX(int a) {
    this->x = a;
}

void Position::setY(int a) {
    this->y = a;
}

int Position::getX() {
    return this->x;
}

int Position::getY() {
    return this->y;
}

bool Position::equals (Position *p) {
    if (x == p->getX() && y == p->getY())
        return true;
    return false;
}