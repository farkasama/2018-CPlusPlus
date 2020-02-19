#include "Move.hpp"

Move::Move(){
    p = new Position();
}

Position* Move::getPos() {
    return p;
}

int Move::getFristAction() {
    string deplacement;
    getline(cin, deplacement);

    for (auto & c: deplacement) c = toupper(c);

    if (deplacement.compare("DEPLACER") == 0 || deplacement.compare("MOVE") == 0 ) {
        return 1;
    }

    if (deplacement.compare("ABANDONNER") == 0) {
        cout << "Vous avez abandonner" << endl;
        return 2;
    }
    if(deplacement.compare("SAVE") == 0 || deplacement.compare("SAUVEGARDE") == 0){
        return 3;
    }
    if (deplacement.compare("HELP") == 0 || deplacement.compare("AIDE") == 0)
        return 4;
    if (deplacement.compare("RETOUR")==0 || deplacement.compare("BACK") == 0) {
        return 5;
    } 
    return 0;
}


bool Move::getMove(){
    string deplacement;
    getline(cin, deplacement);

    for (auto & c: deplacement) c = toupper(c);

    
    if (deplacement.length() == 2) {

        if (deplacement[0] >= 'A' && deplacement[0] <= 'Z'
            && deplacement[1] >= '1' && deplacement[1] <= '9'){
            p->setY(deplacement[0]-'A');
            p->setX(deplacement[1]-'0');
            return true;
        }

        else if (deplacement[1] >= 'A' && deplacement[1] <= 'Z'
            && deplacement[0] >= '1' && deplacement[0] <= '9'){
                p->setY(deplacement[1]-'A');
                p->setX(deplacement[0]-'0');
                return true;
            }
    }

    else if (deplacement.length() == 3) {

        if (deplacement[0] >= 'A' && deplacement[0] <= 'Z'
            && deplacement[1] >= '1' && deplacement[1] <= '9'
            && deplacement[2] >= '0' && deplacement[2] <= '9') {
                p->setY(deplacement[0]-'A');
                p->setX((deplacement[1]-'0')*10 + deplacement[2]-'0');
                return true;
            }

        else if (deplacement[2] >= 'A' && deplacement[2] <= 'Z'
            && deplacement[0] >= '1' && deplacement[0] <= '9'
            && deplacement[1] >= '0' && deplacement[1] <= '9') {
                p->setY(deplacement[2]-'A');
                p->setX((deplacement[0]-'0')*10 + deplacement[1]-'0');
                return true;
            }
    }
    return false;
}

bool Move::isPossible(int t) {
    if (p->getX() >= 0 && p->getX() < t) {
        if (p->getY() >= 0 && p->getY() < t) {
            return true; 
        }
    }
    return false;
}

void Move::inverser(int t) {
    p->setX(t-p->getX());
}