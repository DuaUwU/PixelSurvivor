#ifndef PLAYER_H
#define PLAYER_H

struct Player {
    float x = 400;
    float y = 225;
    float speed = 200;
    int health = 3;
    float invincibleTimer = 0;
};

void UpdatePlayer(Player& player, float dt, int screenWidth, int screenHeight);

#endif