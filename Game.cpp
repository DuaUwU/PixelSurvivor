#include "Enemy.h"
#include "Player.h"
#include "GameState.h"
#include "Bullet.h"
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

void CheckBulletCollisions(
    BulletManager& bulletManager,
    EnemyManager& enemyManager,
    GameState& game
) {
    for (int i = 0; i < bulletManager.bulletCount; i++) {
        Bullet& bullet = bulletManager.bullets[i];

        if (!bullet.active) {
            continue;
        }

        for (int j = 0; j < enemyManager.enemyCount; j++) {
            Enemy& enemy = enemyManager.enemies[j];

            bool hit = CheckCollisionCircles(
                Vector2{bullet.x, bullet.y},
                5,
                Vector2{enemy.x + 16, enemy.y + 16},
                16
            );
                
                if (hit) {
                // Xóa viên đạn đã trúng
                bullet.active = false;

                // Cộng 10 điểm
                game.score += 10;

                // Xóa kẻ địch bằng cách dồn mảng
                for (int k = j; k < enemyManager.enemyCount - 1; k++) {
                    enemyManager.enemies[k] =
                        enemyManager.enemies[k + 1];
                }
                
                enemyManager.enemyCount--;

                // Viên đạn chỉ tiêu diệt một kẻ địch
                break;
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
    enemyManager.warningActive = false;
    enemyManager.warningTimer = 0;
    enemyManager.warningX =
    (float)GetRandomValue(16, screenWidth - 48);

    enemyManager.warningY =
    (float)GetRandomValue(16, screenHeight - 48);    
    SpawnEnemy(enemyManager, 0,screenWidth,screenHeight, player);
    player.invincibleTimer = 0;
    game.score = 0;
    game.survivalTime = 0;
    game.gameOver = false;
}