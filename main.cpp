// ********************************************************* 
// Course: TCP1101 PROGRAMMING FUNDAMENTALS 
// Year: Trimester 1, 2022/23 (T2215) 
// Lab: T13L 
// Names: PANG DING YUAN | FAM YI QI  
// IDs: 1211102575 | 1211101198 
// Emails: 1211102575@student.mmu.edu.my | 1211101198@student.mmu.edu.my 
// Phones: 01110751133 | 0122179918 
// ********************************************************* 

#include "character.h"
#include "command.h"
#include "gameboard.h"
#include <iostream>
using namespace std;

int main()
{
    srand(time(NULL));
    GameBoard board;
    board.gameStart();
    int x = board.getcoX();
    int y = board.getcoY();
    int z = board.getnoOfZombies();
    char **obj = board.getMapObjects();

    Character character(x, y, z);
    character.onMap(board);
    
    Command cmd;
    bool flagContinue = cmd.getFlagContinue();

    do {
        board.display();
        character.display();
        cmd.input();
        flagContinue = cmd.getFlagContinue();
        bool flagArrows = cmd.getFlagArrows();
        bool flagUp = cmd.getFlagUp();
        bool flagDown = cmd.getFlagDown();
        bool flagLeft = cmd.getFlagLeft();
        bool flagRight = cmd.getFlagRight();
        bool flagHelp = cmd.getFlagHelp();
        bool flagSave = cmd.getFlagSave();
        bool flagLoad = cmd.getFlagLoad();
        if (flagArrows == 1) {
            int row;
            int column;
            cout << "Enter row: ";
            cin >> row;
            cout << "Enter column: ";
            cin >> column;
            cmd.arrows(board, row, column);
        }
        else if (flagHelp == 1) {
            cmd.help();
        }
        else if (flagUp == 1){
            cmd.up(board, character, board.getMapObjects());
            board.init(x, y, z, flagUp);
            character.setAlienAttack(0);
        }
        else if (flagDown == 1){
            cmd.down(board, character, board.getMapObjects());
            board.init(x, y, z, flagDown);
            character.setAlienAttack(0);
        }
        else if (flagLeft == 1){
            cmd.left(board, character, board.getMapObjects());
            board.init(x, y, z, flagLeft);
            character.setAlienAttack(0);
        }
        else if (flagRight == 1){
            cmd.right(board, character, board.getMapObjects());
            board.init(x, y, z, flagRight);
            character.setAlienAttack(0);
        }
        else if (flagSave == 1) {
            cmd.save(board, character);
        }
        else if (flagLoad == 1) {
            cmd.load(board, character);
            x = board.getcoX();
            y = board.getcoY();
            z = board.getnoOfZombies();
        }
        cmd.gameend(board, character);
        flagContinue = cmd.getFlagContinue();
    } while(flagContinue == 1);
}