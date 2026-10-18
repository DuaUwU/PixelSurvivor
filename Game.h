#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Enemy.h"
#include "GameState.h"

extern GameState game;

void ResetGame(
    int screenWidth,
    int screenHeight,
    EnemyManager& enemyManager,
    Player& player
);

void CheckCollisions(
    EnemyManager& enemyManager,
    Player& player
);

#endif