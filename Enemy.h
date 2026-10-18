
#ifndef ENEMY_H
#define ENEMY_H
#include "Player.h"
#include "GameState.h"

struct Enemy {
    float x;
    float y;
    float speed;
};

const int MAX_ENEMIES = 10;

struct EnemyManager {
    Enemy enemies[MAX_ENEMIES];
    int enemyCount = 0;
    float spawnTimer = 0;
    bool warningActive = false;
    float warningTimer = 0;
    float warningX = 0;
    float warningY = 0;
};

void SpawnEnemy(EnemyManager& manager,int index, int screenWidth, int screenHeight, const Player& player);
void UpdateEnemies(
    EnemyManager& manager,
    float dt,
    int screenWidth,
    int screenHeight,
    const Player& player,
    const GameState& game
);

#endif
