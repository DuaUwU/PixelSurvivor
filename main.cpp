#include "raylib.h"
#include <cmath>
#include "Player.h"
#include "Enemy.h"
#include "Game.h"



Player player;
EnemyManager enemyManager;

void DrawGame(){

        BeginDrawing();

        ClearBackground(BLACK);
        if(!game.gameOver) {
            DrawText(TextFormat("HP: %d", player.health),
            20, 20, 24, WHITE);
            
            DrawText(TextFormat("Score: %d", game.score),
            20, 50, 24, WHITE);


            if (player.invincibleTimer > 0) {
            if (fmod(player.invincibleTimer, 0.2f) > 0.1f)
                DrawRectangle(player.x, player.y, 32, 32, GREEN);
            }
            else {
                DrawRectangle(player.x, player.y, 32, 32, GREEN);
            }

            for(int i = 0; i < enemyManager.enemyCount; i++) {
                DrawRectangle(enemyManager.enemies[i].x, enemyManager.enemies[i].y, 32, 32, RED);
            }
        }
        if(game.gameOver) {
            DrawText("GAME OVER", 250, 150, 40, RED);
            DrawText(TextFormat("Score: %d", game.score), 300, 210, 20, WHITE);
            DrawText("Press R to Restart", 250, 250, 20, WHITE);
        }

        EndDrawing();
}

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Pixel Survivor");
    SetTargetFPS(60);

    enemyManager.enemyCount = 1;

    for (int i = 0; i < enemyManager.enemyCount; i++) {
        SpawnEnemy(enemyManager, i, screenWidth, screenHeight, player);
    }   

    while (!WindowShouldClose()) {
        
        float dt = GetFrameTime();

        if(!game.gameOver) {

            game.survivalTime += dt;
            game.score = (int)game.survivalTime;

            UpdatePlayer(player, dt, screenWidth, screenHeight);
            UpdateEnemies(enemyManager, dt, screenWidth, screenHeight, player,game);
            CheckCollisions(enemyManager, player);
            
            if(player.invincibleTimer > 0) {
                player.invincibleTimer -= dt;
            }

            if(player.invincibleTimer < 0) {
                player.invincibleTimer = 0;
            }

            if(player.health <= 0) {
                game.gameOver = true;
            }
        }

        if(game.gameOver && IsKeyPressed(KEY_R)){
            ResetGame(
                screenWidth,
                screenHeight,
                enemyManager,
                player
            );
        }

        DrawGame();
    }
    CloseWindow();
    return 0;
}
