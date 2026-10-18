#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Enemy.h"
#include "GameState.h"
#include "Bullet.h"

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

void CheckBulletCollisions(
    BulletManager& bulletManager,
    EnemyManager& enemyManager,
    GameState& game
);

#endif