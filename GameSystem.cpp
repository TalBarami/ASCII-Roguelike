//
// Created by Tal on 27/05/2016.
//

#include "GameSystem.h"
#include <iostream>
#include <conio.h>

GameSystem::GameSystem(string levelFileName)
{
    _player.init(1, 100, 10, 10, 0);
    _level.load(levelFileName, _player);
    _level.print();

    system("PAUSE");
}

void GameSystem::playGame()
{
    bool isDone = false;

    while (!isDone) {
        _level.print();
        playerMove();
        _level.updateEnemies(_player);
    }
}

void GameSystem::playerMove() {
    char input;
    printf("Enter a move command (w/s/a/d): ");
    input = _getch();

    _level.movePlayer(input, _player);
}