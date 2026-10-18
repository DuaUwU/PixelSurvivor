#include "Enemy.h"
#include "Player.h"
#include "Game.h"
#include "raylib.h"
#include <cmath>
#include <cstdlib>

void SpawnEnemy(EnemyManager& manager, int index, int screenWidth, int screenHeight, const Player& player) {
    
    float spawnRadius = 100;
    float distance;
    do{
        manager.enemies[index].x = GetRandomValue(0, screenWidth - 32);
        manager.enemies[index].y = GetRandomValue(0, screenHeight - 32);

        float dx = manager.enemies[index].x - player.x;
        float dy = manager.enemies[index].y - player.y;

        distance = sqrt(dx * dx + dy * dy);

    }while(distance < spawnRadius);
    
    manager.enemies[index].speed = 100;
}   

void UpdateEnemies(EnemyManager& manager,float dt, int screenWidth, int screenHeight, const Player& player, const GameState& game) {
    manager.spawnTimer += dt;
    if(manager.spawnTimer >= 10 && manager.enemyCount < MAX_ENEMIES) {
        manager.spawnTimer = 0;
        SpawnEnemy(manager, manager.enemyCount,screenWidth,screenHeight, player);
        manager.enemyCount++;
    }

    for(int i = 0; i < manager.enemyCount; i++){

        float dx = player.x - manager.enemies[i].x;
        float dy = player.y - manager.enemies[i].y;
        float enemylength = sqrt(dx * dx + dy * dy);
        manager.enemies[i].speed = 100 + game.survivalTime * 2;
        if(manager.enemies[i].speed > 300) {
            manager.enemies[i].speed = 300;
        }

        if(enemylength > 0) {
            dx /= enemylength;
            dy /= enemylength;
            manager.enemies[i].x += dx * manager.enemies[i].speed * dt;
            manager.enemies[i].y += dy * manager.enemies[i].speed * dt;
        }
    }
}