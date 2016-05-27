//
// Created by Tal on 27/05/2016.
//

#include "Level.h"
#include <fstream>
#include <iostream>
#include <cstdio>


Level::Level()
{
}

void Level::load(string fileName, Player &player) {
    ifstream file;
    file.open(fileName);
    if (file.fail()) {
        perror(fileName.c_str());
        system("PAUSE");
        exit(1);
    }

    string line;

    while (getline(file, line)) {
        _levelData.push_back(line);
    }

    file.close();

    char tile;
    for (unsigned int i = 0; i < _levelData.size(); i++) {
        for (unsigned int j = 0; j < _levelData[i].size(); j++) {
            tile = _levelData[i][j];
            switch (tile) {
                case '@': // Player
                    player.setPosition(j, i);
                    break;
                case 'S':
                    _enemies.push_back(Enemy("Snake", tile, 1, 3, 1, 10, 50));
                    _enemies.back().setPosition(j, i);
                    break;
                case 'g':
                    _enemies.push_back(Enemy("Goblin", tile, 2, 10, 5, 35, 150));
                    _enemies.back().setPosition(j, i);
                    break;
                case 'B':
                    _enemies.push_back(Enemy("Bandit", tile, 3, 15, 10, 100, 250));
                    _enemies.back().setPosition(j, i);
                    break;
                case 'O':
                    _enemies.push_back(Enemy("Ogre", tile, 4, 20, 40, 200, 500));
                    _enemies.back().setPosition(j, i);
                    break;
                case 'D':
                    _enemies.push_back(Enemy("Dragon", tile, 100, 2000, 2000, 2000, 5000000));
                    _enemies.back().setPosition(j, i);
                    break;
                default:
                    break;
            }
        }
    }
}

void Level::print() {

    system("cls");
    //cout << string(100, '\n');

    for (int i = 0; i < _levelData.size(); i++) {
        printf("%s\n", _levelData[i].c_str());
    }
    printf("\n");
}

void Level::movePlayer(char input, Player &player) {

    int playerX;
    int playerY;

    player.getPosition(playerX, playerY);

    switch (input) {
        case 'w':
        case 'W':
            processPlayerMove(player, playerX, playerY - 1);
            break;
        case 's':
        case 'S':
            processPlayerMove(player, playerX, playerY + 1);
            break;
        case 'a':
        case 'A':
            processPlayerMove(player, playerX - 1, playerY);
            break;
        case 'd':
        case 'D':
            processPlayerMove(player, playerX + 1, playerY);
            break;
        default:
            printf("Invalid inpute!\n");
            system("PAUSE");
            break;
    }
}

char Level::getTile(int x, int y) {
    return _levelData[y][x];
}

void Level::setTile(int x, int y, char tile) {
    _levelData[y][x] = tile;
}

void Level::processPlayerMove(Player &player, int targetX, int targetY) {
    int playerX, playerY;
    player.getPosition(playerX, playerY);

    char moveTile = getTile(targetX, targetY);
    switch (moveTile) {
        case '.':
            player.setPosition(targetX, targetY);
            setTile(playerX, playerY, '.');
            setTile(targetX, targetY, '@');
            break;
        case '#':
            break;
        default:
            battleMonster(player, targetX, targetY);
            break;
    }
}

void Level::processEnemyMove(Player &player, int enemyIndex, int targetX, int targetY) {
    int playerX, playerY, enemyX, enemyY;
    player.getPosition(playerX, playerY);
    _enemies[enemyIndex].getPosition(enemyX, enemyY);

    char moveTile = getTile(targetX, targetY);
    switch (moveTile) {
        case '.':
            _enemies[enemyIndex].setPosition(targetX, targetY);
            setTile(enemyX, enemyY, '.');
            setTile(targetX, targetY, _enemies[enemyIndex].getTile());
            break;
        case '#':
            break;
        case '@':
            battleMonster(player, enemyX, enemyY);
            break;
        default:
            break;
    }
}

void Level::battleMonster(Player &player, int targetX, int targetY) {
    int enemyX, enemyY, playerX, playerY, attackRoll, attackResult;
    string enemyName;
    player.getPosition(playerX, playerY);

    for (int i = 0; i < _enemies.size(); i++) {
        _enemies[i].getPosition(enemyX, enemyY);
        enemyName = _enemies[i].getName();
        if (targetX == enemyX && targetY == enemyY) {
            attackRoll = player.attack();
            printf("\nPlayer attacked %s with a roll of %d\n", enemyName.c_str(), attackRoll);
            attackResult = _enemies[i].takeDamage(attackRoll);
            if (attackResult != 0) {
                setTile(targetX, targetY, '.');
                print();
                printf("%s died!\n", enemyName.c_str());
                // Remove the enemy:
                _enemies[i] = _enemies.back();
                _enemies.pop_back();
                i--;

                system("PAUSE");
                player.addExperience(attackResult);
                return;
            }

            attackRoll = _enemies[i].attack();
            printf("%s attacked player with a roll of %d\n", enemyName.c_str(), attackRoll);
            attackResult = player.takeDamage(attackRoll);
            if (attackResult != 0) {
                setTile(playerX, playerY, 'x');
                print();
                printf("You died!\n");
                system("PAUSE");
                exit(0);
            }
            system("PAUSE");
            return;
        }
    }
}

void Level::updateEnemies(Player &player) {
    char aiMove;
    int playerX, playerY, enemyX, enemyY;
    player.getPosition(playerX, playerY);

    for (int i = 0; i < _enemies.size(); i++) {
        aiMove = _enemies[i].getMove(playerX, playerY);
        _enemies[i].getPosition(enemyX, enemyY);

        switch (aiMove) {
            case 'w':
                processEnemyMove(player, i, enemyX, enemyY - 1);
                break;
            case 's':
                processEnemyMove(player, i, enemyX, enemyY + 1);
                break;
            case 'a':
                processEnemyMove(player, i, enemyX - 1, enemyY);
                break;
            case 'd':
                processEnemyMove(player, i, enemyX + 1, enemyY);
                break;
        }
    }
}