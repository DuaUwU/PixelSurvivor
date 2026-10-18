#ifndef BULLET_H
#define BULLET_H
#include "Player.h"


struct Bullet {
    float x;
    float y;
    float velocityX;
    float velocityY;
    float speed;
    bool active;
};

const int MAX_BULLETS = 100;

struct BulletManager {
    Bullet bullets[MAX_BULLETS];
    int bulletCount = 0;
};

void ShootBullet(
    BulletManager& manager,
    const Player& player,
    float directionX,
    float directionY
);

#endif