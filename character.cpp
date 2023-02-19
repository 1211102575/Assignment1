#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "command.h"
#include "character.h"
#include "gameboard.h"
using namespace std;

Character::Character(int x, int y, int z)
    :health_(100), 
     damage_(0), 
     range_(1)
{
    coX_ = x;
    coY_ = y;
    noOfZombies_ = z;
    init();
}

//map rowcolumnnumber
void Character::setAlienLocation(int x, int y)
{
    alienAttribute_[3] = x;
    alienAttribute_[4] = y;
}

void Character::setAlienHealth(int newHealth)
{
    alienAttribute_[0] = newHealth;
}

void Character::setAlienAttack(int damage) {
    alienAttribute_[1] = damage;
}

void Character::setNoOfZombies(int zombies) {
    noOfZombies_ = zombies;
}

void Character::setZombieHealth(int whichzombie, int health)
{
    zombieAttribute_[whichzombie][0] = health;
}

void Character::loadAlienAttribute(int health, int damage, int range, int x, int y){
    alienAttribute_[0] = health;
    alienAttribute_[1] = damage;
    alienAttribute_[2] = range;
    alienAttribute_[3] = x;
    alienAttribute_[4] = y;
}

void Character::loadZombieAttribute(int number, int health, int damage, int range, int x, int y) {
    zombieAttribute_[number][0] = health;
    zombieAttribute_[number][1] = damage;
    zombieAttribute_[number][2] = range;
    zombieAttribute_[number][3] = x;
    zombieAttribute_[number][4] = y;
}

void Character::onMap(GameBoard &gameboard) {
    xAlien_ = coX_ / 2 + 1;
    yAlien_ = coY_ / 2 + 1;

    alienAttribute_[3] = xAlien_;
    alienAttribute_[4] = yAlien_;

    for (int i = 0; i < noOfZombies_; ++i) { 
        int x;
        int y;
        x = (rand() % coX_) + 1;
        y = (rand() % coY_) + 1;
        zombieAttribute_[i][3] = x;
        zombieAttribute_[i][4] = y;
        if (i == 0) {
            while ((zombieAttribute_[i][3] == alienAttribute_[3]) && (zombieAttribute_[i][4] == alienAttribute_[4])) {
                x = (rand() % coX_) + 1;
                y = (rand() % coY_) + 1;
                zombieAttribute_[i][3] = x;
                zombieAttribute_[i][4] = y;
            }
        }
        for (int j = 0; j < i; ++j) {
            int flagRepeat = 0;
            while (flagRepeat == 0 || (((zombieAttribute_[i][3] == alienAttribute_[3]) && (zombieAttribute_[i][4] == alienAttribute_[4])) || ((zombieAttribute_[i][3] == zombieAttribute_[j][3]) && (zombieAttribute_[i][4] == zombieAttribute_[j][4])))) {
                if (((zombieAttribute_[i][3] == alienAttribute_[3]) && (zombieAttribute_[i][4] == alienAttribute_[4])) || ((zombieAttribute_[i][3] == zombieAttribute_[j][3]) && (zombieAttribute_[i][4] == zombieAttribute_[j][4]))) {
                    x = (rand() % coX_) + 1;
                    y = (rand() % coY_) + 1;
                    zombieAttribute_[i][3] = x;
                    zombieAttribute_[i][4] = y;
                }
                else {
                    for (int k = 0;  k < i; ++k) {
                        while (((zombieAttribute_[i][3] == alienAttribute_[3]) && (zombieAttribute_[i][4] == alienAttribute_[4])) || ((zombieAttribute_[i][3] == zombieAttribute_[k][3]) && (zombieAttribute_[i][4] == zombieAttribute_[k][4]))) {
                            x = (rand() % coX_) + 1;
                            y = (rand() % coY_) + 1;
                            zombieAttribute_[i][3] = x;
                            zombieAttribute_[i][4] = y;
                        }
                    }
                    flagRepeat = flagRepeat + 1;      
                }
            }
        }
        char a = 49 + i;
        gameboard.characterOnMap(zombieAttribute_[i][3], zombieAttribute_[i][4], a);
    }
    gameboard.characterOnMap(xAlien_, yAlien_, 'A');
}

//to create character attribute
void Character::init(bool load) {
    if (load == 1)
    {
        zombieAttribute_ = new int*[noOfZombies_];
        for(int i = 0; i < noOfZombies_; ++i) {
            zombieAttribute_[i] = new int[5];
        }
    }
    else 
    {
        alienAttribute_ = new int[5];
        alienAttribute_[0] = health_;
        alienAttribute_[1] = damage_;
        alienAttribute_[2] = range_;

        zombieAttribute_ = new int*[noOfZombies_];
        for(int i = 0; i < noOfZombies_; ++i) {
            zombieAttribute_[i] = new int[5];
        }
        
        int zombieHealth[] = {100, 150, 200, 250, 300};
        int choiceOfHealth = 5;
        
        for (int i = 0; i < noOfZombies_; ++i) {
            int health = rand() % choiceOfHealth;
            zombieAttribute_[i][0] = zombieHealth[health];
        }

        int zombieDamage[] = {5, 10, 15, 100};
        int choiceOfDamage = 4;

        for (int i = 0; i < noOfZombies_; ++i) {
            int damage = rand() % choiceOfDamage;
            zombieAttribute_[i][1] = zombieDamage[damage];
        }

        int zombieRange[] = {1, 2, 3};
        int choiceOfRange = 4;

        for (int i = 0; i < noOfZombies_; ++i) {
            int range = rand() % choiceOfRange;
            zombieAttribute_[i][2] = zombieRange[range];
        }
    }
    
}


void Character::display() const{
    cout << "Alien"
         << setw(6) << ": "
         << "Health " << alienAttribute_[0]
         << ", " << "Attack " << setw(1)
         << alienAttribute_[1] << endl;

    for(int i = 0; i < noOfZombies_; ++i) {
        cout << "Zombie " << i + 1 
             << setw(2) << " : "
             << "Health " << zombieAttribute_[i][0]
             << ", " << "Attack" << setw(3)
             << zombieAttribute_[i][1]
             << ", Range " << zombieAttribute_[i][2] << endl;
    }
}

int *Character::getAlienAttribute() {
    return alienAttribute_;
}

int **Character:: getZombieAttribute(){
    return zombieAttribute_;
}

int Character ::getNoOfZombie()
{
    return noOfZombies_;
}


// void Character::zombieMovement() {
//     for (int i = 0; i < noOfZombies_; ++i) {
//         int zomNext = zombieAttribute_[i][3] +  
//     }
// }
// void isEMpty ()
// {
// }

// int main() {
//     srand(1);
//     GameBoard board;
//     board.gameStart();
//     int x = board.getcoX();
//     int y = board.getcoY();
//     int z = board.getnoOfZombies();
//     char **obj = board.getMapObjects();

//     Character character(x, y, z);
//     character.onMap(board);
//     board.display();
//     character.display();

// }