//
// Created by Tal on 27/05/2016.
//

#include "Enemy.h"
#include <random>
#include <ctime>

using namespace std;

Enemy::Enemy(string name, char tile, int level, int attack, int defense, int health, int experienceValue)
{
    _name = name;
    _tile = tile;
    _level = level;
    _attack = attack;
    _defense = defense;
    _health = health;
    _experienceValue = experienceValue;
}

int Enemy::attack() {
    static default_random_engine randomEngine(time(NULL));
    uniform_int_distribution<int> attackRoll(0, _attack);
    return attackRoll(randomEngine);
}

int Enemy::takeDamage(int attack) {
    attack -= _defense;
    if (attack > 0) {
        _health -= attack;
        if (_health <= 0)
            return _experienceValue;
    }
    return 0;
}

char Enemy::getMove(int playerX, int playerY) {
    static default_random_engine rEngine(time(NULL));
    uniform_int_distribution<int> moveRoll(0, 6);

    int dx = _x - playerX;
    int dy = _y - playerY;
    int adx = abs(dx);
    int ady = abs(dy);
    int distance = adx + ady;

    if (distance <= 5) {
        if (adx > ady) { // Moving along x axis
            if (dx > 0)
                return 'a';
            else
                return 'd';
        }
        else { // Moving along y axis
            if (dy > 0)
                return 'w';
            else
                return 's';
        }
    }
    int randomMove = moveRoll(rEngine);
    switch (randomMove) {
        case 0:
            return 'w';
        case 1:
            return 'a';
        case 2:
            return 's';
        case 3:
            return 'd';
        default:
            return '.';
    }
}

void Enemy::setPosition(int x, int y) {
    _x = x;
    _y = y;
}
void Enemy::getPosition(int &x, int &y) {
    x = _x;
    y = _y;
}

char Enemy::getTile() {
    return _tile;
}

string Enemy::getName() {
    return _name;
}