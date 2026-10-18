#include "Enemy.h"
#include "Player.h"
#include "Game.h"
#include "raylib.h"
#include <cmath>
#include <cstdlib>


void SpawnEnemy(
    EnemyManager& manager,
    int index,
    int screenWidth,
    int screenHeight,
    const Player& player
) {
    // Quái xuất hiện tại đúng vị trí vòng cảnh báo
    manager.enemies[index].x = manager.warningX;
    manager.enemies[index].y = manager.warningY;

    manager.enemies[index].speed = 100;
}

void UpdateEnemies(EnemyManager& manager,float dt, int screenWidth, int screenHeight, const Player& player, const GameState& game) {
    // Đếm thời gian đến đợt spawn tiếp theo
    manager.spawnTimer += dt;

    float spawnInterval = 10.0f - game.survivalTime * 0.1f;

    if (spawnInterval < 3.0f) {
        spawnInterval = 3.0f;
    }

// Bắt đầu cảnh báo
    if (!manager.warningActive &&
        manager.spawnTimer >= spawnInterval &&
        manager.enemyCount < MAX_ENEMIES) {

        manager.warningActive = true;
        manager.warningTimer = 0;

        // Chọn vị trí cảnh báo cách player ít nhất 120 pixel
        float dx, dy, distance;

        do {
            manager.warningX =
                (float)GetRandomValue(16, screenWidth - 48);
            manager.warningY =
                (float)GetRandomValue(16, screenHeight - 48);

            dx = manager.warningX - (player.x + 16);
            dy = manager.warningY - (player.y + 16);

            distance = sqrt(dx * dx + dy * dy);

        } while (distance < 120);
    }

// Đang đếm ngược cảnh báo
    if (manager.warningActive) {
        manager.warningTimer += dt;

        if (manager.warningTimer >= 0.5f) {
            float dx = manager.warningX - (player.x + 16);
            float dy = manager.warningY - (player.y + 16);
            float distance = sqrt(dx * dx + dy * dy);

            // Nếu player đi vào quá gần vị trí spawn,
            // chọn lại vị trí và cảnh báo thêm lần nữa.
            if (distance < 120) {
                manager.warningX =
                    (float)GetRandomValue(16, screenWidth - 48);
                manager.warningY =
                    (float)GetRandomValue(16, screenHeight - 48);

                dx = manager.warningX - (player.x + 16);
                dy = manager.warningY - (player.y + 16);
                distance = sqrt(dx * dx + dy * dy);

                while (distance < 120) {
                    manager.warningX =
                        (float)GetRandomValue(16, screenWidth - 48);
                    manager.warningY =
                        (float)GetRandomValue(16, screenHeight - 48);

                    dx = manager.warningX - (player.x + 16);
                    dy = manager.warningY - (player.y + 16);
                    distance = sqrt(dx * dx + dy * dy);
                }

                manager.warningTimer = 0;
            } else {
                int index = manager.enemyCount;

                manager.enemies[index].x = manager.warningX;
                manager.enemies[index].y = manager.warningY;
                manager.enemies[index].speed = 100;

                manager.enemyCount++;

                manager.warningActive = false;
                manager.warningTimer = 0;
                manager.spawnTimer = 0;
            }
        }
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