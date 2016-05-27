//
// Created by Tal on 27/05/2016.
//

#ifndef UNTITLED_ENEMY_H
#define UNTITLED_ENEMY_H

#include <string>

using namespace std;

class Enemy
{
public:
    Enemy(string name, char tile, int level, int attack, int defense, int health, int experience);

    int attack();
    int takeDamage(int attack);

    void setPosition(int x, int y);
    void getPosition(int &x, int &y);
    char getTile();
    string getName();

    // AI move command
    char getMove(int playerX, int playerY);

private:
    string _name;
    char _tile;

    int _level;
    int _attack;
    int _defense;
    int _health;
    int _experienceValue;

    int _x;
    int _y;
};


#endif //UNTITLED_ENEMY_H
