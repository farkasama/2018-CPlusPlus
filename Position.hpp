#ifndef POSITION_H
#define POSITION_H

class Position {
    private:
        int x;
        int y;
    public:
        Position();
        Position(int, int);
        int getX();
        int getY();
        void setX(int);
        void setY(int);
        bool equals(Position* p);
};

#endif