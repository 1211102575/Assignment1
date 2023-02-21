#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include "command.h"
#include "gameboard.h"
#include "character.h"
using namespace std;

Command::Command() 
    :flagContinue_(1),
     flagArrows_(0),
     flagUp_(0),
     flagDown_(0),
     flagLeft_(0),
     flagRight_(0),
     flagHelp_(0),
     flagSave_(0),
     flagLoad_(0)
{}

string Command::input() {
    cout << "command> ";
    cin >> command_;
    if(command_ == "help") {
        flagArrows_ = 0,
        flagContinue_ = 1,
        flagUp_ = 0,
        flagDown_ = 0,
        flagLeft_ = 0,
        flagRight_ = 0,
        flagHelp_ = 1,
        flagSave_ = 0,
        flagLoad_ = 0;
    }
    else if(command_ == "arrow") {
        flagArrows_ = 1,
        flagContinue_ = 1,
        flagUp_ = 0,
        flagDown_ = 0,
        flagLeft_ = 0,
        flagRight_ = 0,
        flagHelp_ = 0,
        flagSave_ = 0,
        flagLoad_ = 0;
    }
    else if(command_ == "up") {
        flagArrows_ = 0,
        flagContinue_ = 1,
        flagUp_ = 1,
        flagDown_ = 0,
        flagLeft_ = 0,
        flagRight_ = 0,
        flagHelp_ = 0,
        flagSave_ = 0,
        flagLoad_ = 0;
    }
    else if(command_ == "down") 
    {
        flagArrows_ = 0,
        flagContinue_ = 1,
        flagUp_ = 0,
        flagDown_ = 1,
        flagLeft_ = 0,
        flagRight_ = 0,
        flagHelp_ = 0,
        flagSave_ = 0,
        flagLoad_ = 0;
    }
    else if(command_ == "left") {
        flagArrows_ = 0,
        flagContinue_ = 1,
        flagUp_ = 0,
        flagDown_ = 0,
        flagLeft_ = 1,
        flagRight_ = 0,
        flagHelp_ = 0,
        flagSave_ = 0,
        flagLoad_ = 0;
    }
    else if(command_ == "right") {
        flagArrows_ = 0,
        flagContinue_ = 1,
        flagUp_ = 0,
        flagDown_ = 0,
        flagLeft_ = 0,
        flagRight_ = 1,
        flagHelp_ = 0,
        flagSave_ = 0,
        flagLoad_ = 0;
    }
    else if(command_ == "save") {
        flagArrows_ = 0,
        flagContinue_ = 1,
        flagUp_ = 0,
        flagDown_ = 0,
        flagLeft_ = 0,
        flagRight_ = 0,
        flagHelp_ = 0,
        flagSave_ = 1,
        flagLoad_ = 0;
    }
    else if(command_ == "load") {
        flagArrows_ = 0,
        flagContinue_ = 1,
        flagUp_ = 0,
        flagDown_ = 0,
        flagLeft_ = 0,
        flagRight_ = 0,
        flagHelp_ = 0,
        flagSave_ = 0,
        flagLoad_ = 1;
    }
    // else if(command_ == "quit") {
    //     quit();
    // }
    return command_;
}

bool Command::getFlagArrows() {
    return flagArrows_;
}
bool Command::getFlagContinue() {
    return flagContinue_;
}
bool Command::getFlagUp() {
    return flagUp_;
}
bool Command::getFlagDown() {
    return flagDown_;
}
bool Command::getFlagLeft() {
    return flagLeft_;
}
bool Command::getFlagRight() {
    return flagRight_;
}
bool Command::getFlagHelp() {
    return flagHelp_;
}
bool Command::getFlagSave() {
    return flagSave_;
}
bool Command::getFlagLoad() {
    return flagLoad_;
}

//https://cplusplus.com/doc/tutorial/files/
void Command::save(GameBoard &gameboard, Character &character) {
    string filename;
    cout << "Create a new file name to save." << endl;
    cout << "What do you wish to name the file: ";
    cin >> filename;
    ofstream fileToSave;
    fileToSave.open(filename);
    fileToSave << gameboard.getcoX() << "\n";
    fileToSave << gameboard.getcoY() << "\n";
    fileToSave << gameboard.getnoOfZombies() << "\n";
    fileToSave << character.getAlienAttribute()[0] << "\n";
    fileToSave << character.getAlienAttribute()[1] << "\n";
    fileToSave << character.getAlienAttribute()[2] << "\n";
    fileToSave << character.getAlienAttribute()[3] << "\n";
    fileToSave << character.getAlienAttribute()[4] << "\n";
    for (int i = 0; i < gameboard.getnoOfZombies(); ++i) {
        for (int j = 0; j < 5; ++j) {
            fileToSave << character.getZombieAttribute()[i][j] << "\n";
        }
    }
    for (int i = 0; i < gameboard.getcoY(); ++i) {
        for (int j = 0; j < gameboard.getcoX(); ++j) {
            fileToSave << gameboard.getMapObjects()[i][j] << "\n";
        }
    }
    fileToSave.close();
}

void Command::load(GameBoard &gameboard, Character &character)
{
    string data;
    string filename;
    cout << "What file to load from? " << endl;
    cout << "File name: ";
    cin >> filename;
    ifstream fileToLoad(filename);
    
    vector<int> gameData; //https://www.freecodecamp.org/news/string-to-int-in-c-how-to-convert-a-string-to-an-integer-example
    vector<char> mapObj;
    if (fileToLoad.is_open())
    {
        int i = 0;
        while (i < 8)
        {
            getline(fileToLoad, data);
            int intData = stoi(data);
            gameData.push_back(intData);
            ++i;
        }
        for (i = 0; i < gameData[2] * 5; ++i) 
        {
            getline(fileToLoad, data);
            int intData = stoi(data);
            gameData.push_back(intData);
        }
        int p = 0;
        while (getline(fileToLoad, data))
        {
            
            char obj = data[0];
            mapObj.push_back(obj);
            ++p;
        }
        fileToLoad.close();
    }
    else
    {
        cout << "File not found." << endl;
    }
    //map and object
    gameboard.init(gameData[0], gameData[1], gameData[2], 0);
    //alien
    character.loadAlienAttribute(gameData[3], gameData[4], gameData[5], gameData[6], gameData[7]);
    //zombie
    int j;
    bool load = 1;
    character.setNoOfZombies(gameData[2]);
    character.init(load);
    for (int i = 0; i < gameData[2]; ++i)
    {
        j = i * 5;
        character.loadZombieAttribute(i, gameData[8 + j], gameData[9 + j], gameData[10 + j], gameData[11 + j], gameData[12 + j]);
    }
    char loadObj[gameData[1]][gameData[0]];
    int dataForObj = 0;
    for (int k = 0; k < gameData[1]; ++k)
    {
        for (int l = 0; l < gameData[0]; ++l)
        {
            loadObj[k][l] = mapObj[dataForObj];
            dataForObj = dataForObj + 1;
        }
    }

    cout << "Game loaded." << endl;
    flagLoad_ = 0;
    for (int i = 0; i < gameData[1]; ++i) {
        for (int j = 0; j < gameData[0]; ++j) 
        {
            char ch = loadObj[i][j];
            gameboard.characterOnMap(j + 1, gameData[1] - i, ch);
        }
    }
    pauCle::Pause();
    pauCle::ClearScreen();
}

void Command::help() {
    
    cout << "Commands" << endl;
    cout << "1. help   - Display commands." << endl;
    cout << "2. arrow  - Change the direction of an arrow." << endl;   
    cout << "3. up     - Move up." << endl;
    cout << "4. down   - Move down." << endl;
    cout << "5. left   - Move left." << endl;
    cout << "6. right  - Move right." << endl;
    cout << "7. save   - Save the game." << endl;
    cout << "8. load   - Load the game." << endl;
    cout << "9. quit   - Quit the game." << endl;
    flagHelp_ = 0;
    pauCle::Pause();
    pauCle::ClearScreen();
}

void Command::arrows(GameBoard &gameboard, int x, int y) {
    int coX = gameboard.getcoX();
    int coY = gameboard.getcoY();
    char** mapObj = gameboard.getMapObjects();
    char arrowObj[] = {'^', 'v', '<', '>'};
    int flagArr = 0; 
    for (int i = 0; i < 4; ++i) {
        if (mapObj[coY - y][x - 1] == arrowObj[i]) {
            string direction;
            cout << "Change to what direction(up/down/left/right): ";
            cin >> direction;
            if (direction == "up") {
                cout << "Arrow " << mapObj[coY - y][x - 1] << " at (" << x << ", " << y << ") is changed to ^." << endl;
                pauCle::Pause();
                pauCle::ClearScreen();
                gameboard.characterOnMap(x, y, '^');
            }
            else if (direction == "down") {
                cout << "Arrow " << mapObj[coY - y][x - 1] << " at (" << x << ", " << y << ") is changed to v." << endl;
                pauCle::Pause();
                pauCle::ClearScreen();
                gameboard.characterOnMap(x, y, 'v');
            }
            else if (direction == "left") {
                cout << "Arrow " << mapObj[coY - y][x - 1] << " at (" << x << ", " << y << ") is changed to <." << endl;
                pauCle::Pause();
                pauCle::ClearScreen();
                gameboard.characterOnMap(x, y, '<');
            }
            else if (direction == "right") {
                cout << "Arrow " << mapObj[coY - y][x - 1] << " at (" << x << ", " << y << ") is changed to >." << endl;
                pauCle::Pause();
                pauCle::ClearScreen();
                gameboard.characterOnMap(x, y, '>');
            }
            else {
                cout << "Try again.";
            }
            break;
        }
        else {
            flagArr = flagArr + 1;
            if (flagArr == 4) {
                cout << "Try again." << endl;
                pauCle::Pause();
                pauCle::ClearScreen();
            }
        }
    }
    flagArrows_ = 0;
}

void Command::quit() {
    cout << "Are you sure? (y/n): ";
    char yn;
    cin >> yn;
    if (yn == 'y') {
        flagContinue_ = 0;
        cout << "Goodbye!";
    }
    else if (yn == 'n') {
        input();
    }
    else {
        cout << "Try again!";
        input();
    }
}

void Command:: gameend(GameBoard &gameboard, Character &character)
{
    int *alienAttribute = character.getAlienAttribute() ;
    int **zombieAttribute = character.getZombieAttribute();
    char yn;
    if (alienAttribute[0] == 0)
    {   
        gameboard.display();
        character.display();
        cout << "Zombies Win !" ;
        flagContinue_ = 0;
        cout << "Do you want to try again? (y/n): ";
        cin >> yn;
        if (yn == 'y') {
            gameboard.gameStart();
        }
        else {
            cout << "GoodBye!";
        }
    }
    else
    {
        int total ;
        for (int i = 0; i < character.getNoOfZombie(); ++i) 
        {
            total += zombieAttribute[i][0];
        }
        if (total == 0)
        {
            cout << "YOU WIN!!";
            flagContinue_ = 0;
            cout << "Do you want to try again? (y/n): ";
            cin >> yn;
            if (yn == 'y') {
                gameboard.gameStart();
            }
            else {
                cout << "GoodBye!";
            }
        }
    }
}


void Command::up(GameBoard &gameboard, Character &character, char** obj)
{
    bool flagEnd = 0;
    int *alienAttribute = character.getAlienAttribute() ;
    int **zombieAttribute = character.getZombieAttribute();
    int oriX = alienAttribute[3] - 1;
    int oriY = gameboard.getcoY() - alienAttribute[4];
    char zombie[character.getNoOfZombie()];
    for (int i = 0; i < character.getNoOfZombie(); ++i) {
        zombie[i] = '1' + i;
    }
    for (int i =oriY ; i > 0 ; --i)
    {
        int x=i-1;
        char **getmapobject = gameboard.getMapObjects();
        if (alienAttribute[4] == gameboard.getcoY()) {
                cout << "Alien hits the border. Ending Alien's turn." << endl;
                pauCle::Pause();
                pauCle::ClearScreen();
                zombiemovement(gameboard, character);
                break;
        }

        if (getmapobject[x][oriX] == ' ')
        {   
            cout << "Alien found an empty space." << endl;
            pauCle::Pause();
            pauCle::ClearScreen();
            gameboard.display();
            character.display();
        }
        else if (getmapobject[x][oriX] == 'r') {
            cout << "Alien hits a rock. Ending Alien's turn." << endl;
            char objects[] = {' ', ' ', ' ', '^', 'v', '<', '>', 'h', 'p'};
            int noOfObjects = 9;
            int randNum = rand() % noOfObjects;
            getmapobject[x][oriX] = objects[randNum];
            gameboard.characterOnMap(alienAttribute[3] , alienAttribute[4] + 1, getmapobject[x][oriX]);
            if (getmapobject[x][oriX] == ' ') {
                cout << "Discovers nothing." << endl;
            }
            else if (getmapobject[x][oriX] == '^' || getmapobject[x][oriX] == 'v' || getmapobject[x][oriX] == '<' || getmapobject[x][oriX] == '>') {
                cout << "Discovers an arrow." << endl;
            }
            else if (getmapobject[x][oriX] == 'h') {
                cout << "Discovers a health pack." << endl;
            }
            else if (getmapobject[x][oriX] == 'p') {
                cout << "Discovers a pod." << endl;
            }
            pauCle::Pause();
            pauCle::ClearScreen();
            zombiemovement(gameboard, character);
            break;
        }
        
        else if (getmapobject[x][oriX] == 'h')
        {
            cout << "Alien obtained a health pack." << endl;
            if (alienAttribute[0] >= 100)
            {
                cout << "Health is already full." << endl;
                pauCle::Pause();
                pauCle::ClearScreen();
            }
            else
            {   
                cout << "Restoring 10 health." << endl;                
                character.setAlienHealth(alienAttribute[0] +10);
                pauCle::Pause();
                pauCle::ClearScreen();
            }
        }

        else if (getmapobject[x][oriX] == 'p')
        {
            cout << "Alien found a pod." << endl;
            int rangeZombie[character.getNoOfZombie()];
            int closestZombie;
            for (int i = 0; i < character.getNoOfZombie(); ++i) {
                int xDif = oriX - zombieAttribute[i][3];
                int yDif = oriY - zombieAttribute[i][4];
                rangeZombie[i] = sqrt((xDif * xDif) + (yDif * yDif));
                closestZombie = *min_element(rangeZombie, rangeZombie + character.getNoOfZombie());
            }
            for (int i = 0; i < character.getNoOfZombie(); ++i) {
                if (rangeZombie[i] == closestZombie) {
                    closestZombie = i;
                    break;
                }
                break;
            }
            cout << "Zombie " << closestZombie+1 << " lost 10 health!" << endl;
            pauCle::Pause();
            pauCle::ClearScreen();
            int newhealth = zombieAttribute[closestZombie][0]-10;
            character.setZombieHealth(closestZombie, newhealth);
        }

        else if (getmapobject[x][oriX] == '^')
        {
            cout << "Alien found an ^ arrow." << endl;
            cout << "Alien's attack + 10!" << endl;
            int newDamage = character.getAlienAttribute()[1] + 10;
            character.setAlienAttack(newDamage);
            pauCle::Pause();
            pauCle::ClearScreen();
            if (alienAttribute[4] + 1 == gameboard.getcoY()) {
                gameboard.characterOnMap(alienAttribute[3],alienAttribute[4],'#');
                character.setAlienLocation(alienAttribute[3],alienAttribute[4]+1);
                int *alienAttribute = character.getAlienAttribute() ;
                gameboard.characterOnMap(alienAttribute[3],alienAttribute[4], 'A');
                gameboard.display();
                character.display();
                cout << "Alien hits the border. Ending Alien's turn." << endl;
                pauCle::Pause();
                pauCle::ClearScreen();
                zombiemovement(gameboard, character);
                zombiemovement(gameboard, character);
                break;
            }
            else
            {
                for (int i = 0; i < character.getNoOfZombie(); ++i) {
                    if (getmapobject[x][oriX] == zombie[i]) {
                        if (zombieAttribute[i][0] >= alienAttribute[1]) {
                            character.setZombieHealth(i, zombieAttribute[i][0] - alienAttribute[1]);
                            cout << endl << "Alien hits a zombie." << endl;
                            cout << "Zombie " << zombie[i] << " loses " << alienAttribute[1] << " health." << endl;
                            cout << "Ending Alien's turn." << endl;
                            flagEnd = 1;
                            pauCle::Pause();
                            pauCle::ClearScreen();
                            zombiemovement(gameboard, character);
                            break;
                        }
                    }
                }
                if (flagEnd == 1) {
                    flagEnd = 0;
                    break;
                }
            }
            gameboard.characterOnMap(alienAttribute[3],alienAttribute[4],'#');
            character.setAlienLocation(alienAttribute[3],alienAttribute[4]+1);
            int *alienAttribute = character.getAlienAttribute() ;
            gameboard.characterOnMap(alienAttribute[3],alienAttribute[4], 'A');
            gameboard.display();
            character.display();
            pauCle::Pause();
            pauCle::ClearScreen();

            gameboard.display();
            character.display();
            up(gameboard, character, obj);
            break;
        }

        else if (getmapobject[x][oriX] == 'v')
        {
            cout << "Alien found an v arrow." << endl;
            cout << "Alien's attack + 10!" << endl;
            int newDamage = character.getAlienAttribute()[1] + 10;
            character.setAlienAttack(newDamage);
            pauCle::Pause();
            pauCle::ClearScreen();
            if (alienAttribute[4] - 1 == 1) {
                cout << "Alien hits the border. Ending Alien's turn." << endl;
                pauCle::Pause();
                pauCle::ClearScreen();
                zombiemovement(gameboard, character);
                break;
            }
            else
            {
                for (int i = 0; i < character.getNoOfZombie(); ++i) {
                    if (getmapobject[x][oriX] == zombie[i]) {
                        if (zombieAttribute[i][0] >= alienAttribute[1]) {
                            character.setZombieHealth(i, zombieAttribute[i][0] - alienAttribute[1]);
                            cout << endl << "Alien hits a zombie." << endl;
                            cout << "Zombie " << zombie[i] << " loses " << alienAttribute[1] << " health." << endl;
                            cout << "Ending Alien's turn." << endl;
                            flagEnd = 1;
                            pauCle::Pause();
                            pauCle::ClearScreen();
                            zombiemovement(gameboard, character);
                            break;
                        }
                    }
                }
                if (flagEnd == 1) {
                    flagEnd = 0;
                    break;
                }
            }
            gameboard.characterOnMap(alienAttribute[3],alienAttribute[4],'#');
            character.setAlienLocation(alienAttribute[3],alienAttribute[4]+1);
            int *alienAttribute = character.getAlienAttribute() ;
            gameboard.characterOnMap(alienAttribute[3],alienAttribute[4], 'A');
            gameboard.display();
            character.display();
            cout << endl << "Changing direction. Going Down!" << endl;
            pauCle::Pause();
            pauCle::ClearScreen();

            gameboard.display();
            character.display();
            down(gameboard,character,obj);
            break;
        }

        else if (getmapobject[x][oriX] == '<')
        {
            cout << "Alien found an < arrow." << endl;
            cout << "Alien's attack + 10!" << endl;
            int newDamage = character.getAlienAttribute()[1] + 10;
            character.setAlienAttack(newDamage);
            pauCle::Pause();
            pauCle::ClearScreen();
            if (alienAttribute[3] == 1) {
                cout << "Alien hits the border. Ending Alien's turn." << endl;
                pauCle::Pause();
                pauCle::ClearScreen();
                zombiemovement(gameboard, character);
                break;
            }
            else
            {   
                for (int i = 0; i < character.getNoOfZombie(); ++i) {
                    if (getmapobject[x][oriX] == zombie[i]) {
                        if (zombieAttribute[i][0] >= alienAttribute[1]) {
                            character.setZombieHealth(i, zombieAttribute[i][0] - alienAttribute[1]);
                            cout << endl << "Alien hits a zombie." << endl;
                            cout << "Zombie " << zombie[i] << " loses " << alienAttribute[1] << " health." << endl;
                            cout << "Ending Alien's turn." << endl;
                            flagEnd = 1;
                            pauCle::Pause();
                            pauCle::ClearScreen();
                            zombiemovement(gameboard, character);
                            break;
                        }
                    }
                }
                if (flagEnd == 1) {
                    flagEnd = 0;
                    break;
                }
            }
            gameboard.characterOnMap(alienAttribute[3],alienAttribute[4],'#');
            character.setAlienLocation(alienAttribute[3],alienAttribute[4]+1);
            int *alienAttribute = character.getAlienAttribute() ;
            gameboard.characterOnMap(alienAttribute[3],alienAttribute[4], 'A');
            gameboard.display();
            character.display();
            cout << endl << "Changing direction. Going Left!" << endl;
            pauCle::Pause();
            pauCle::ClearScreen();

            gameboard.display();
            character.display();
            left(gameboard,character,obj);
            break;
        }
        
        else if (getmapobject[x][oriX] == '>')
        {
            cout << "Alien found an > arrow." << endl;
            cout << "Alien's attack + 10!" << endl;
            int newDamage = character.getAlienAttribute()[1] + 10;
            character.setAlienAttack(newDamage);
            pauCle::Pause();
            pauCle::ClearScreen();
            if (alienAttribute[3] == gameboard.getcoX()) {
                cout << "Alien hits the border. Ending Alien's turn." << endl;
                pauCle::Pause();
                pauCle::ClearScreen();
                zombiemovement(gameboard, character);
                break;
            }
            else
            {
                for (int i = 0; i < character.getNoOfZombie(); ++i) {
                    if (getmapobject[x][oriX] == zombie[i]) {
                        if (zombieAttribute[i][0] >= alienAttribute[1]) {
                            character.setZombieHealth(i, zombieAttribute[i][0] - alienAttribute[1]);
                            cout << endl << "Alien hits a zombie." << endl;
                            cout << "Zombie " << zombie[i] << " loses " << alienAttribute[1] << " health." << endl;
                            cout << "Ending Alien's turn." << endl;
                            flagEnd = 1;
                            pauCle::Pause();
                            pauCle::ClearScreen();
                            zombiemovement(gameboard, character);
                            break;
                        }
                    }
                }
                if (flagEnd == 1) {
                    flagEnd = 0;
                    break;
                }
            }
            gameboard.characterOnMap(alienAttribute[3],alienAttribute[4],'#');
            character.setAlienLocation(alienAttribute[3],alienAttribute[4]+1);
            int *alienAttribute = character.getAlienAttribute() ;
            gameboard.characterOnMap(alienAttribute[3],alienAttribute[4], 'A');
            gameboard.display();
            character.display();
            cout << endl << "Changing direction. Going Right!" << endl;
            pauCle::Pause();
            pauCle::ClearScreen();

            gameboard.display();
            character.display();
            right(gameboard,character,obj);
            break;
        }
        else
        {
            for (int i = 0; i < character.getNoOfZombie(); ++i) {
                if (getmapobject[x][oriX] == zombie[i]) {
                    if (zombieAttribute[i][0] >= alienAttribute[1]) {
                        character.setZombieHealth(i, zombieAttribute[i][0] - alienAttribute[1]);
                        cout << endl << "Alien hits a zombie." << endl;
                        cout << "Zombie " << zombie[i] << " loses " << alienAttribute[1] << " health." << endl;
                        cout << "Ending Alien's turn." << endl;
                        flagEnd = 1;
                        pauCle::Pause();
                        pauCle::ClearScreen();
                        zombiemovement(gameboard, character);
                        break;
                    }
                }
            }
            if (flagEnd == 1) {
                flagEnd = 0;
                break;
            }
        }
        gameboard.characterOnMap(alienAttribute[3], alienAttribute[4],'#');
        character.setAlienLocation(alienAttribute[3],alienAttribute[4] + 1);
        int *alienAttribute = character.getAlienAttribute() ;
        gameboard.characterOnMap(alienAttribute[3], alienAttribute[4], 'A');
        pauCle::Pause();
        pauCle::ClearScreen();
        gameboard.display();
        character.display();
        if (alienAttribute[4] == gameboard.getcoY()) {
            cout << "Alien hits the border. Ending Alien's turn." << endl;
            pauCle::Pause();
            pauCle::ClearScreen();
            zombiemovement(gameboard, character);
        }
    }
}

void Command :: down(GameBoard &gameboard, Character &character, char** obj)
{
    bool flagEnd = 0;
    int *alienAttribute = character.getAlienAttribute() ;
    int **zombieAttribute = character.getZombieAttribute();
    int oriX = alienAttribute[3] - 1;
    int oriY = gameboard.getcoY() - alienAttribute[4];
    char zombie[character.getNoOfZombie()];
    for (int i = 0; i < character.getNoOfZombie(); ++i) {
        zombie[i] = '1' + i;
    }
    for (int i = oriY ; i <gameboard.getcoY()-1 ; ++i)
    {
        int x=i+1;
        char **getmapobject = gameboard.getMapObjects();
        if (alienAttribute[4] == 1) {
                cout << "Alien hits the border. Ending Alien's turn." << endl;
                pauCle::Pause();
                pauCle::ClearScreen();
                zombiemovement(gameboard, character);
                break;
        }

        if (getmapobject[x][oriX] == ' ')
        {
            cout << "Alien found an empty space." << endl;
            pauCle::Pause();
            pauCle::ClearScreen();
        }

        else if (getmapobject[x][oriX] == 'r') {
            cout << "Alien hits a rock. Ending Alien's turn." << endl;
            char objects[] = {' ', ' ', ' ', '^', 'v', '<', '>', 'h', 'p'};
            int noOfObjects = 9;
            int randNum = rand() % noOfObjects;
            getmapobject[x][oriX] = objects[randNum];
            gameboard.characterOnMap(alienAttribute[3], alienAttribute[4] - 1, getmapobject[x][oriX]);
            if (getmapobject[x][oriX] == ' ') {
                cout << "Discovers nothing." << endl;
            }
            else if (getmapobject[x][oriX] == '^' || getmapobject[x][oriX] == 'v' || getmapobject[x][oriX] == '<' || getmapobject[x][oriX] == '>') {
                cout << "Discovers an arrow." << endl;
            }
            else if (getmapobject[x][oriX] == 'h') {
                cout << "Discovers a health pack." << endl;
            }
            else if (getmapobject[x][oriX] == 'p') {
                cout << "Discovers a pod." << endl;
            }
            pauCle::Pause();
            pauCle::ClearScreen();
            zombiemovement(gameboard, character);
            break;
        }
        
        else if (getmapobject[x][oriX] == 'h')
        {
            cout << "Alien obtained a health pack." << endl;
            if (alienAttribute[0] >= 100)
            {
                cout << "Health is already full." << endl;
                pauCle::Pause();
                pauCle::ClearScreen();
            }
            else
            {   
                cout << "Restoring 10 health." << endl;                
                character.setAlienHealth(alienAttribute[0] +10);
                pauCle::Pause();
                pauCle::ClearScreen();
            }
        }
        else if (getmapobject[x][oriX] == 'p')
        {
            cout << "Alien found a pod." << endl;
            int rangeZombie[character.getNoOfZombie()];
            int closestZombie;
            for (int i = 0; i < character.getNoOfZombie(); ++i) {
                int xDif = oriX - zombieAttribute[i][3];
                int yDif = oriY - zombieAttribute[i][4];
                rangeZombie[i] = sqrt((xDif * xDif) + (yDif * yDif));
                closestZombie = *min_element(rangeZombie, rangeZombie + character.getNoOfZombie());
            }
            for (int i = 0; i < character.getNoOfZombie(); ++i) {
                if (rangeZombie[i] == closestZombie) {
                    closestZombie = i;
                    break;
                }
            }
            cout << "Zombie " << closestZombie+1 << " lost 10 health!" << endl;
            pauCle::Pause();
            pauCle::ClearScreen();
            int newhealth = zombieAttribute[closestZombie][0]-10;
            character.setZombieHealth(closestZombie, newhealth);
        }
        else if (getmapobject[x][oriX] == '^')
        {
            cout << "Alien found an ^ arrow." << endl;
            cout << "Alien's attack + 10!" << endl;
            int newDamage = character.getAlienAttribute()[1] + 10;
            character.setAlienAttack(newDamage);
            pauCle::Pause();
            pauCle::ClearScreen();
            gameboard.characterOnMap(alienAttribute[3],alienAttribute[4],'#');
            character.setAlienLocation(alienAttribute[3],alienAttribute[4]-1);
            int *alienAttribute = character.getAlienAttribute() ;
            gameboard.characterOnMap(alienAttribute[3],alienAttribute[4], 'A');
            gameboard.display();
            character.display();
            if (alienAttribute[4] == gameboard.getcoY()) {
                cout << "Alien hits the border. Ending Alien's turn." << endl;
                pauCle::Pause();
                pauCle::ClearScreen();
                zombiemovement(gameboard, character);
                break;
            }
            else
            {
                for (int i = 0; i < character.getNoOfZombie(); ++i) {
                    if (getmapobject[x][oriX] == zombie[i]) {
                        if (zombieAttribute[i][0] >= alienAttribute[1]) {
                            character.setZombieHealth(i, zombieAttribute[i][0] - alienAttribute[1]);
                            cout << endl << "Alien hits a zombie." << endl;
                            cout << "Zombie " << zombie[i] << " loses " << alienAttribute[1] << " health." << endl;
                            cout << "Ending Alien's turn." << endl;
                            flagEnd = 1;
                            pauCle::Pause();
                            pauCle::ClearScreen();
                            zombiemovement(gameboard, character);
                            break;
                        }
                    }
                }
                if (flagEnd == 1) {
                    flagEnd = 0;
                    break;
                }
            }
            cout << endl << "Changing direction. Going Up!" << endl;
            pauCle::Pause();
            pauCle::ClearScreen();

            gameboard.display();
            character.display();
            up(gameboard, character, obj);
            break;
        }
        else if (getmapobject[x][oriX] == 'v')
        {
            cout << "Alien found an v arrow." << endl;
            cout << "Alien's attack + 10!" << endl;
            int newDamage = character.getAlienAttribute()[1] + 10;
            character.setAlienAttack(newDamage);
            pauCle::Pause();
            pauCle::ClearScreen();
            gameboard.characterOnMap(alienAttribute[3],alienAttribute[4],'#');
            character.setAlienLocation(alienAttribute[3],alienAttribute[4]-1);
            int *alienAttribute = character.getAlienAttribute() ;
            gameboard.characterOnMap(alienAttribute[3],alienAttribute[4], 'A');
            gameboard.display();
            character.display();
            if (alienAttribute[4] == 1) {
                cout << "Alien hits the border. Ending Alien's turn." << endl;
                pauCle::Pause();
                pauCle::ClearScreen();
                zombiemovement(gameboard, character);
                break;
            }
            else
            {
                for (int i = 0; i < character.getNoOfZombie(); ++i) {
                    if (getmapobject[x][oriX] == zombie[i]) {
                        if (zombieAttribute[i][0] >= alienAttribute[1]) {
                            character.setZombieHealth(i, zombieAttribute[i][0] - alienAttribute[1]);
                            cout << endl << "Alien hits a zombie." << endl;
                            cout << "Zombie " << zombie[i] << " loses " << alienAttribute[1] << " health." << endl;
                            cout << "Ending Alien's turn." << endl;
                            flagEnd = 1;
                            pauCle::Pause();
                            pauCle::ClearScreen();
                            zombiemovement(gameboard, character);
                            break;
                        }
                    }
                }
                if (flagEnd == 1) {
                    flagEnd = 0;
                    break;
                }
            }
            pauCle::Pause();
            pauCle::ClearScreen();

            gameboard.display();
            character.display();
            down(gameboard,character,obj);
            break;
        }

        else if (getmapobject[x][oriX] == '<')
        {
            cout << "Alien found an < arrow." << endl;
            cout << "Alien's attack + 10!" << endl;
            int newDamage = character.getAlienAttribute()[1] + 10;
            character.setAlienAttack(newDamage);
            pauCle::Pause();
            pauCle::ClearScreen();
            gameboard.characterOnMap(alienAttribute[3],alienAttribute[4],'#');
            character.setAlienLocation(alienAttribute[3],alienAttribute[4]-1);
            int *alienAttribute = character.getAlienAttribute() ;
            gameboard.characterOnMap(alienAttribute[3],alienAttribute[4], 'A');
            gameboard.display();
            character.display();
            if (alienAttribute[3] == 1) {
                cout << "Alien hits the border. Ending Alien's turn." << endl;
                pauCle::Pause();
                pauCle::ClearScreen();
                zombiemovement(gameboard, character);
                break;
            }
            else
            {
                for (int i = 0; i < character.getNoOfZombie(); ++i) {
                    if (getmapobject[x][oriX] == zombie[i]) {
                        if (zombieAttribute[i][0] >= alienAttribute[1]) {
                            character.setZombieHealth(i, zombieAttribute[i][0] - alienAttribute[1]);
                            cout << endl << "Alien hits a zombie." << endl;
                            cout << "Zombie " << zombie[i] << " loses " << alienAttribute[1] << " health." << endl;
                            cout << "Ending Alien's turn." << endl;
                            flagEnd = 1;
                            pauCle::Pause();
                            pauCle::ClearScreen();
                            zombiemovement(gameboard, character);
                            break;
                        }
                    }
                }
                if (flagEnd == 1) {
                    flagEnd = 0;
                    break;
                }
            }
            cout << endl << "Changing direction. Going Left!" << endl;
            pauCle::Pause();
            pauCle::ClearScreen();

            gameboard.display();
            character.display();
            left(gameboard,character,obj);
            break;
        }
        
        else if (getmapobject[x][oriX] == '>')
        {
            cout << "Alien found an > arrow." << endl;
            cout << "Alien's attack + 10!" << endl;
            int newDamage = character.getAlienAttribute()[1] + 10;
            character.setAlienAttack(newDamage);
            pauCle::Pause();
            pauCle::ClearScreen();
            gameboard.characterOnMap(alienAttribute[3],alienAttribute[4],'#');
            character.setAlienLocation(alienAttribute[3],alienAttribute[4]-1);
            int *alienAttribute = character.getAlienAttribute() ;
            gameboard.characterOnMap(alienAttribute[3],alienAttribute[4], 'A');
            gameboard.display();
            character.display();
            if (alienAttribute[3] == gameboard.getcoX()) {
                cout << "Alien hits the border. Ending Alien's turn." << endl;
                pauCle::Pause();
                pauCle::ClearScreen();
                zombiemovement(gameboard, character);
                break;
            }
            else
            {
                for (int i = 0; i < character.getNoOfZombie(); ++i) {
                    if (getmapobject[x][oriX] == zombie[i]) {
                        if (zombieAttribute[i][0] >= alienAttribute[1]) {
                            character.setZombieHealth(i, zombieAttribute[i][0] - alienAttribute[1]);
                            cout << endl << "Alien hits a zombie." << endl;
                            cout << "Zombie " << zombie[i] << " loses " << alienAttribute[1] << " health." << endl;
                            cout << "Ending Alien's turn." << endl;
                            flagEnd = 1;
                            pauCle::Pause();
                            pauCle::ClearScreen();
                            zombiemovement(gameboard, character);
                            break;
                        }
                    }
                }
                if (flagEnd == 1) {
                    flagEnd = 0;
                    break;
                }
            }
            cout << endl << "Changing direction. Going Right!" << endl;
            pauCle::Pause();
            pauCle::ClearScreen();

            gameboard.display();
            character.display();
            right(gameboard,character,obj);
            break;
        }
        else
        {
            for (int i = 0; i < character.getNoOfZombie(); ++i) {
                if (getmapobject[x][oriX] == zombie[i]) {
                    if (zombieAttribute[i][0] >= alienAttribute[1]) {
                        character.setZombieHealth(i, zombieAttribute[i][0] - alienAttribute[1]);
                        cout << endl << "Alien hits a zombie." << endl;
                        cout << "Zombie " << zombie[i] << " loses " << alienAttribute[1] << " health." << endl;
                        cout << "Ending Alien's turn." << endl;
                        flagEnd = 1;
                        pauCle::Pause();
                        pauCle::ClearScreen();
                        zombiemovement(gameboard, character);
                        break;
                    }
                }
            }
            if (flagEnd == 1) {
                flagEnd = 0;
                break;
            }
        }
        gameboard.characterOnMap(alienAttribute[3],alienAttribute[4],'#');
        character.setAlienLocation(alienAttribute[3],alienAttribute[4]-1);
        int *alienAttribute = character.getAlienAttribute() ;
        gameboard.characterOnMap(alienAttribute[3],alienAttribute[4], 'A');
        gameboard.display();
        character.display();
        if (alienAttribute[4] == 1) {
            cout << "Alien hits the border. Ending Alien's turn." << endl;
            pauCle::Pause();
            pauCle::ClearScreen();
            zombiemovement(gameboard, character);
        }
    }
}

void Command :: left(GameBoard &gameboard, Character &character, char** obj)
{
    bool flagEnd = 0;
    int *alienAttribute = character.getAlienAttribute() ;
    int **zombieAttribute = character.getZombieAttribute();
    int oriX = alienAttribute[3] - 1;
    int oriY = gameboard.getcoY() - alienAttribute[4];
    char zombie[character.getNoOfZombie()];
    for (int i = 0; i < character.getNoOfZombie(); ++i) {
        zombie[i] = '1' + i;
    }
    for (int i = oriX ; i > 0 ; --i)
    {   
        int x=i-1;
        char **getmapobject = gameboard.getMapObjects();
        if (alienAttribute[3] == 1) {
                cout << endl << "Alien hits the border. Ending Alien's turn." << endl;
                pauCle::Pause();
                pauCle::ClearScreen();
                zombiemovement(gameboard, character);
                break;
        }

        if (getmapobject[oriY][x] == ' ')
        {
            cout << "Alien found an empty space." << endl;
            pauCle::Pause();
            pauCle::ClearScreen();
        }

        else if (getmapobject[oriY][x] == 'r') {
            cout << "Alien hits a rock. Ending Alien's turn." << endl;
            char objects[] = {' ', ' ', ' ', '^', 'v', '<', '>', 'h', 'p'};
            int noOfObjects = 9;
            int randNum = rand() % noOfObjects;
            getmapobject[oriY][x] = objects[randNum];
            gameboard.characterOnMap(alienAttribute[3] - 1, alienAttribute[4], getmapobject[oriY][x]);
            if (getmapobject[oriY][x] == ' ') {
                cout << "Discovers nothing." << endl;
            }
            else if (getmapobject[oriY][x] == '^' || getmapobject[oriY][x] == 'v' || getmapobject[oriY][x] == '<' || getmapobject[oriY][x] == '>') {
                cout << "Discovers an arrow." << endl;
            }
            else if (getmapobject[oriY][x] == 'h') {
                cout << "Discovers a health pack." << endl;
            }
            else if (getmapobject[oriY][x] == 'p') {
                cout << "Discovers a pod." << endl;
            }
            pauCle::Pause();
            pauCle::ClearScreen();
            zombiemovement(gameboard, character);
            break;
        }

        else if (getmapobject[oriY][x] == 'h')
        {
            cout << "Alien obtained a health pack." << endl;
            if (alienAttribute[0] >= 100)
            {
                cout << "Health is already full." << endl;
                pauCle::Pause();
                pauCle::ClearScreen();
            }
            else
            {   
                cout << "Restoring 10 health." << endl;                
                character.setAlienHealth(alienAttribute[0] +10);
                pauCle::Pause();
                pauCle::ClearScreen();
            }
        }
        else if (getmapobject[oriY][x] == 'p')
        { 
            cout << "Alien found a pod." << endl;
            int rangeZombie[character.getNoOfZombie()];
            int closestZombie;
            for (int i = 0; i < character.getNoOfZombie(); ++i) {
                int xDif = oriX - zombieAttribute[i][3];
                int yDif = oriY - zombieAttribute[i][4];
                rangeZombie[i] = sqrt((xDif * xDif) + (yDif * yDif));
                closestZombie = *min_element(rangeZombie, rangeZombie + character.getNoOfZombie());
            }
            for (int i = 0; i < character.getNoOfZombie(); ++i) {
                if (rangeZombie[i] == closestZombie) {
                    closestZombie = i;
                    break;
                }
            }
            cout << "Zombie " << closestZombie+1 << " lost 10 health!" << endl;
            pauCle::Pause();
            pauCle::ClearScreen();
            int newhealth = zombieAttribute[closestZombie][0]-10;
            character.setZombieHealth(closestZombie, newhealth);
        }

        else if (getmapobject[oriY][x] == '^')
        {
            cout << "Alien found an ^ arrow." << endl;
            cout << "Alien's attack + 10!" << endl;
            int newDamage = character.getAlienAttribute()[1] + 10;
            character.setAlienAttack(newDamage);
            pauCle::Pause();
            pauCle::ClearScreen();
            gameboard.characterOnMap(alienAttribute[3],alienAttribute[4],'#');
            character.setAlienLocation(alienAttribute[3]-1,alienAttribute[4]);
            int *alienAttribute = character.getAlienAttribute() ;
            gameboard.characterOnMap(alienAttribute[3],alienAttribute[4], 'A');
            gameboard.display();
            character.display();
            if (alienAttribute[4] == gameboard.getcoY()) {
                cout << "Alien hits the border. Ending Alien's turn." << endl;
                pauCle::Pause();
                pauCle::ClearScreen();
                zombiemovement(gameboard, character);
                break;
            }
            else
            {
                for (int i = 0; i < character.getNoOfZombie(); ++i) {
                    if (getmapobject[oriY-1][x] == zombie[i]) {
                        if (zombieAttribute[i][0] >= alienAttribute[1]) {
                            character.setZombieHealth(i, zombieAttribute[i][0] - alienAttribute[1]);
                            cout << endl << "Alien hits a zombie." << endl;
                            cout << "Zombie " << zombie[i] << " loses " << alienAttribute[1] << " health." << endl;
                            cout << "Ending Alien's turn." << endl;
                            flagEnd = 1;
                            pauCle::Pause();
                            pauCle::ClearScreen();
                            zombiemovement(gameboard, character);
                            break;
                        }
                    }
                }
                if (flagEnd == 1) {
                    flagEnd = 0;
                    break;
            }
            }
            cout << endl << "Changing direction. Going Up!" << endl;
            pauCle::Pause();
            pauCle::ClearScreen();

            gameboard.display();
            character.display();
            up(gameboard, character, obj);
            break;
        }

        else if (getmapobject[oriY][x] == 'v')
        {
            cout << "Alien found an v arrow." << endl;
            cout << "Alien's attack + 10!" << endl;
            int newDamage = character.getAlienAttribute()[1] + 10;
            character.setAlienAttack(newDamage);
            pauCle::Pause();
            pauCle::ClearScreen();
            gameboard.characterOnMap(alienAttribute[3],alienAttribute[4],'#');
            character.setAlienLocation(alienAttribute[3]-1,alienAttribute[4]);
            int *alienAttribute = character.getAlienAttribute() ;
            gameboard.characterOnMap(alienAttribute[3],alienAttribute[4], 'A');
            gameboard.display();
            character.display();
            if (alienAttribute[4] == 1) {
                cout << "Alien hits the border. Ending Alien's turn." << endl;
                pauCle::Pause();
                pauCle::ClearScreen();
                zombiemovement(gameboard, character);
                break;
            }
            else
            {
                for (int i = 0; i < character.getNoOfZombie(); ++i) {
                    if (getmapobject[oriY][x] == zombie[i]) {
                        if (zombieAttribute[i][0] >= alienAttribute[1]) {
                            character.setZombieHealth(i, zombieAttribute[i][0] - alienAttribute[1]);
                            cout << endl << "Alien hits a zombie." << endl;
                            cout << "Zombie " << zombie[i] << " loses " << alienAttribute[1] << " health." << endl;
                            cout << "Ending Alien's turn." << endl;
                            flagEnd = 1;
                            pauCle::Pause();
                            pauCle::ClearScreen();
                            zombiemovement(gameboard, character);
                            break;
                        }
                    }
                }
                if (flagEnd == 1) {
                    flagEnd = 0;
                    break;
                }
            }
            cout << endl << "Changing direction. Going Down!" << endl;
            pauCle::Pause();
            pauCle::ClearScreen();

            gameboard.display();
            character.display();
            down(gameboard,character,obj);
            break;
        }

        else if (getmapobject[oriY][x] == '<')
        {
            cout << "Alien found an < arrow." << endl;
            cout << "Alien's attack + 10!" << endl;
            int newDamage = character.getAlienAttribute()[1] + 10;
            character.setAlienAttack(newDamage);
            pauCle::Pause();
            pauCle::ClearScreen();
            gameboard.characterOnMap(alienAttribute[3],alienAttribute[4],'#');
            character.setAlienLocation(alienAttribute[3]-1,alienAttribute[4]);
            int *alienAttribute = character.getAlienAttribute() ;
            gameboard.characterOnMap(alienAttribute[3],alienAttribute[4], 'A');
            gameboard.display();
            character.display();
            if (alienAttribute[3] == 1) {
                cout << endl << "Alien hits the border. Ending Alien's turn." << endl;
                pauCle::Pause();
                pauCle::ClearScreen();
                zombiemovement(gameboard, character);
                break;
            }
            else
            {
                for (int i = 0; i < character.getNoOfZombie(); ++i) {
                    if (getmapobject[oriY][x-1] == zombie[i]) {
                        if (zombieAttribute[i][0] >= alienAttribute[1]) {
                            character.setZombieHealth(i, zombieAttribute[i][0] - alienAttribute[1]);
                            cout << endl << "Alien hits a zombie." << endl;
                            cout << "Ending Alien's turn." << endl;
                            flagEnd = 1;
                            pauCle::Pause();
                            pauCle::ClearScreen();
                            zombiemovement(gameboard, character);
                            break;
                        }
                    }
                }
                if (flagEnd == 1) {
                    flagEnd = 0;
                    break;
                }
            }
            pauCle::Pause();
            pauCle::ClearScreen();
            
            gameboard.display();
            character.display();
            left(gameboard,character,obj);
            break;
        }
        
        else if (getmapobject[oriY][x] == '>')
        {
            cout << "Alien found an > arrow." << endl;
            cout << "Alien's attack + 10!" << endl;
            int newDamage = character.getAlienAttribute()[1] + 10;
            character.setAlienAttack(newDamage);
            pauCle::Pause();
            pauCle::ClearScreen();
            gameboard.characterOnMap(alienAttribute[3],alienAttribute[4],'#');
            character.setAlienLocation(alienAttribute[3]-1,alienAttribute[4]);
            int *alienAttribute = character.getAlienAttribute() ;
            gameboard.characterOnMap(alienAttribute[3],alienAttribute[4], 'A');
            gameboard.display();
            character.display();
            if (alienAttribute[3] == gameboard.getcoX()) {
                cout << "Alien hits the border. Ending Alien's turn." << endl;
                pauCle::Pause();
                pauCle::ClearScreen();
                zombiemovement(gameboard, character);
                break;
            }
            else
            {
                for (int i = 0; i < character.getNoOfZombie(); ++i) {
                    if (getmapobject[oriY][x+1] == zombie[i]) {
                        if (zombieAttribute[i][0] >= alienAttribute[1]) {
                            character.setZombieHealth(i, zombieAttribute[i][0] - alienAttribute[1]);
                            cout << endl << "Alien hits a zombie." << endl;
                            cout << "Zombie " << zombie[i] << " loses " << alienAttribute[1] << " health." << endl;
                            cout << "Ending Alien's turn." << endl;
                            flagEnd = 1;
                            pauCle::Pause();
                            pauCle::ClearScreen();
                            zombiemovement(gameboard, character);
                            break;
                        }
                    }
                }
                if (flagEnd == 1) {
                    flagEnd = 0;
                    break;
                }
            }
            cout << endl << "Changing direction. Going Right!" << endl;
            pauCle::Pause();
            pauCle::ClearScreen();

            gameboard.display();
            character.display();
            right(gameboard,character,obj);
            break;
        }
        else
        {
            for (int i = 0; i < character.getNoOfZombie(); ++i) {
                if (getmapobject[oriY][x] == zombie[i]) {
                    if (zombieAttribute[i][0] >= alienAttribute[1]) {
                        character.setZombieHealth(i, zombieAttribute[i][0] - alienAttribute[1]);
                        cout << endl << "Alien hits a zombie." << endl;
                        cout << "Zombie " << zombie[i] << " loses " << alienAttribute[1] << " health." << endl;
                        cout << "Ending Alien's turn." << endl;
                        flagEnd = 1;
                        pauCle::Pause();
                        pauCle::ClearScreen();
                        zombiemovement(gameboard, character);
                        break;
                    }
                }
            }
            if (flagEnd == 1) {
                flagEnd = 0;
                break;
            }
        }
        gameboard.characterOnMap(alienAttribute[3],alienAttribute[4],'#');
        character.setAlienLocation(alienAttribute[3]-1,alienAttribute[4]);
        int *alienAttribute = character.getAlienAttribute() ;
        gameboard.characterOnMap(alienAttribute[3],alienAttribute[4], 'A');
        gameboard.display();
        character.display();
        if (alienAttribute[3] == 1) {
            cout << "Alien hits the border. Ending Alien's turn." << endl;
            pauCle::Pause();
            pauCle::ClearScreen();
            zombiemovement(gameboard, character);
        }
    }
}

void Command :: right (GameBoard &gameboard, Character &character, char** obj)
{
    bool flagEnd = 0;
    int *alienAttribute = character.getAlienAttribute() ;
    int **zombieAttribute = character.getZombieAttribute();
    int oriX = alienAttribute[3] - 1;
    int oriY = gameboard.getcoY() - alienAttribute[4];
    char zombie[character.getNoOfZombie()];
    for (int i = 0; i < character.getNoOfZombie(); ++i) {
        zombie[i] = '1' + i;
    }
    for (int i = oriX ; i <gameboard.getcoX()-1 ; ++i)
    {
        int x=i+1;
        char **getmapobject = gameboard.getMapObjects();

        if (alienAttribute[4] == gameboard.getcoX()) {
                cout << "Alien hits the border. Ending Alien's turn." << endl;
                pauCle::Pause();
                pauCle::ClearScreen();
                zombiemovement(gameboard, character);
                break;
        }

        if (getmapobject[oriY][x] == ' ')
        {
            cout << "Alien found an empty space." << endl;
            pauCle::Pause();
            pauCle::ClearScreen();
        }

        else if (getmapobject[oriY][x] == 'r') {
            cout << "Alien hits a rock. Ending Alien's turn." << endl;
            char objects[] = {' ', ' ', ' ', '^', 'v', '<', '>', 'h', 'p'};
            int noOfObjects = 9;
            int randNum = rand() % noOfObjects;
            getmapobject[oriY][x] = objects[randNum];
            gameboard.characterOnMap(alienAttribute[3] + 1, alienAttribute[4], getmapobject[oriY][x]);
            if (getmapobject[oriY][x] == ' ') {
                cout << "Discovers nothing." << endl;
            }
            else if (getmapobject[oriY][x] == '^' || getmapobject[oriY][x] == 'v' || getmapobject[oriY][x] == '<' || getmapobject[oriY][x] == '>') {
                cout << "Discovers an arrow." << endl;
            }
            else if (getmapobject[oriY][x] == 'h') {
                cout << "Discovers a health pack." << endl;
            }
            else if (getmapobject[oriY][x] == 'p') {
                cout << "Discovers a pod." << endl;
            }
            pauCle::Pause();
            pauCle::ClearScreen();
            zombiemovement(gameboard, character);
            break;
        }
    
        else if (getmapobject[oriY][x] == 'h')
        {
            cout << "Alien obtained a health pack." << endl;
            if (alienAttribute[0] >= 100)
            {
                cout << "Health is already full." << endl;
                pauCle::Pause();
                pauCle::ClearScreen();
            }
            else
            {   
                cout << "Restoring 10 health." << endl;                
                character.setAlienHealth(alienAttribute[0] +10);
                pauCle::Pause();
                pauCle::ClearScreen();
            }
        }
        else if (getmapobject[oriY][x] == 'p')
        { 
            cout << "Alien found a pod." << endl;
            int rangeZombie[character.getNoOfZombie()];
            int closestZombie;
            for (int i = 0; i < character.getNoOfZombie(); ++i) {
                int xDif = oriX - zombieAttribute[i][3];
                int yDif = oriY - zombieAttribute[i][4];
                rangeZombie[i] = sqrt((xDif * xDif) + (yDif * yDif));
                closestZombie = *min_element(rangeZombie, rangeZombie + character.getNoOfZombie());
            }
            for (int i = 0; i < character.getNoOfZombie(); ++i) {
                if (rangeZombie[i] == closestZombie) {
                    closestZombie = i;
                    break;
                }
            }
            cout << "Zombie " << closestZombie+1 << " lost 10 health!" << endl;
            pauCle::Pause();
            pauCle::ClearScreen();
            int newhealth = zombieAttribute[closestZombie][0]-10;
            character.setZombieHealth(closestZombie, newhealth);
        }
        else if (getmapobject[oriY][x] == '^')
        {
            cout << "Alien found an ^ arrow." << endl;
            cout << "Alien's attack + 10!" << endl;
            int newDamage = character.getAlienAttribute()[1] + 10;
            character.setAlienAttack(newDamage);
            pauCle::Pause();
            pauCle::ClearScreen();
            gameboard.characterOnMap(alienAttribute[3],alienAttribute[4],'#');
            character.setAlienLocation(alienAttribute[3]+1,alienAttribute[4]);
            int *alienAttribute = character.getAlienAttribute() ;
            gameboard.characterOnMap(alienAttribute[3],alienAttribute[4], 'A');
            gameboard.display();
            character.display();
            if (alienAttribute[4] == gameboard.getcoY()) {
                cout << "Alien hits the border. Ending Alien's turn." << endl;
                pauCle::Pause();
                pauCle::ClearScreen();
                zombiemovement(gameboard, character);
                break;
            }
            else
            {
                for (int i = 0; i < character.getNoOfZombie(); ++i) {
                    if (getmapobject[oriY-1][x] == zombie[i]) {
                        if (zombieAttribute[i][0] >= alienAttribute[1]) {
                            character.setZombieHealth(i, zombieAttribute[i][0] - alienAttribute[1]);
                            cout << endl << "Alien hits a zombie." << endl;
                            cout << "Zombie " << zombie[i] << " loses " << alienAttribute[1] << " health." << endl;
                            cout << "Ending Alien's turn." << endl;
                            flagEnd = 1;
                            pauCle::Pause();
                            pauCle::ClearScreen();
                            zombiemovement(gameboard, character);
                            break;
                        }
                    }
                }
                if (flagEnd == 1) {
                    flagEnd = 0;
                    break;
                }
            }
            cout << endl << "Changing direction. Going Up!" << endl;
            pauCle::Pause();
            pauCle::ClearScreen();

            gameboard.display();
            character.display();
            up(gameboard, character, obj);
            break;
        }

        else if (getmapobject[oriY][x] == 'v')
        {
            cout << "Alien found an v arrow." << endl;
            cout << "Alien's attack + 10!" << endl;
            int newDamage = character.getAlienAttribute()[1] + 10;
            character.setAlienAttack(newDamage);
            pauCle::Pause();
            pauCle::ClearScreen();
            gameboard.characterOnMap(alienAttribute[3],alienAttribute[4],'#');
            character.setAlienLocation(alienAttribute[3]+1,alienAttribute[4]);
            int *alienAttribute = character.getAlienAttribute() ;
            gameboard.characterOnMap(alienAttribute[3],alienAttribute[4], 'A');
            gameboard.display();
            character.display();
            cout << endl << "Changing direction. Going Down!" << endl;
            pauCle::Pause();
            pauCle::ClearScreen();
            if (alienAttribute[4] == 1) {
                cout << "Alien hits the border. Ending Alien's turn." << endl;
                pauCle::Pause();
                pauCle::ClearScreen();
                zombiemovement(gameboard, character);
                break;
            }
            else
            {
                for (int i = 0; i < character.getNoOfZombie(); ++i) {
                    if (getmapobject[oriY + 1][x] == zombie[i]) {
                        if (zombieAttribute[i][0] >= alienAttribute[1]) {
                            character.setZombieHealth(i, zombieAttribute[i][0] - alienAttribute[1]);
                            cout << endl << "Alien hits a zombie." << endl;
                            cout << "Zombie " << zombie[i] << " loses " << alienAttribute[1] << " health." << endl;
                            cout << "Ending Alien's turn." << endl;
                            flagEnd = 1;
                            pauCle::Pause();
                            pauCle::ClearScreen();
                            zombiemovement(gameboard, character);
                            break;
                        }
                    }
                }
                if (flagEnd == 1) {
                    flagEnd = 0;
                    break;
                }
            }
            gameboard.display();
            character.display();
            down(gameboard,character,obj);
            break;
        }

        else if (getmapobject[oriY][x] == '<')
        {
            cout << "Alien found an < arrow." << endl;
            cout << "Alien's attack + 10!" << endl;
            int newDamage = character.getAlienAttribute()[1] + 10;
            character.setAlienAttack(newDamage);
            pauCle::Pause();
            pauCle::ClearScreen();
            gameboard.characterOnMap(alienAttribute[3],alienAttribute[4],'#');
            character.setAlienLocation(alienAttribute[3]+1,alienAttribute[4]);
            int *alienAttribute = character.getAlienAttribute() ;
            gameboard.characterOnMap(alienAttribute[3],alienAttribute[4], 'A');
            gameboard.display();
            character.display();
            if (alienAttribute[3] == 1) {
                cout << "Alien hits the border. Ending Alien's turn." << endl;
                pauCle::Pause();
                pauCle::ClearScreen();
                zombiemovement(gameboard, character);
                break;
            }
            else
            {
                for (int i = 0; i < character.getNoOfZombie(); ++i) {
                    if (getmapobject[oriY][x-1] == zombie[i]) {
                        if (zombieAttribute[i][0] >= alienAttribute[1]) {
                            character.setZombieHealth(i, zombieAttribute[i][0] - alienAttribute[1]);
                            cout << endl << "Alien hits a zombie." << endl;
                            cout << "Zombie " << zombie[i] << " loses " << alienAttribute[1] << " health." << endl;
                            cout << "Ending Alien's turn." << endl;
                            flagEnd = 1;
                            pauCle::Pause();
                            pauCle::ClearScreen();
                            zombiemovement(gameboard, character);
                            break;
                        }
                    }
                }
                if (flagEnd == 1) {
                    flagEnd = 0;
                    break;
                }
            }
            cout << endl << "Changing direction. Going Left!" << endl;
            pauCle::Pause();
            pauCle::ClearScreen();

            gameboard.display();
            character.display();
            left(gameboard,character,obj);
            break;
        }
        
        else if (getmapobject[oriY][x] == '>')
        {
            cout << "Alien found an > arrow." << endl;
            cout << "Alien's attack + 10!" << endl;
            int newDamage = character.getAlienAttribute()[1] + 10;
            character.setAlienAttack(newDamage);
            pauCle::Pause();
            pauCle::ClearScreen();
            gameboard.characterOnMap(alienAttribute[3],alienAttribute[4],'#');
            character.setAlienLocation(alienAttribute[3]+1,alienAttribute[4]);
            int *alienAttribute = character.getAlienAttribute() ;
            gameboard.characterOnMap(alienAttribute[3],alienAttribute[4], 'A');
            gameboard.display();
            character.display();
            if (alienAttribute[3] == gameboard.getcoX()) {
                cout << "Alien hits the border. Ending Alien's turn." << endl;
                pauCle::Pause();
                pauCle::ClearScreen();
                zombiemovement(gameboard, character);
                break;
            }
            else
            {
                for (int i = 0; i < character.getNoOfZombie(); ++i) {
                    if (getmapobject[oriY][x+1] == zombie[i]) {
                        if (zombieAttribute[i][0] >= alienAttribute[1]) {
                            character.setZombieHealth(i, zombieAttribute[i][0] - alienAttribute[1]);
                            cout << endl << "Alien hits a zombie." << endl;
                            cout << "Zombie " << zombie[i] << " loses " << alienAttribute[1] << " health." << endl;
                            cout << "Ending Alien's turn." << endl;
                            flagEnd = 1;
                            pauCle::Pause();
                            pauCle::ClearScreen();
                            zombiemovement(gameboard, character);
                            break;
                        }
                    }
                }
                if (flagEnd == 1) {
                    flagEnd = 0;
                    break;
                }
            }
            pauCle::Pause();
            pauCle::ClearScreen();

            gameboard.display();
            character.display();
            right(gameboard,character,obj);
            break;
        }
        else
        {
            for (int i = 0; i < character.getNoOfZombie(); ++i) {
                if (getmapobject[oriY][x] == zombie[i]) {
                    if (zombieAttribute[i][0] >= alienAttribute[1]) {
                        character.setZombieHealth(i, zombieAttribute[i][0] - alienAttribute[1]);
                        cout << endl << "Alien hits a zombie." << endl;
                        cout << "Zombie " << zombie[i] << " loses " << alienAttribute[1] << " health." << endl;
                        cout << "Ending Alien's turn." << endl;
                        flagEnd = 1;
                        pauCle::Pause();
                        pauCle::ClearScreen();
                        zombiemovement(gameboard, character);
                        break;
                    }
                }
            }
            if (flagEnd == 1) {
                flagEnd = 0;
                break;
            }
        }
        gameboard.characterOnMap(alienAttribute[3],alienAttribute[4],'#');
        character.setAlienLocation(alienAttribute[3]+1,alienAttribute[4]);
        int *alienAttribute = character.getAlienAttribute() ;
        gameboard.characterOnMap(alienAttribute[3],alienAttribute[4], 'A');
        gameboard.display();
        character.display();
        if (alienAttribute[3] == gameboard.getcoX()) {
            cout << "Alien hits the border. Ending Alien's turn." << endl;
            pauCle::Pause();
            pauCle::ClearScreen();
            zombiemovement(gameboard, character);
        }
    }
}

void Command :: zombiemovement(GameBoard &gameboard, Character &character )
{
    int numOfZombie = character.getNoOfZombie();
    int **zombieAttribute = character.getZombieAttribute();
    int *alienAttribute = character.getAlienAttribute();
    string direction[4] =  {"up","down","left","right"};
    for (int i = 0 ; i < numOfZombie ; ++i)
    {
        gameboard.display();
        character.display();
        int which = rand() % 4;
        cout << "Zombie " << i + 1 << "'s turn." << endl; 
        int attackRange = zombieAttribute[i][2] ;
        if(direction[which]== "up")
        {
            gameboard.characterOnMap(zombieAttribute[i][3], zombieAttribute[i][4], ' ');
            zombieAttribute[i][4] +=1;
            cout << "Zombie " << i + 1 << " moves up." << endl;
        }
        else if(direction[which]== "down")
        {
            gameboard.characterOnMap(zombieAttribute[i][3], zombieAttribute[i][4], ' ');
            zombieAttribute[i][4] -=1;
            cout << "Zombie " << i + 1 << " moves down." << endl;
        }
        else if (direction [which] == "left")
        {
            gameboard.characterOnMap(zombieAttribute[i][3], zombieAttribute[i][4], ' ');
            zombieAttribute[i][3] -=1;
            cout << "Zombie " << i + 1 << " moves left." << endl;
        }
        else if (direction [which] == "right")
        {
            gameboard.characterOnMap(zombieAttribute[i][3], zombieAttribute[i][4], ' ');
            zombieAttribute[i][3] +=1;
            cout << "Zombie " << i + 1 << " moves right." << endl;
        }
        gameboard.characterOnMap(zombieAttribute[i][3], zombieAttribute[i][4], '1' + i);
        pauCle::Pause();
        pauCle::ClearScreen();
        gameboard.display();
        character.display();
        
        if (((zombieAttribute[i][3] + 1) == alienAttribute[3]) && (zombieAttribute[i][4] == alienAttribute[4])) 
        {
            alienAttribute[0] = alienAttribute[0] - zombieAttribute[i][1];
            cout << "Zombie " << i + 1 << " attacks." << endl;
        }
        else if (((zombieAttribute[i][3] - 1) == alienAttribute[3]) && (zombieAttribute[i][4] == alienAttribute[4]))
        {
            alienAttribute[0] = alienAttribute[0] - zombieAttribute[i][1];
            cout << "Zombie " << i + 1 << " attacks." << endl;
        }
        else if (((zombieAttribute[i][3]) == alienAttribute[3]) && (zombieAttribute[i][4] + 1 == alienAttribute[4]))
        {
            alienAttribute[0] = alienAttribute[0] - zombieAttribute[i][1];
            cout << "Zombie " << i + 1 << " attacks." << endl;
        }
        else if (((zombieAttribute[i][3]) == alienAttribute[3]) && (zombieAttribute[i][4] - 1 == alienAttribute[4]))
        {
            alienAttribute[0] = alienAttribute[0] - zombieAttribute[i][1];
            cout << "Zombie " << i + 1 << " attacks." << endl;
        }
        else if (attackRange > 1) 
        {
            for (int j = 1; j < attackRange; ++j) 
            {   
                for (int k = 1; k < attackRange; ++k)
                {
                    if (zombieAttribute[i][4] + j == alienAttribute[4] && (zombieAttribute[i][3] + k == alienAttribute[3] || zombieAttribute[i][3] - k == alienAttribute[3]))
                    {
                        alienAttribute[0] = alienAttribute[0] - zombieAttribute[i][1];
                        cout << "Zombie " << i + 1 << " attacks." << endl;
                        break;
                    }
                    else if (zombieAttribute[i][4] - j == alienAttribute[4] && (zombieAttribute[i][3] + k == alienAttribute[3] || zombieAttribute[i][3] - k == alienAttribute[3]))
                    {
                        alienAttribute[0] = alienAttribute[0] - zombieAttribute[i][1];
                        cout << "Zombie " << i + 1 << " attacks." << endl;
                        break;
                    }
                    else if (((zombieAttribute[i][3] + j + 1) == alienAttribute[3]) && (zombieAttribute[i][4] == alienAttribute[4])) 
                    {
                        alienAttribute[0] = alienAttribute[0] - zombieAttribute[i][1];
                        cout << "Zombie " << i + 1 << " attacks." << endl;
                        break;
                    }
                    else if (((zombieAttribute[i][3] - j - 1) == alienAttribute[3]) && (zombieAttribute[i][4] == alienAttribute[4]))
                    {
                        alienAttribute[0] = alienAttribute[0] - zombieAttribute[i][1];
                        cout << "Zombie " << i + 1 << " attacks." << endl;
                        break;
                    }
                    else if (((zombieAttribute[i][3]) == alienAttribute[3]) && (zombieAttribute[i][4] + j + 1 == alienAttribute[4]))
                    {
                        alienAttribute[0] = alienAttribute[0] - zombieAttribute[i][1];
                        cout << "Zombie " << i + 1 << " attacks." << endl;
                        break;
                    }
                    else if (((zombieAttribute[i][3]) == alienAttribute[3]) && (zombieAttribute[i][4] - j - 1 == alienAttribute[4]))
                    {
                        alienAttribute[0] = alienAttribute[0] - zombieAttribute[i][1];
                        cout << "Zombie " << i + 1 << " attacks." << endl;
                        break;
                    }
                }
            }
        }
        else {
            cout << "Alien not in range." << endl;
        }
        character.setAlienHealth(alienAttribute[0]);
        pauCle::Pause();
        pauCle::ClearScreen();
    }
}