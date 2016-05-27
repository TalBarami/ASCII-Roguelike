//
// Created by Tal on 27/05/2016.
//

#ifndef UNTITLED_PLAYER_H
#define UNTITLED_PLAYER_H


class Player
{
public:
    Player();
    void init(int level, int health, int attack, int defense, int experience);
    int attack();
    int takeDamage(int attack);

    void setPosition(int x, int y);
    void getPosition(int &x, int &y);
    void addExperience(int experience);

private:
    int _level;
    int _health;
    int _attack;
    int _defense;
    int _experience;

    int _x;
    int _y;
};


#endif //UNTITLED_PLAYER_H
