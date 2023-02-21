#include <iostream>
#include <string>
#include "character.h"
#ifndef COMMAND_H
#define COMMAND_H
#include "gameboard.h"
using namespace std;

class Command {
private:
    string command_;
    bool flagArrows_;
    bool flagContinue_;
    bool flagUp_;
    bool flagDown_;
    bool flagLeft_;
    bool flagRight_;
    bool flagHelp_;
    bool flagSave_;
    bool flagLoad_;


public:
    Command();

    void run();
    string input();
    // int getX();
    // int getY();
    bool getFlagArrows();
    bool getFlagContinue();
    bool getFlagUp();
    bool getFlagDown();
    bool getFlagLeft();
    bool getFlagRight();
    bool getFlagHelp();
    bool getFlagSave();
    bool getFlagLoad();

    void gameend(GameBoard &gameboard, Character &character);

    void up(GameBoard &gameboard, Character &character, char** obj);
    void arrows(GameBoard &gameboard, int x, int y);
    void help();
    void save(GameBoard &gameboard, Character &character);
    void load(GameBoard &gameboard, Character &character);
    void quit();
    void down(GameBoard &gameboard,Character &character, char** obj);
    void left (GameBoard &gameboard,Character &character, char** obj);
    void right (GameBoard &gameboard,Character &character, char** obj);
    void zombiemovement(GameBoard &gameboard, Character &character);
};
#endif