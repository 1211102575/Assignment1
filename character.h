#include <iostream>
#include <string>
#include "gameboard.h"
#ifndef CHARACTER_H
#define CHARACTER_H

class Character {
private:
    int coX_;
    int coY_;
    int noOfZombies_;
    int xAlien_;
    int yAlien_;
    int health_, damage_, range_;
    int *alienAttribute_;
    int **zombieAttribute_;

public:
    Character(int x, int y, int z);
//    Character(int health, int damage, int range, int noOfZombies);
    void onMap(GameBoard &gameboard);
    void init(bool load = 0);
    void display() const;

    int* getAlienAttribute();
    int** getZombieAttribute();
    int getNoOfZombie();
    void zombieMovement();
    void setNoOfZombies(int zombies);
    void setAlienLocation(int x, int y);
    void setAlienHealth(int health);
    void setAlienAttack(int damage);
    void setZombieHealth(int whichzombie, int health);
    void loadAlienAttribute(int health, int damage, int range, int x, int y);
    void loadZombieAttribute(int number, int health, int damage, int range, int x, int y);
};
#endif