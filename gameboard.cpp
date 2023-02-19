#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "gameboard.h"
#include "character.h"
#include "command.h"
using namespace std;

GameBoard::GameBoard() {}

namespace pauCle {
    int Pause()
    {
        #if defined(_WIN32)
            return std::system("pause");
        #elif defined(__linux__) || defined(__APPLE__)
            return std::system(R"(read -p "Press any key to continue . . . " dummy)");
        #endif
    }

    int ClearScreen()
    {
        #if defined(_WIN32)
            return std::system("cls");
        #elif defined(__linux__) || defined(__APPLE__)
            return std::system("clear");
        #endif
    }
}

int GameBoard::getcoX() const {
    return coX_;
}

int GameBoard::getcoY() const{
    return coY_;
}

int GameBoard::getnoOfZombies() const {
    return noOfZombies_;
}

char **GameBoard::getMapObjects() {
    return coordinate_;
}


void GameBoard::gameStart() {
    coX_ = 11;
    coY_ = 5;
    noOfZombies_ = 1;
    
    cout << " Default Game Settings " << endl;
    cout << "-----------------------" << endl;
    cout << "Board Rows   " << ": " << coX_ << endl;
    cout << "Board Columns" << ": " << coY_ << endl;
    cout << "Zombie Count " << ": " << noOfZombies_ << endl;
    cout << endl;
    cout << "Do you wish to change the game settings (y/n)? => ";
    char yon;
    cin >> yon;
    if(yon == 'y') {
        pauCle::ClearScreen();
        boardSetting();
    }
    else if(yon == 'n') {
        init(coX_, coY_, noOfZombies_);
        cout << "Creating gameboard." << endl;
        pauCle::Pause();
        pauCle::ClearScreen();
    }
}

void GameBoard::boardSetting() {
    int newCoX;
    int newCoY;
    int newZombies;
    bool flagBoardSetting = 1;
    do {
        cout << "Customizing Game Board" << endl;
        cout << "-----------------------" << endl;
        cout << "Enter rows => ";
        cin >> newCoX;
        if ((newCoX % 2 == 0) || newCoX < 1) {
            flagBoardSetting = 1;
            cout << "Please Enter An Positive Odd Number!" << endl;
            pauCle::Pause();
            pauCle::ClearScreen();
        }
        else {
            flagBoardSetting = 0;
            cout << "Enter column => ";
            cin >> newCoY;
            if ((newCoY % 2 == 0) || newCoY < 1) {
                flagBoardSetting = 1;
                cout << "Please Enter An Positive Odd Number!" << endl;
                pauCle::Pause();
                pauCle::ClearScreen();
            }
            else {
                flagBoardSetting = 0;
                cout << endl;
                cout << "Number of Zombies" << endl;
                cout << "------------------" << endl;
                cout << "Enter number of zombies => ";
                cin >> newZombies;
                if (newZombies < 1) {
                    cout << endl << "Must Have At least One Zombie!" << endl;
                    pauCle::Pause();
                    pauCle::ClearScreen();
                    flagBoardSetting = 1;
                }
                else {
                flagBoardSetting = 0;
                }
            }
        }
    } while (flagBoardSetting == 1);
    init(newCoX, newCoY, newZombies);
}

void GameBoard::init(int coX, int coY, int noOfZombies, bool cleanUp) {
    coX_ = coX;
    coY_ = coY;
    noOfZombies_ = noOfZombies;

    char objects[] = {' ', ' ', ' ', '^', 'v', '<', '>', 'h', 'p', 'r'};
    int noOfObjects = 10;

    if (cleanUp == 1) {
        for (int i = 0; i < coY_; ++i) {
            for (int j = 0; j < coX_; ++j) {
                if (coordinate_ [i][j]== '#') {
                    int randNum = rand() % noOfObjects;
                    coordinate_[i][j] = objects[randNum];
                }
            }
        }
    }
    else {
        coordinate_ = new char*[coY_]; //https://www.sololearn.com/learn/courses/c-plus-plus-introduction/lesson/421714254?p=2
        for (int i = 0; i < coY_; ++i) {
            coordinate_[i] = new char[coX_];
        }

        for (int i = 0; i < coY_; ++i) {
            for (int j = 0; j < coX_; ++j) {
                int randNum = rand() % noOfObjects;
                coordinate_[i][j] = objects[randNum];
            }
        }
    }
}

void GameBoard::display() const {
    cout << "* * *.----------------. * * *" << endl;
    cout << "* *. .Alien VS Zombie . . * *" << endl;
    cout << "*. . .----------------. . . *" << endl;

    for (int i = 0; i < coY_; ++i) {
        cout << setw(2) << (coY_ - i);
        for (int j = 0; j < coX_; ++j) {
           cout << "|" << coordinate_[i][j];
        }
        cout << "|" << endl;

        cout << setw(4);
        if (i == coY_ - 1) {
            break;
        }
        for (int j = 0; j < coX_; j++) {
            cout << "|~";
        }
        cout << "|" << endl;       
    }
    
    cout << setw(5);
    for (int j = 1; j <= coX_; ++j) {
        if ((j / 10) == 0) {
            cout << "  ";
        }
        else {
            cout << (j / 10) << " ";
        }
    }
    cout << endl;

    cout << setw(4);
    for (int j = 1; j <= coX_; ++j) {
        cout << j % 10 << " ";
    }
    cout << endl << endl;
}

void GameBoard::characterOnMap(int x, int y, char ch) {
    coordinate_[coY_ - y][x - 1] = ch;
}


// int main() {
//     GameBoard board;

// }