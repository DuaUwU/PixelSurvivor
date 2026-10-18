
#include "raylib.h"
#include <cmath>

#include "Player.h"
#include "Enemy.h"
#include "Game.h"
#include "Bullet.h"

enum ScreenState
{
    MENU,
    PLAYING,
    GAME_OVER
};

ScreenState currentScreen = MENU;

Player player;
EnemyManager enemyManager;
BulletManager bulletManager;

float shootDirectionX = 0;
float shootDirectionY = -1;

// ==================== MENU ====================

void DrawMenu()
{
    BeginDrawing();
    ClearBackground(Color{18, 22, 34, 255});

    // Nen luoi
    for (int x = 0; x < 800; x += 40)
        DrawLine(x, 0, x, 450, Color{30, 37, 52, 255});

    for (int y = 0; y < 450; y += 40)
        DrawLine(0, y, 800, y, Color{30, 37, 52, 255});

    DrawText("PIXEL SURVIVOR", 205, 90, 48, GREEN);
    DrawText("SURVIVE AS LONG AS YOU CAN",
             235, 150, 20, LIGHTGRAY);

    DrawRectangle(290, 220, 220, 55,
                  Color{35, 100, 65, 255});
    DrawRectangleLines(290, 220, 220, 55, GREEN);
    DrawText("PRESS ENTER TO PLAY", 310, 238, 18, WHITE);

    DrawText("W A S D - Move", 315, 315, 20, LIGHTGRAY);
    DrawText("SPACE - Shoot", 315, 345, 20, LIGHTGRAY);

    EndDrawing();
}

// ==================== BACKGROUND ====================

void DrawBackground()
{
    ClearBackground(Color{18, 22, 34, 255});

    for (int x = 0; x < 800; x += 40)
        DrawLine(x, 0, x, 450, Color{30, 37, 52, 255});

    for (int y = 0; y < 450; y += 40)
        DrawLine(0, y, 800, y, Color{30, 37, 52, 255});
}

// ==================== PLAYER ====================

void DrawPlayer()
{
    DrawRectangle(
        (int)player.x,
        (int)player.y,
        32, 32, GREEN
    );

    DrawRectangleLines(
        (int)player.x,
        (int)player.y,
        32, 32, LIME
    );
}

// ==================== GAME ====================

void DrawGame()
{
    BeginDrawing();
    DrawBackground();

    // Ve HUD va nhan vat khi dang choi
    if (currentScreen == PLAYING)
    {
        // Khung HUD
        DrawRectangle(
            15, 15, 220, 75,
            Color{12, 16, 27, 230}
        );

        DrawRectangleLines(
            15, 15, 220, 75,
            Color{55, 70, 95, 255}
        );

        // Thanh mau
        DrawText("HEALTH", 25, 23, 14, LIGHTGRAY);
        DrawRectangle(25, 45, 180, 14, DARKGRAY);

        int healthWidth = player.health * 60;

        if (healthWidth > 180) healthWidth = 180;
        if (healthWidth < 0) healthWidth = 0;

        Color hpColor = GREEN;

        if (player.health == 2) hpColor = ORANGE;
        if (player.health <= 1) hpColor = RED;

        DrawRectangle(25, 45, healthWidth, 14, hpColor);

        DrawText(
            TextFormat("SCORE  %d", game.score),
            25, 66, 16, WHITE
        );

        DrawText(
            TextFormat("TIME  %.1f s", game.survivalTime),
            20, 100, 20, WHITE
        );

        // Hieu ung bat tu
        if (player.invincibleTimer <= 0 ||
            fmod(player.invincibleTimer, 0.2f) > 0.1f)
        {
            DrawPlayer();
        }

        // Ve quai
        for (int i = 0; i < enemyManager.enemyCount; i++)
        {
            int x = (int)enemyManager.enemies[i].x;
            int y = (int)enemyManager.enemies[i].y;

            DrawRectangle(x, y, 32, 32, RED);
            DrawRectangleLines(x, y, 32, 32, MAROON);
        }

        // Vong canh bao spawn
        if (enemyManager.warningActive)
        {
            float radius = 15 + enemyManager.warningTimer * 20;

            DrawCircleLines(
                (int)(enemyManager.warningX + 16),
                (int)(enemyManager.warningY + 16),
                radius,
                YELLOW
            );
        }

        // Ve dan
        for (int i = 0; i < bulletManager.bulletCount; i++)
        {
            const Bullet& bullet = bulletManager.bullets[i];

            if (bullet.active)
            {
                DrawCircle(
                    (int)bullet.x,
                    (int)bullet.y,
                    5,
                    YELLOW
                );
            }
        }
    }

    // Man hinh Game Over
    if (currentScreen == GAME_OVER)
    {
        DrawRectangle(
            0, 0, 800, 450,
            Color{0, 0, 0, 210}
        );

        DrawText("GAME OVER", 250, 125, 44, RED);

        DrawText(
            TextFormat("FINAL SCORE: %d", game.score),
            285, 200, 24, WHITE
        );

        DrawText(
            TextFormat("SURVIVAL TIME: %.1f s", game.survivalTime),
            270, 240, 20, LIGHTGRAY
        );

        DrawRectangle(
            270, 290, 260, 48,
            Color{35, 100, 65, 255}
        );

        DrawRectangleLines(
            270, 290, 260, 48, GREEN
        );

        DrawText(
            "PRESS R TO RETRY",
            300, 305, 20, WHITE
        );
    }

    EndDrawing();
}

// ==================== RESET ====================

void StartNewGame(
    int screenWidth,
    int screenHeight
)
{
    ResetGame(
        screenWidth,
        screenHeight,
        enemyManager,
        player
    );

    bulletManager.bulletCount = 0;

    shootDirectionX = 0;
    shootDirectionY = -1;

    currentScreen = PLAYING;
}

// ==================== MAIN ====================

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(
        screenWidth,
        screenHeight,
        "Pixel Survivor"
    );

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        // MENU
        if (currentScreen == MENU)
        {
            if (IsKeyPressed(KEY_ENTER))
            {
                StartNewGame(screenWidth, screenHeight);
            }
        }

        // PLAYING
        else if (currentScreen == PLAYING)
        {
            // Cap so huong di chuyen
            float moveX = 0;
            float moveY = 0;

            if (IsKeyDown(KEY_A)) moveX -= 1;
            if (IsKeyDown(KEY_D)) moveX += 1;
            if (IsKeyDown(KEY_W)) moveY -= 1;
            if (IsKeyDown(KEY_S)) moveY += 1;

            if (moveX != 0 || moveY != 0)
            {
                float length = sqrt(
                    moveX * moveX + moveY * moveY
                );

                shootDirectionX = moveX / length;
                shootDirectionY = moveY / length;
            }

            // Ban dan
            if (IsKeyPressed(KEY_SPACE))
            {
                ShootBullet(
                    bulletManager,
                    player,
                    shootDirectionX,
                    shootDirectionY
                );
            }

            // Cap nhat dan
            for (int i = 0; i < bulletManager.bulletCount; i++)
            {
                Bullet& bullet = bulletManager.bullets[i];

                if (!bullet.active)
                    continue;

                bullet.x += bullet.velocityX * bullet.speed * dt;
                bullet.y += bullet.velocityY * bullet.speed * dt;

                if (bullet.x < 0 || bullet.x > screenWidth ||
                    bullet.y < 0 || bullet.y > screenHeight)
                {
                    bullet.active = false;
                }
            }

            // Don dan khong hoat dong
            int writeIndex = 0;

            for (int i = 0; i < bulletManager.bulletCount; i++)
            {
                if (bulletManager.bullets[i].active)
                {
                    bulletManager.bullets[writeIndex] =
                        bulletManager.bullets[i];

                    writeIndex++;
                }
            }

            bulletManager.bulletCount = writeIndex;

            // Cap nhat game
            game.survivalTime += dt;

            UpdatePlayer(
                player, dt,
                screenWidth, screenHeight
            );

            UpdateEnemies(
                enemyManager, dt,
                screenWidth, screenHeight,
                player, game
            );

            CheckCollisions(enemyManager, player);

            CheckBulletCollisions(
                bulletManager,
                enemyManager,
                game
            );

            // Dem thoi gian bat tu
            if (player.invincibleTimer > 0)
            {
                player.invincibleTimer -= dt;

                if (player.invincibleTimer < 0)
                    player.invincibleTimer = 0;
            }

            // Game Over
            if (player.health <= 0)
            {
                game.gameOver = true;
                currentScreen = GAME_OVER;
            }
        }

        // GAME OVER
        else if (currentScreen == GAME_OVER)
        {
            if (IsKeyPressed(KEY_R))
            {
                StartNewGame(screenWidth, screenHeight);
            }
        }

        // Ve man hinh hien tai
        if (currentScreen == MENU)
            DrawMenu();
        else
            DrawGame();
    }

    CloseWindow();
    return 0;
}
