#include "Enemy.h"
#include "Player.h"
#include "GameState.h"
#include "raylib.h"
#include <cmath>
#include <cstdlib>

GameState game;

void CheckCollisions(EnemyManager& enemyManager, Player& player) {
    Rectangle playerRect = {player.x, player.y, 32, 32};

    for (int i = 0; i < enemyManager.enemyCount; i++) {
        Rectangle enemyRect = {enemyManager.enemies[i].x, enemyManager.enemies[i].y, 32, 32};

        if (CheckCollisionRecs(playerRect, enemyRect)) {
            if (player.invincibleTimer <= 0) {
                player.invincibleTimer = 1.0f;
                player.health--;
                TraceLog(LOG_INFO, "Player collided with enemy!");
            }
        }
    }
}

void ResetGame(int screenWidth, int screenHeight, EnemyManager& enemyManager, Player& player){
    player.health = 3;
    player.x = (screenWidth - 32) / 2.0f;
    player.y = (screenHeight - 32) / 2.0f;
    enemyManager.enemyCount = 1;
    enemyManager.spawnTimer = 0;
    SpawnEnemy(enemyManager, 0,screenWidth,screenHeight, player);
    player.invincibleTimer = 0;
    game.score = 0;
    game.survivalTime = 0;
    game.gameOver = false;
}