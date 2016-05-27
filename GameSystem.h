//
// Created by Tal on 27/05/2016.
//

#ifndef UNTITLED_GAMESYSTEM_H
#define UNTITLED_GAMESYSTEM_H

#include "Player.h"
#include "Level.h"
#include <string>

using namespace std;

class GameSystem
{
public:
    GameSystem(string levelFileName);
    void playGame();
    void playerMove();

private:
    Level _level;
    Player _player;
};



#endif //UNTITLED_GAMESYSTEM_H
