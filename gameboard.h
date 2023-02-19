#include <iostream>
#ifndef GAMEBOARD_H
#define GAMEBOARD_H

class GameBoard {
protected:
    char **coordinate_;
    int coX_, coY_;
    int noOfZombies_;

public:
    GameBoard();
    void gameStart();

    void boardSetting();

    void init(int coX, int coY, int noOfZombies, bool cleanUp = 0);

    void display() const;

    int getcoX() const;
    int getcoY() const;
    int getnoOfZombies() const;
    char **getMapObjects();

    void characterOnMap(int x, int y, char ch);
};

namespace pauCle {
    int ClearScreen();
    int Pause();
}

#endif