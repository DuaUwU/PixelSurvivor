#include "Bullet.h"
#include "Player.h"
#include "raylib.h"
#include <cmath>

void ShootBullet(
    BulletManager& manager,
    const Player& player,
    float directionX,
    float directionY
) {
    if (manager.bulletCount >= MAX_BULLETS) {
        return;
    }

    int index = manager.bulletCount;

    manager.bullets[index].x = player.x + 16;
    manager.bullets[index].y = player.y + 16;

    float length = sqrt(
        directionX * directionX +
        directionY * directionY
    );

    if (length == 0) {
        return;
    }

    manager.bullets[index].velocityX = directionX / length;
    manager.bullets[index].velocityY = directionY / length;

    manager.bullets[index].speed = 400;
    manager.bullets[index].active = true;

    manager.bulletCount++;
}