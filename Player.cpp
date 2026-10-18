
#include "Player.h"
#include "raylib.h"
#include <cmath>

void UpdatePlayer(Player& player, float dt,
                  int screenWidth, int screenHeight) {
    float moveX = 0;
    float moveY = 0;

    if (IsKeyDown(KEY_W)) moveY -= 1;
    if (IsKeyDown(KEY_S)) moveY += 1;
    if (IsKeyDown(KEY_A)) moveX -= 1;
    if (IsKeyDown(KEY_D)) moveX += 1;

    float length = std::sqrt(moveX * moveX + moveY * moveY);

    if (length > 0) {
        moveX /= length;
        moveY /= length;
    }

    player.x += moveX * player.speed * dt;
    player.y += moveY * player.speed * dt;

    if (player.x < 0) player.x = 0;
    if (player.y < 0) player.y = 0;
    if (player.x > screenWidth - 32)
        player.x = screenWidth - 32;
    if (player.y > screenHeight - 32)
        player.y = screenHeight - 32;
}
