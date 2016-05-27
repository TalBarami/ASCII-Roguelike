//
// Created by Tal on 27/05/2016.
//

#ifndef UNTITLED_LEVEL_H
#define UNTITLED_LEVEL_H

#include <vector>
#include <string>
#include "Player.h"
#include "Enemy.h"

using namespace std;

class Level
{
public:
    Level();
    void load(string fileName, Player &player);
    void print();

    void movePlayer(char input, Player &player);
    void updateEnemies(Player &player);

    char getTile(int x, int y);
    void setTile(int x, int y, char tile);

private:
    void processPlayerMove(Player &player, int targetX, int targetY);
    void processEnemyMove(Player &player, int enemyIndex, int targetX, int targetY);
    void battleMonster(Player &player, int targetX, int targetY);

private:
    vector <string> _levelData;
    vector<Enemy> _enemies;
};



#endif //UNTITLED_LEVEL_H
