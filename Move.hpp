#ifndef MOVE_H
#define MOVE_H

#include <iostream>
#include <cstdlib>
#include <string>
#include "Position.hpp"

using namespace std;

class Move {
    private:
        Position *p;
    public:
        Move();
        Position* getPos();
        int getFristAction();
        bool getMove();
        bool isPossible(int t);
        void inverser(int t);
};

#endif